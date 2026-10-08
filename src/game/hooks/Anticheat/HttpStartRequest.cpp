#include "common.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/hooks/ShopBackend/ShopJson.hpp"

namespace YimMenu::Features
{
	extern bool g_FreeShoppingEnabled;
}

namespace YimMenu::Hooks
{
	void Anticheat::HttpStartRequest(void* request)
	{
		uintptr_t req_ptr = reinterpret_cast<uintptr_t>(request);
		const char** host_ptr = reinterpret_cast<const char**>(req_ptr + 0x18F8);
		const char* path = *reinterpret_cast<const char**>(req_ptr + 0x1900);

		if (path && strstr(path, "GameTransactions.asmx/Bonus"))
		{
			*const_cast<const char**>(host_ptr) = "0.0.0.0";
			LOG(WARNING) << "Blocked Bonus Report";
		}

		const bool isTxn = path && (strstr(path, "GameTransactions") || strstr(path, "Catalog") || strstr(path, "shop"));

		if (Features::g_FreeShoppingEnabled && request)
		{
			static int s_scans = 0;
			++s_scans;

			// Walk the whole request object (not just head pointers): body ptr
			// often sits near host/path at +0x18F0 and in a small wrapper.
			const bool hit = ShopJson::TryRewriteObjectGraph(request, 0x4000, 256);

			if (hit)
			{
				LOG(INFO) << "[ShopBackend] HttpStartRequest rewrote txn JSON (scan #" << s_scans
				          << ") path=" << (path ? path : "?");
			}
			else if (isTxn && s_scans <= 24)
			{
				LOG(INFO) << "[ShopBackend] HttpStartRequest no-json #" << s_scans
				          << " path=" << path;

				// Dump pointer candidates across the object so we can find the body.
				auto* slots = reinterpret_cast<std::uint64_t*>(request);
				int shown    = 0;
				for (int i = 0; i < 0x1A00 / 8 && shown < 16; ++i)
				{
					if (!ShopJson::IsLikelyUserPtr(slots[i]))
						continue;
					++shown;
					LOG(INFO) << "[ShopBackend] req +" << std::hex << (i * 8)
					          << " = 0x" << slots[i] << std::dec;
					// Peek first bytes of each pointee for '{'.
					auto* child = reinterpret_cast<const unsigned char*>(slots[i]);
					__try
					{
						if (child[0] == '{' || child[0] == ' ')
							LOG(INFO) << "[ShopBackend]   child looks like text: "
							          << ShopJson::DumpToLine("body?", child, 64);
					}
					__except (EXCEPTION_EXECUTE_HANDLER)
					{
					}
				}
			}
		}

		return BaseHook::Get<Anticheat::HttpStartRequest, DetourHook<decltype(&Anticheat::HttpStartRequest)>>()->Original()(request);
	}
}
