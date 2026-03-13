# Space Rangers: Alien Invasion

A console-based 2D space shooter built in C++ for Windows.

In this game, you control a spaceship, dodge incoming hazards, collect stars and crates, fight enemy ships, and face a boss in later levels.

## Gameplay Overview

- Survive asteroid and enemy waves.
- Shoot enemies to increase score and progress levels.
- Collect stars for score bonuses.
- Interact with crates and life system.
- Defeat the boss to complete the game.

## Features

- ASCII-rendered game map in terminal/console
- Multiple levels with increasing difficulty
- Enemy movement and enemy bullet system
- Boss battle phase with health and boss bullets
- Pause menu and game-over/completion screens

## Controls

### Main Menu

- `1` = Play game
- `2` = Instructions
- `3` = High scores
- `4` = Exit

### In Game

- `A` = Move left
- `D` = Move right
- `W` = Move up (limited range)
- `S` = Move down
- `Space` = Shoot
- `J` = Jump upward
- `Esc` = Pause game
- `Q` = Quit game loop

## Tech Stack

- Language: `C++`
- Compiler: `g++` (MSYS2 UCRT)
- Platform: `Windows`
- Libraries/Headers: `iostream`, `conio.h`, `windows.h`, `cstdlib`, `ctime`, `string`

## Project Structure

```text
PF_Project/
|- game.cpp
|- README.md
|- .vscode/
	|- tasks.json
	|- launch.json
```

## Build and Run (VS Code)

This project is configured for MSYS2 UCRT (`C:/msys64/ucrt64/bin/g++.exe`).

1. Open the project in VS Code.
2. Use `Terminal > Run Task...`
3. Select: `Build and Run game.exe (MSYS2 runtime)`

This task will:

- Compile `game.cpp` to `game.exe`
- Launch the game with required MSYS2 runtime path

## Debug (VS Code)

Use `F5` and select:

- `Debug game.exe (MSYS2)`

## Notes

- If build fails with `Permission denied` on `game.exe`, close any running game instance and build again.
- This is a terminal-based game, so best experience is in a standard console window.

## Author

- Faseeh Ur Rehman Asghar

## License

This project is for educational use.
