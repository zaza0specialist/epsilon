#include "Hooking.hpp"

#include "BaseHook.hpp"
#include "DetourHook.hpp"
#include "VMTHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"

#include <cstdio>

namespace YimMenu
{
	Hooking::Hooking()
	{
		BaseHook::Add<Hooks::RawInput::GetRawInputData>(new DetourHook("GetRawInputData", reinterpret_cast<void*>(GetProcAddress(LoadLibraryA("user32.dll"), "GetRawInputData")), Hooks::RawInput::GetRawInputData));

		// BaseHook::Add<Hooks::Anticheat::QueueDependency>(new DetourHook("QueueDependency", Pointers.QueueDependency, Hooks::Anticheat::QueueDependency));
		BaseHook::Add<Hooks::Anticheat::GameSkeletonUpdate>(new DetourHook("GameSkeletonUpdate", Pointers.GameSkeletonUpdate, Hooks::Anticheat::GameSkeletonUpdate));
		BaseHook::Add<Hooks::Anticheat::PrepareMetricForSending>(new DetourHook("PrepareMetricForSending", Pointers.PrepareMetricForSending, Hooks::Anticheat::PrepareMetricForSending));
		BaseHook::Add<Hooks::Anticheat::GetThreadContext>(new DetourHook("GetThreadContext", reinterpret_cast<void*>(GetProcAddress(LoadLibraryA("kernel32.dll"), "GetThreadContext")), Hooks::Anticheat::GetThreadContext));
		BaseHook::Add<Hooks::Anticheat::HttpStartRequest>(new DetourHook("HttpStartRequest", Pointers.HttpStartRequest, Hooks::Anticheat::HttpStartRequest));
		BaseHook::Add<Hooks::Anticheat::BattlEyeServerProcessPlayerJoin>(new DetourHook("BattlEyeServerProcessPlayerJoin", Pointers.BattlEyeServerProcessPlayerJoin, Hooks::Anticheat::BattlEyeServerProcessPlayerJoin));
		BaseHook::Add<Hooks::Anticheat::GetAnticheatInitializedHash>(new DetourHook("GetAnticheatInitializedHash", Pointers.GetAnticheatInitializedHash, Hooks::Anticheat::GetAnticheatInitializedHash));
		BaseHook::Add<Hooks::Anticheat::GetAnticheatInitializedHash2>(new DetourHook("GetAnticheatInitializedHash2", Pointers.GetAnticheatInitializedHash2, Hooks::Anticheat::GetAnticheatInitializedHash2));

		BaseHook::Add<Hooks::Script::RunScriptThreads>(new DetourHook("RunScriptThreads", Pointers.RunScriptThreads, Hooks::Script::RunScriptThreads));
		BaseHook::Add<Hooks::Script::InitNativeTables>(new DetourHook("InitNativeTables", Pointers.InitNativeTables, Hooks::Script::InitNativeTables));
		BaseHook::Add<Hooks::Script::ScriptVM>(new DetourHook("ScriptVM", reinterpret_cast<void*>(Pointers.ScriptVM), Hooks::Script::ScriptVM));

		BaseHook::Add<Hooks::Info::AssignPhysicalIndex>(new DetourHook("AssignPhysicalIndex", Pointers.AssignPhysicalIndex, Hooks::Info::AssignPhysicalIndex));
		BaseHook::Add<Hooks::Info::NetworkPlayerMgrShutdown>(new DetourHook("NetworkPlayerMgrShutdown", Pointers.NetworkPlayerMgrShutdown, Hooks::Info::NetworkPlayerMgrShutdown));

		BaseHook::Add<Hooks::Network::ReceiveNetMessage>(new DetourHook("ReceiveNetMessage", Pointers.ReceiveNetMessage, Hooks::Network::ReceiveNetMessage));

		BaseHook::Add<Hooks::Spoofing::IsNodeInScope>(new DetourHook("IsNodeInScope", Pointers.IsNodeInScope, Hooks::Spoofing::IsNodeInScope));
		BaseHook::Add<Hooks::Spoofing::ShouldUseNodeCache>(new DetourHook("ShouldUseNodeCache", Pointers.ShouldUseNodeCache, Hooks::Spoofing::ShouldUseNodeCache));
		BaseHook::Add<Hooks::Spoofing::WriteNetArrayData>(new DetourHook("WriteNetArrayData", Pointers.WriteNetArrayData, Hooks::Spoofing::WriteNetArrayData));
		BaseHook::Add<Hooks::Spoofing::WriteNodeData>(new DetourHook("WriteNodeData", Pointers.WriteNodeData, Hooks::Spoofing::WriteNodeData));
		BaseHook::Add<Hooks::Spoofing::WriteSyncTree>(new DetourHook("WriteSyncTree", Pointers.WriteSyncTree, Hooks::Spoofing::WriteSyncTree));

		BaseHook::Add<Hooks::Network::GetPoolType>(new DetourHook("GetPoolType", Pointers.GetPoolType, Hooks::Network::GetPoolType));
		BaseHook::Add<Hooks::Network::GetDLCHash>(new DetourHook("GetDLCHash", Pointers.GetDLCHash, Hooks::Network::GetDLCHash));

		BaseHook::Add<Hooks::Matchmaking::MatchmakingAdvertise>(new DetourHook("MatchmakingAdvertise", Pointers.MatchmakingAdvertise, Hooks::Matchmaking::MatchmakingAdvertise));
		BaseHook::Add<Hooks::Matchmaking::MatchmakingSessionDetailSendResponse>(new DetourHook("MatchmakingSessionDetailSendResponse", Pointers.MatchmakingSessionDetailSendResponse, Hooks::Matchmaking::MatchmakingSessionDetailSendResponse));
		BaseHook::Add<Hooks::Matchmaking::MatchmakingUnadvertise>(new DetourHook("MatchmakingUnadvertise", Pointers.MatchmakingUnadvertise, Hooks::Matchmaking::MatchmakingUnadvertise));
		BaseHook::Add<Hooks::Matchmaking::MatchmakingUpdate>(new DetourHook("MatchmakingUpdate", Pointers.MatchmakingUpdate, Hooks::Matchmaking::MatchmakingUpdate));

		BaseHook::Add<Hooks::Misc::AssistedAimShouldReleaseEntity>(new DetourHook("AssistedAimShouldReleaseEntity", Pointers.AssistedAimShouldReleaseEntity, Hooks::Misc::AssistedAimShouldReleaseEntity));

		LOG(INFO) << "ShopCheckoutStartTarget: " << Pointers.ShopCheckoutStartTarget;
		LOG(INFO) << "ShopRewriterTarget: " << Pointers.ShopRewriterTarget;
		auto logTargetBytes = [](const char* name, void* p) {
			if (!p)
			{
				LOG(INFO) << name << " bytes: NULL";
				return;
			}
			auto* b = static_cast<const unsigned char*>(p);
			char hex[64];
			std::snprintf(hex, sizeof(hex), "%02X %02X %02X %02X %02X %02X %02X %02X",
			    b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
			LOG(INFO) << name << " bytes: " << hex << " (first=" << (b[0] == 0xE9 ? "E9" : "not-E9") << ")";
		};
		logTargetBytes("ShopCheckoutStartTarget", Pointers.ShopCheckoutStartTarget);
		logTargetBytes("ShopRewriterTarget", Pointers.ShopRewriterTarget);
		// Enhanced RVAs (see Pointers.cpp). Rewriter rewrites outbound txn JSON to $0
		// so R*'s backend records ownership; CheckoutStart must always call original.
		if (Pointers.ShopCheckoutStartTarget)
			BaseHook::Add<Hooks::ShopBackend::CheckoutStart>(new DetourHook("ShopCheckoutStart", Pointers.ShopCheckoutStartTarget, Hooks::ShopBackend::CheckoutStart));
		if (Pointers.ShopRewriterTarget)
			BaseHook::Add<Hooks::ShopBackend::Rewriter>(new DetourHook("ShopRewriter", Pointers.ShopRewriterTarget, Hooks::ShopBackend::Rewriter));
	}

	Hooking::~Hooking()
	{
		DestroyImpl();
	}

	bool Hooking::Init()
	{
		return GetInstance().InitImpl();
	}

	void Hooking::Destroy()
	{
		GetInstance().DestroyImpl();
		BytePatches::RestoreAll();
	}

	bool Hooking::InitImpl()
	{
		BaseHook::EnableAll();
		const auto st = m_MinHook.ApplyQueued();
		LOG(INFO) << "MH_ApplyQueued status=" << static_cast<int>(st)
		          << (st == MH_OK ? " (OK)" : " (FAILED - hooks may be inactive!)");

		return st == MH_OK;
	}

	void Hooking::DestroyImpl()
	{
		BaseHook::DisableAll();
		m_MinHook.ApplyQueued();

		for (auto it : BaseHook::Hooks())
		{
			delete it;
		}
		BaseHook::Hooks().clear();
	}
}