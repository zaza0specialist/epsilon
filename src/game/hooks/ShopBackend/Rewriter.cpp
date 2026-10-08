#include "common.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/hooks/ShopBackend/ShopJson.hpp"

#include <cstdint>

namespace YimMenu::Features
{
	extern bool g_FreeShoppingEnabled;
}

namespace YimMenu::Hooks
{
	std::uint64_t ShopBackend::Rewriter(void* ctx, std::uint32_t a2, std::uint32_t a3, std::uint32_t a4, void* payload)
	{
		static int s_enters   = 0;
		static int s_failDump = 0;
		++s_enters;

		const bool freeshop = Features::g_FreeShoppingEnabled;
		if (s_enters <= 12)
		{
			LOG(INFO) << "[ShopBackend] Rewriter ENTER #" << s_enters
			          << " ctx=" << ctx << " payload=" << payload
			          << " a2=0x" << std::hex << a2 << " a3=0x" << a3 << " a4=0x" << a4 << std::dec
			          << " freeshop=" << freeshop;
		}

		bool rewritten = false;

		// JSON may already be in the payload, or only built inside original().
		if (freeshop)
			rewritten = ShopJson::HuntAndRewrite(payload, ctx);

		auto result = BaseHook::Get<ShopBackend::Rewriter, DetourHook<decltype(&ShopBackend::Rewriter)>>()->Original()(ctx, a2, a3, a4, payload);

		if (freeshop && !rewritten)
			rewritten = ShopJson::HuntAndRewrite(payload, ctx);

		if (freeshop)
		{
			if (rewritten)
			{
				LOG(INFO) << "[ShopBackend] Rewriter zeroed price/bank/wallet (#" << s_enters << ")";
			}
			else if (s_failDump < 6)
			{
				++s_failDump;
				LOG(INFO) << "[ShopBackend] Rewriter no-json #" << s_failDump << " — dump";
				LOG(INFO) << ShopJson::DumpToLine("payload", payload, 160);
				LOG(INFO) << ShopJson::DumpToLine("ctx", ctx, 160);
			}
		}

		if (freeshop && s_enters <= 12)
			LOG(INFO) << "[ShopBackend] Rewriter EXIT rewritten=" << rewritten << " result=" << result;

		return result;
	}
}
