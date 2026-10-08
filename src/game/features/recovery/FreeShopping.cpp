#include <array>
#include <cstdint>
#include <utility>

#include "core/commands/BoolCommand.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/netshop/CNetShopTransaction.hpp"
#include "types/netshop/netCatalogBaseItem.hpp"

namespace YimMenu::Features
{
	// Referenced by ShopBackend::CheckoutStart / Rewriter / HttpStartRequest.
	bool g_FreeShoppingEnabled = false;

	// Free Shopping — client-side basket flow implementation:
	//  - Free Shopping: covers store purchases (basket flow + NETWORK_BUY_*/NETWORK_DEDUCT_CASH).
	//
	// The real server transaction always fires (that is what records ownership on R*'s
	// backend); only the client-side money deduction is cancelled by zeroing the amount.

	// Layout of the script-side basket item struct (NETSHOPPING_BASKET_ITEM):
	//   0x00  uint64  PrimaryHash
	//   0x08  uint64  SecondaryHash
	//   0x10  uint64  Value (price)
	//   0x18  uint64  StatValue
#pragma pack(push, 1)
	struct ScrBasketItem
	{
		std::uint64_t m_PrimaryHash;
		std::uint64_t m_SecondaryHash;
		std::uint64_t m_Value;
		std::uint64_t m_StatValue;
	};
#pragma pack(pop)

	// Internal basket item object used inside CNetShopTransaction.
	// Offsets determined by reverse-engineering the basket container.
	struct CNetShopItem
	{
		char pad_0000[0x08];     // 0x00
		std::uint32_t m_Id;      // 0x08  primary catalog hash
		std::uint32_t m_ExtraId; // 0x0C  secondary / DLC hash
		std::uint32_t m_Qty;     // 0x10
		std::int32_t m_Price;    // 0x14
	};
	static_assert(sizeof(CNetShopItem) == 0x18);

	// Balance stat hashes that shop_controller checks to decide if you can afford something.
	static constexpr std::array<Hash, 6> sc_balance_stats = {
	    "MP0_CHAR_BANK_BALANCE_0"_J,
	    "MP1_CHAR_BANK_BALANCE_0"_J,
	    "MP0_WALLET_BALANCE"_J,
	    "MP1_WALLET_BALANCE"_J,
	    "BANK_BALANCE"_J,
	    "WALLET_BALANCE"_J,
	};

	// ─── forward declarations ────────────────────────────────────────────────
	static void NetGameserverBeginServiceHook(rage::scrNativeCallContext* ctx);
	static void NetGameserverCheckoutStartHook(rage::scrNativeCallContext* ctx);
	static void NetGameserverUseServerTransactionsHook(rage::scrNativeCallContext* ctx);
	static void NetGameserverBasketEndHook(rage::scrNativeCallContext* ctx);
	static void NetGameserverBasketAddItemHook(rage::scrNativeCallContext* ctx);
	static void StatGetIntHook(rage::scrNativeCallContext* ctx);
	static void NetworkCanSpendMoneyHook(rage::scrNativeCallContext* ctx);
	static void NetworkCanSpendMoney2Hook(rage::scrNativeCallContext* ctx);
	static void NetworkGetCanSpendFromWalletHook(rage::scrNativeCallContext* ctx);
	static void NetworkGetCanSpendFromBankHook(rage::scrNativeCallContext* ctx);
	static void NetworkGetCanSpendFromBankAndWalletHook(rage::scrNativeCallContext* ctx);
	static void NetworkDeductCashHook(rage::scrNativeCallContext* ctx);
	static void NetworkBuyItemHook(rage::scrNativeCallContext* ctx);
	static void NetworkBuyPropertyHook(rage::scrNativeCallContext* ctx);

	// ─── hook forward-declaration & definition macros ─────────────────────────
#define DECLARE_FREE_SHOPPING_HOOK(native_name) static void native_name##_Hook(rage::scrNativeCallContext* ctx);
#define FREE_SHOPPING_HOOK_ENTRY(native_name) {NativeIndex::native_name, &native_name##_Hook},

