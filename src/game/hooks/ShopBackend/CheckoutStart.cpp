#include "common.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Features
{
	extern bool g_FreeShoppingEnabled;
}

namespace YimMenu::Hooks
{
	bool ShopBackend::CheckoutStart(void* a1, unsigned int txnId)
	{
		// Always log entry (rate-limited) so we can tell "never called" from "called".
		static int s_enters = 0;
		if (s_enters < 8)
		{
			++s_enters;
			LOG(INFO) << "[ShopBackend] CheckoutStart ENTER #" << s_enters
			          << " a1=" << a1 << " txnId=" << txnId
			          << " freeshop=" << Features::g_FreeShoppingEnabled;
		}

		// Always forward to the original so the real checkout/submit runs and
		// ownership is recorded. (txnId==1337 bypass skipped the server submit
		// on service/property txns — office trade-in failed.)
		auto result = BaseHook::Get<ShopBackend::CheckoutStart, DetourHook<decltype(&ShopBackend::CheckoutStart)>>()->Original()(a1, txnId);

		if (Features::g_FreeShoppingEnabled)
			LOG(INFO) << "[ShopBackend] CheckoutStart EXIT txnId=" << txnId << " result=" << static_cast<int>(result);

		return result;
	}
}
