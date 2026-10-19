#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "game/pointers/Pointers.hpp"

// Ported from reference/Ultimate_Menu_V3_1.73_Legacy.lua (Collectibles menu)
namespace YimMenu::Features
{
	static bool InSession()
	{
		return *Pointers.IsSessionStarted;
	}

	class UnlockActionFigures : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!InSession())
				return;
			for (int i = 0; i <= 99; i++)
				Stats::SetBool("MPX_PROP_FIGURE_" + std::to_string(i), true);
		}
	};

	class UnlockSignalJammers : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!InSession())
				return;
			for (int i = 0; i <= 49; i++)
				Stats::SetBool("MPX_JAMMER_IDENTIFIED_" + std::to_string(i), true);
		}
	};

	class UnlockPlayingCards : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!InSession())
				return;
			for (int i = 0; i <= 53; i++)
				Stats::SetBool("MPX_CH_CARD_ID_" + std::to_string(i), true);
		}
	};

	class UnlockSolomonProps : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!InSession())
				return;
			for (int i = 0; i <= 9; i++)
				Stats::SetBool("MPX_PROP_HIDDEN_SOL_ID_" + std::to_string(i), true);
		}
	};

	class UnlockMovieProps : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!InSession())
				return;
			for (int i = 1; i <= 10; i++)
				Stats::SetInt("MPX_MOVIE_PROP_COLLECTED_" + std::to_string(i), -1);
		}
	};

	class UnlockLdOrganics : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!InSession())
				return;
			for (int i = 0; i <= 99; i++)
				Stats::SetBool("MPX_LD_ORGANIC_COLLECTED_" + std::to_string(i), true);
		}
	};

	class UnlockGhostExposed : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!InSession())
				return;
			for (int i = 0; i <= 9; i++)
				Stats::SetBool("MPX_GHOST_EXPOSED_" + std::to_string(i), true);
		}
	};

	class UnlockAllCollectibles : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!InSession())
				return;
			for (int i = 0; i <= 99; i++)
				Stats::SetBool("MPX_PROP_FIGURE_" + std::to_string(i), true);
			for (int i = 0; i <= 49; i++)
				Stats::SetBool("MPX_JAMMER_IDENTIFIED_" + std::to_string(i), true);
			for (int i = 0; i <= 53; i++)
				Stats::SetBool("MPX_CH_CARD_ID_" + std::to_string(i), true);
			for (int i = 0; i <= 9; i++)
				Stats::SetBool("MPX_PROP_HIDDEN_SOL_ID_" + std::to_string(i), true);
			for (int i = 1; i <= 10; i++)
				Stats::SetInt("MPX_MOVIE_PROP_COLLECTED_" + std::to_string(i), -1);
			for (int i = 0; i <= 99; i++)
				Stats::SetBool("MPX_LD_ORGANIC_COLLECTED_" + std::to_string(i), true);
			for (int i = 0; i <= 9; i++)
				Stats::SetBool("MPX_GHOST_EXPOSED_" + std::to_string(i), true);
		}
	};

	static UnlockActionFigures _unlockactionfigures{"unlockactionfigures", "Action Figures", "Marks all 100 action figures as collected"};
	static UnlockSignalJammers _unlocksignaljammers{"unlocksignaljammers", "Signal Jammers", "Marks all 50 signal jammers as destroyed"};
	static UnlockPlayingCards _unlockplayingcards{"unlockplayingcards", "Playing Cards", "Marks all 54 playing cards as collected"};
	static UnlockSolomonProps _unlockprops{"unlockprops", "Solomon Movie Props", "Marks all hidden Solomon props as collected"};
	static UnlockMovieProps _unlockmovieprops{"unlockmovieprops", "Movie Props (LS Patriots)", "Marks all movie props as collected"};
	static UnlockLdOrganics _unlockldorganics{"unlockldorganics", "LD Organics Products", "Marks all LD Organics products as collected"};
	static UnlockGhostExposed _unlockghost{"unlockghost", "Ghost Exposed", "Marks all Ghost Exposed sites as found"};
	static UnlockAllCollectibles _unlockallcollectibles{"unlockallcollectibles", "Unlock All Collectibles", "Completes every collectible set at once"};
}
