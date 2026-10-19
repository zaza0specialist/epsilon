# Contributing to Epsilon

Epsilon is a private fork of [YimMenu v2](https://github.com/YimMenu/YimMenuV2) for GTA V: Enhanced. This guide covers the workflow for this fork. For the upstream project's own conventions, see the [YimMenu contribution guide](https://github.com/YimMenu/YimMenuV2/blob/enhanced/CONTRIBUTING.md).

There are no external pull requests. This repository is private and work happens locally.

## What Epsilon changes relative to upstream

Epsilon keeps upstream's architecture and adds three things:

- **The Epsilon theme** (`src/core/frontend/manager/styles/Epsilon/`) — a fifth and default style, selectable from Settings → GUI → UI.
- **Network protections and diagnostics** (`src/game/features/network/Protections.cpp`, `src/game/backend/Protections.cpp`) — the blocking of grief, kick, spam and cash-drop events, plus the logging and the per-player leave summary.
- **Documentation** — this guide, the README, and the About section in Settings.

Everything else should be traceable to upstream. When you are unsure whether something is ours or theirs, `git log --oneline` on the branch tells you: our work is the commits above upstream's tip.

## Getting set up

Requirements:

- Windows 10/11 x64
- Visual Studio 2022 Build Tools (x64 toolset, C++ desktop workload)
- CMake 3.20 or newer
- Ninja

```bat
git clone <this repository>
cd epsilon
build.bat
```

`build.bat` configures with CMake and compiles with Ninja, producing `build/Epsilon.dll`. There is no separate configure step, and no dependency that has to be installed by hand.

The build is incremental — Ninja only recompiles what changed, so a normal edit-and-build cycle takes a few seconds.

## Working with upstream

Our branch shares ancestry with upstream, so taking upstream's changes is an ordinary merge:

```bat
git fetch upstream
git merge upstream/enhanced
```

Expect conflicts in `src/game/frontend/submenus/Recovery.cpp` and `src/game/features/recovery/FreeShopping.cpp` when upstream touches free shopping — resolve by taking upstream's version, since that is the one we track.

**Do not rewrite history that has been pushed.** A previous rewrite of this repository left us with no merge base and would have required `--allow-unrelated-histories` to pull upstream again. If history does need rewriting, say so first.

The tag `archive/pre-upstream-rebuild` marks the commit from before the branch was rebuilt on upstream's tip, and keeps the older commit history reachable.

## Code style

`.clang-format` is authoritative. It is based on the Microsoft style with tabs, so format the files you touch rather than the whole tree:

```bat
clang-format -i src/path/to/file.cpp
```

Reformatting files you are not otherwise changing creates noisy diffs against upstream, and upstream itself is currently inconsistent — some of the renderer files were rewritten with spaces in `#1158`.

Beyond formatting, follow upstream's conventions:

- Keep the `core/` versus `game/` split: `core/` is engine-agnostic, `game/` is game-specific.
- Implement new features as commands. `src/game/features/self/Godmode.cpp` is a `LoopedCommand` that runs every frame; `src/game/features/self/Suicide.cpp` is a plain `Command`.
- Use `static_cast` and `reinterpret_cast` rather than C-style casts.
- Use `std::string_view` for immutable string parameters.
- Use `std::to_array` for constexpr arrays instead of relying on deduction, so the build stays correct under Clang.
- Compile with Clang when you can, and fix the warnings it reports.

## What was removed, and why

Some upstream features were deliberately dropped. Do not reintroduce them without asking first:

- **Player kicks** — the whole `Player → Kick` submenu, including `FreemodeStateKick`, `HostKick`, `NullFunctionKick` and `ScriptHostKick`.
- **Toxic and troll actions** — `Blackscreen`, `CeoKick`, `KillLoopExploit`, `SendGooch`, `SendPhantomCar`, `SendSext`, `SetBounty`.
- **Forced teleports of other players** — `SendToInterior`, `SendToProperty`.
- **The `WriteNetArrayData` spoofing hook**, and with it the `NetArrayCachedDataPatch` byte patch, which nothing else uses. It existed to power the features above.
- **The free shopping `ShopBackend` hooks** (`CheckoutStart`, `Rewriter`) and the phone-based free shopping script. Upstream's own free shopping (`#1157`, fixed in `#1167`) is used instead.
- **The upstream GitHub workflows.** They build a `YimMenuV2` target that does not exist here, and the nightly job runs on a daily cron and publishes releases into this repository. Actions is disabled at the repository level for the same reason.

## Keeping attribution honest

Do not add tooling that analyses other projects' binaries, and do not strip attribution from work that is not ours. If a feature is based on someone's technique, say so in the commit message; if it is our own implementation, do not imply otherwise in a comment.

## Before you commit

- The build completes without errors, and you have not introduced new warnings.
- The menu opens and the affected screen renders. If you touched the theme, check it in the Epsilon style *and* in one of the others — the other themes use the original renderer and are a good way to catch a change that only works in one path.
- If you touched protections, re-read the behaviour in `src/game/hooks/Network/HandleNetGameEvent.cpp` for the case you changed, including the `prot_compat` path, which blocks nothing and exists so that legitimate players are not broken by our own checks.
- The log at `%APPDATA%\Epsilon\cout.log` is clean of anything you did not intend to log.

## Commit messages

One logical change per commit, and a message that says what changed and why:

```
protections: block CEO money events from players in the same crew
Epsilon: draw the card grid at two columns on narrow windows
docs: document the leave summary format
```

The prefix convention comes from upstream: `feat:`, `fix:`, and a short scope for everything else.

## Reporting problems

Open an issue in this repository with:

- what you did,
- what you expected,
- what happened instead,
- the relevant part of `%APPDATA%\Epsilon\cout.log`.

For a player who is dropped from a session, the leave summary line is the most useful thing to include — it reports how long they stayed and which protections intervened, if any.