	// ─── individual NETWORK_BUY_* hooks (Free Shopping only) ─────────────────
	DECLARE_FREE_SHOPPING_HOOK(NETWORK_BUY_HEALTHCARE)
	DECLARE_FREE_SHOPPING_HOOK(NETWORK_BUY_AIRSTRIKE)
	DECLARE_FREE_SHOPPING_HOOK(NETWORK_BUY_HELI_STRIKE)
	DECLARE_FREE_SHOPPING_HOOK(NETWORK_BUY_BOUNTY)
	DECLARE_FREE_SHOPPING_HOOK(NETWORK_BUY_FAIRGROUND_RIDE)
	DECLARE_FREE_SHOPPING_HOOK(NETWORK_CASINO_BUY_CHIPS)

	// ─── per-native zero-price macro ────────────────────────────────────────
#define DEFINE_FREE_SHOPPING_HOOK(command, native_name)                                         \
	static void native_name##_Hook(rage::scrNativeCallContext* ctx)                               \
	{                                                                                             \
		if (command.GetState())                                                                   \
			ctx->SetArg<int>(0, 0);                                                               \
		NativeInvoker::GetNativeHandler(NativeIndex::native_name)(ctx);                           \
	}

	// ─── shared hook installation ────────────────────────────────────────────
	// Must be called once when the toggle is first enabled.
	static void InstallSharedHooks()
	{
		NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NET_GAMESERVER_BEGIN_SERVICE, &NetGameserverBeginServiceHook);
		NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NET_GAMESERVER_CHECKOUT_START, &NetGameserverCheckoutStartHook);
		NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NET_GAMESERVER_USE_SERVER_TRANSACTIONS, &NetGameserverUseServerTransactionsHook);
		NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NET_GAMESERVER_BASKET_END, &NetGameserverBasketEndHook);
		NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NET_GAMESERVER_BASKET_ADD_ITEM, &NetGameserverBasketAddItemHook);

		NativeHooks::AddHook("shop_controller"_J, NativeIndex::STAT_GET_INT, &StatGetIntHook);
		NativeHooks::AddHook("am_mp_property_int"_J, NativeIndex::STAT_GET_INT, &StatGetIntHook);

		NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_CAN_SPEND_MONEY, &NetworkCanSpendMoneyHook);
		NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_CAN_SPEND_MONEY2, &NetworkCanSpendMoney2Hook);
		NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_GET_CAN_SPEND_FROM_WALLET, &NetworkGetCanSpendFromWalletHook);
		NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_GET_CAN_SPEND_FROM_BANK, &NetworkGetCanSpendFromBankHook);
		NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_GET_CAN_SPEND_FROM_BANK_AND_WALLET, &NetworkGetCanSpendFromBankAndWalletHook);

		NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_DEDUCT_CASH, &NetworkDeductCashHook);
	}

	// ─── command classes ─────────────────────────────────────────────────────
	class FreeShopping : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			g_FreeShoppingEnabled = true;

			static auto hooked = []() {
				InstallSharedHooks();

				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_BUY_ITEM, &NetworkBuyItemHook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_BUY_PROPERTY, &NetworkBuyPropertyHook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_BUY_HEALTHCARE, &NETWORK_BUY_HEALTHCARE_Hook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_BUY_AIRSTRIKE, &NETWORK_BUY_AIRSTRIKE_Hook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_BUY_HELI_STRIKE, &NETWORK_BUY_HELI_STRIKE_Hook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_BUY_BOUNTY, &NETWORK_BUY_BOUNTY_Hook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_BUY_FAIRGROUND_RIDE, &NETWORK_BUY_FAIRGROUND_RIDE_Hook);
				NativeHooks::AddHook(NativeHooks::ALL_SCRIPTS, NativeIndex::NETWORK_CASINO_BUY_CHIPS, &NETWORK_CASINO_BUY_CHIPS_Hook);

				return true;
			}();

			LOG(INFO) << "[FreeShopping] enabled — ShopBackend Rewriter will zero outbound txn JSON";
		}

		virtual void OnDisable() override
		{
			g_FreeShoppingEnabled = false;
			LOG(INFO) << "[FreeShopping] disabled";
		}
	};

	static FreeShopping _FreeShopping{"freeshopping", "Free Shopping", "Buy items in the in-game store for free. The real transaction fires so the server records ownership, but the money deduction is cancelled client-side. Some server-validated items may still be rejected."};

	// ─── NET_GAMESERVER_BEGIN_SERVICE ────────────────────────────────────────
	// Do NOT zero the service price or stamp txnId=1337 — both broke server
	// validation / checkout (office trade-in). Affordability is spoofed via
	// STAT/CAN_SPEND; $0 only happens on the wire (Rewriter / HTTP JSON).
	// Always run the original so a real service transaction is created.
	static void NetGameserverBeginServiceHook(rage::scrNativeCallContext* ctx)
	{
		if (ctx->GetArg<int>(3) == -50712147)
			return ctx->SetReturnValue<BOOL>(FALSE);

		if (_FreeShopping.GetState())
		{
			auto category = ctx->GetArg<Hash>(1);
			auto item     = ctx->GetArg<Hash>(2);
			auto action   = ctx->GetArg<Hash>(3);
			auto* value   = ctx->GetArg<int*>(4);
			auto* txn     = ctx->GetArg<int*>(0);

			static int s_logged = 0;
			if (s_logged < 12)
			{
				++s_logged;
				LOG(INFO) << "[FreeShopping] BEGIN_SERVICE cat=0x" << std::hex << category
				          << " item=0x" << item << " act=0x" << action << std::dec
				          << " value=" << (value ? *value : -1)
				          << " txn=" << (txn ? *txn : -1);
			}
		}

		NativeInvoker::GetNativeHandler(NativeIndex::NET_GAMESERVER_BEGIN_SERVICE)(ctx);
	}

	// ─── NET_GAMESERVER_CHECKOUT_START ──────────────────────────────────────
	// Always forward to the original so the real checkout/submit runs and the
	// server records ownership. Log txn id + result for diagnosis.
	static void NetGameserverCheckoutStartHook(rage::scrNativeCallContext* ctx)
	{
		const auto txn_id = ctx->GetArg<int>(0);

		NativeInvoker::GetNativeHandler(NativeIndex::NET_GAMESERVER_CHECKOUT_START)(ctx);

		if (_FreeShopping.GetState())
		{
			static int s_logged = 0;
			if (s_logged < 8)
			{
				++s_logged;
				const auto result = *ctx->GetReturnValue<BOOL>();
				LOG(INFO) << "[FreeShopping] CHECKOUT_START txn=" << txn_id
				          << " result=" << static_cast<int>(result);
			}
		}
	}

	// ─── NET_GAMESERVER_USE_SERVER_TRANSACTIONS ──────────────────────────────
	// MUST stay TRUE when free shopping is on: returning FALSE disables the
	// server transaction path that records ownership. $0 pricing is handled by
	// ShopBackend::Rewriter / HTTP JSON rewrite on the wire, not by skipping
	// the server submit.
	static void NetGameserverUseServerTransactionsHook(rage::scrNativeCallContext* ctx)
	{
		NativeInvoker::GetNativeHandler(NativeIndex::NET_GAMESERVER_USE_SERVER_TRANSACTIONS)(ctx);
	}

	// ─── NET_GAMESERVER_BASKET_ADD_ITEM ──────────────────────────────────────
	// Do NOT zero the script basket Value or catalog price here. Client-side $0
	// made the server reject / skip the real txn (car never persisted). Keep
	// real prices through checkout; affordability is spoofed (STAT/CAN_SPEND);
	// $0 is applied only on outbound JSON (Rewriter / HTTP).
	static void NetGameserverBasketAddItemHook(rage::scrNativeCallContext* ctx)
	{
		static int s_logged = 0;
		if (_FreeShopping.GetState() && s_logged < 8)
		{
			++s_logged;
			auto* item_data = ctx->GetArg<std::uint64_t*>(0);
			const auto qty  = ctx->GetArg<int>(1);
			LOG(INFO) << "[FreeShopping] BASKET_ADD value="
			          << (item_data ? static_cast<std::int64_t>(item_data[2]) : -1)
			          << " qty=" << qty;
		}

		NativeInvoker::GetNativeHandler(NativeIndex::NET_GAMESERVER_BASKET_ADD_ITEM)(ctx);
	}

	// ─── NET_GAMESERVER_BASKET_END ───────────────────────────────────────────
	// Force a profile save so the $0 purchase is flushed to the server.
	static void NetGameserverBasketEndHook(rage::scrNativeCallContext* ctx)
	{
		NativeInvoker::GetNativeHandler(NativeIndex::NET_GAMESERVER_BASKET_END)(ctx);

		if (_FreeShopping.GetState())
			STATS::STAT_SAVE(0, 0, 3, 0);
	}

	// ─── STAT_GET_INT ────────────────────────────────────────────────────────
	// Spoof balance stats to INT32_MAX so the script always thinks you can
	// afford anything.
	static void StatGetIntHook(rage::scrNativeCallContext* ctx)
	{
		const auto stat_hash = ctx->GetArg<Hash>(0);
		auto* out            = ctx->GetArg<int*>(1);

		if ((_FreeShopping.GetState()) && out)
		{
			for (const auto& h : sc_balance_stats)
			{
				if (stat_hash == h)
				{
					*out = INT32_MAX;
					ctx->SetReturnValue<BOOL>(TRUE);
					return;
				}
			}
		}

		NativeInvoker::GetNativeHandler(NativeIndex::STAT_GET_INT)(ctx);
	}

	// ─── NETWORK_CAN_SPEND_MONEY / FROM_WALLET / FROM_BANK ──────────────────
	static void NetworkCanSpendMoneyHook(rage::scrNativeCallContext* ctx)
	{
		if (_FreeShopping.GetState())
			return ctx->SetReturnValue<BOOL>(TRUE);

		NativeInvoker::GetNativeHandler(NativeIndex::NETWORK_CAN_SPEND_MONEY)(ctx);
	}

	static void NetworkCanSpendMoney2Hook(rage::scrNativeCallContext* ctx)
	{
		if (_FreeShopping.GetState())
			return ctx->SetReturnValue<BOOL>(TRUE);

		NativeInvoker::GetNativeHandler(NativeIndex::NETWORK_CAN_SPEND_MONEY2)(ctx);
	}

	static void NetworkGetCanSpendFromWalletHook(rage::scrNativeCallContext* ctx)
	{
		if (_FreeShopping.GetState())
			return ctx->SetReturnValue<BOOL>(TRUE);

		NativeInvoker::GetNativeHandler(NativeIndex::NETWORK_GET_CAN_SPEND_FROM_WALLET)(ctx);
	}

	static void NetworkGetCanSpendFromBankHook(rage::scrNativeCallContext* ctx)
	{
		if (_FreeShopping.GetState())
			return ctx->SetReturnValue<BOOL>(TRUE);

		NativeInvoker::GetNativeHandler(NativeIndex::NETWORK_GET_CAN_SPEND_FROM_BANK)(ctx);
	}

	static void NetworkGetCanSpendFromBankAndWalletHook(rage::scrNativeCallContext* ctx)
	{
		if (_FreeShopping.GetState())
			return ctx->SetReturnValue<BOOL>(TRUE);

		NativeInvoker::GetNativeHandler(NativeIndex::NETWORK_GET_CAN_SPEND_FROM_BANK_AND_WALLET)(ctx);
	}

	// ─── NETWORK_DEDUCT_CASH ────────────────────────────────────────────────
	static void NetworkDeductCashHook(rage::scrNativeCallContext* ctx)
	{
		if (_FreeShopping.GetState())
			ctx->SetArg<int>(0, 0);

		NativeInvoker::GetNativeHandler(NativeIndex::NETWORK_DEDUCT_CASH)(ctx);
	}

	// ─── NETWORK_BUY_ITEM ───────────────────────────────────────────────────
	static void NetworkBuyItemHook(rage::scrNativeCallContext* ctx)
	{
		if (_FreeShopping.GetState())
			ctx->SetArg<int>(0, 0);

		NativeInvoker::GetNativeHandler(NativeIndex::NETWORK_BUY_ITEM)(ctx);
	}

	// ─── NETWORK_BUY_PROPERTY ───────────────────────────────────────────────
	static void NetworkBuyPropertyHook(rage::scrNativeCallContext* ctx)
	{
		if (_FreeShopping.GetState())
			ctx->SetArg<int>(0, 0);

		NativeInvoker::GetNativeHandler(NativeIndex::NETWORK_BUY_PROPERTY)(ctx);
	}

	DEFINE_FREE_SHOPPING_HOOK(_FreeShopping, NETWORK_BUY_HEALTHCARE)
	DEFINE_FREE_SHOPPING_HOOK(_FreeShopping, NETWORK_BUY_AIRSTRIKE)
	DEFINE_FREE_SHOPPING_HOOK(_FreeShopping, NETWORK_BUY_HELI_STRIKE)
	DEFINE_FREE_SHOPPING_HOOK(_FreeShopping, NETWORK_BUY_BOUNTY)
	DEFINE_FREE_SHOPPING_HOOK(_FreeShopping, NETWORK_BUY_FAIRGROUND_RIDE)
	DEFINE_FREE_SHOPPING_HOOK(_FreeShopping, NETWORK_CASINO_BUY_CHIPS)
}
