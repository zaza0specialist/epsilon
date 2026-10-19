# Epsilon

A private fork of [YimMenu v2](https://github.com/YimMenu/YimMenuV2) for GTA V: Enhanced, carrying our own interface theme and our own network protections.

Epsilon keeps the upstream YimMenu v2 codebase and adds three things to it:

- **The Epsilon theme** — a dark, resizable interface with an accent-coloured header, an icon sidebar, a two-column card grid with per-feature status badges, and iOS-style switches. Five themes are selectable; Epsilon is the default.
- **Network protections** — blocking for the script and net events used to grief, kick, spam and cash-drop abuse, with a reason recorded for every block.
- **Diagnostics** — a compatibility mode that blocks nothing but logs every event, plus a per-player leave summary reporting how long a player stayed and which protections intervened.

> This repository is private and for personal use. Modifying a networked game may violate the publisher's terms of service, and anti-cheat systems actively target modified clients. Use it at your own risk.

## Attribution

This is a derivative work of YimMenu v2, licensed under the GNU General Public License v2.0. The upstream project, its licence and its contributors remain the copyright holders of the original work, and this fork is distributed under the same licence. The full text is in [LICENSE](LICENSE).

Upstream: <https://github.com/YimMenu/YimMenuV2>

## Building

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

`build.bat` configures with CMake and compiles with Ninja. The result is `build/Epsilon.dll`.

## Using it

1. In the Rockstar Games Launcher, open Grand Theft Auto V: Enhanced and disable BattlEye in its settings. On Steam or Epic Games you may also need to pass `-nobattleye` on the command line.
2. Launch the game and inject `Epsilon.dll` at the main menu with an injector.
3. Press `INSERT` or `Ctrl+\` to open the menu.

Settings and logs are written to `%APPDATA%\Epsilon`.

The interface loads fonts from `%APPDATA%\Epsilon\fonts` at startup, falling back to Segoe UI when nothing is found. Dropping an `Inter` font file in that folder is enough to change it.

## Protections

Found under **Network → Protections**.

| Toggle | Default | What it does |
| --- | --- | --- |
| Block Kicks | on | Blocks remote kick script events (CEO ban, vehicle kick, network bail, kick from interior) |
| Block Griefing | on | Blocks forced teleports, cutscenes, spectate, bounty abuse, forced missions and similar grief events |
| Block Spam | on | Blocks sound spam, SMS and fake notifications, and rate-limits event floods |
| Block Cash Drops | on | Blocks forced money events (CEO money, fake cash spawn notifications) |
| Block Chat Ads | on | Hides chat messages containing links or advertisements |
| Log Net Events | off | Logs every received net game event to `cout.log` |
| Log Unknown Script Events | off | Logs the hash and payload of unrecognised script events, for capturing new kick vectors |
| Compatibility Mode | off | Blocks nothing, logs everything — use it to check whether a legitimate player is being dropped by our own protections |

### Reading the logs

`cout.log` records join and leave events, every blocked or logged event, and a summary line whenever a player disconnects:

```
Epicok87 left after 94s - 2 protection triggers (Explosion (targeted ped), Request Control (ped))
```

A leave with **no protection triggers** means nothing on our side interfered with that player, which is the quickest way to separate our protections from anything else.

## Known issues

- **BattlEye-enabled players can be dropped from a hosted session.** A peer with BattlEye enabled leaves a session roughly two minutes in. Our own protections are not involved, and the cause is still being investigated. Disable BattlEye on the other client, or host from a client that is not modified.
- **FSL is no longer usable.** It used to move account saves off the Rockstar servers, but it no longer functions. Progress made with it is only visible while it is active.
- **Public sessions desync every few minutes.** Without a working BattlEye bypass, legitimate hosts eventually remove a modified client.

## Licence

GNU General Public License v2.0. See [LICENSE](LICENSE).
