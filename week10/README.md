# In Cave Danger

## Project Description

In Cave Danger is a text-based interactive story game written in C++. The player is an escaped convict running from the police. After finding a cave, the player must survive random cave events, manage health and fatigue, solve an ancient door puzzle, and reach an underground civilization to escape.

## How to Compile

Open the terminal in the project folder and run:

```bash
g++ -std=c++17 -Wall final-story_game.cpp -o story_game
```

## How to Run

After compiling, run:

```bash
./story_game
```

## How to Play

The game gives numbered choices at each scene. Type the number for the action you want and press Enter.

Blank input, spaces-only input, letters, and numbers outside the allowed range are rejected. The game will keep asking until a valid choice is entered.

The player must manage:

* Health
* Fatigue
* Police Heat
* Inventory items
* Puzzle progress

Resting lowers fatigue, but it also increases Police Heat. If Police Heat gets too high, the police catch up.

## Goal

Reach the underground civilization and accept their help before health reaches 0, fatigue reaches 100, or Police Heat reaches the limit.

## Gameplay Features

* Random cave events
* Up to 10 scenes per run
* Not every event appears in every playthrough
* Random health loss in danger scenes
* Multiple possible endings
* Inventory system
* Rest system
* Ancient door puzzle using a clue from `story.txt`

## Win Condition

The player wins by surviving the cave, solving the ancient door puzzle, and escaping with help from the underground civilization.

## Loss Conditions

The player can lose by:

* Refusing to enter the cave
* Losing all health
* Becoming too exhausted
* Letting the police catch up
* Refusing the final safe escape route

## Files Included

* `final-story_game.cpp` - main C++ source file
* `story.txt` - text file read by the game for the puzzle clue
* `README.md` - project instructions and feature list

## File Created When Running

* `game_summary.txt` - created by the game after reaching an ending

## C++ Features Used

This project includes:

* Variables using multiple data types, including `int`, `bool`, `string`, and `double`
* `if/else` conditionals
* `switch` statement for game states
* Loops for input validation and the main game loop
* Functions that return values
* Void functions
* Functions with parameters
* `vector` for inventory and cave events
* `struct` for player data and cave event data
* `enum class` for game states
* File reading with `ifstream`
* File writing with `ofstream`
* Error handling for missing or failed files
* `auto` with a lambda function
* Range-based `for` loop
* Random events using `<random>`
* `std::shuffle` for event randomization

## Required Input File

The game reads from:

```txt
story.txt
```

The file should contain the clue for the ancient door puzzle. Example:

```txt
Only the symbol of the moon opens the path below.
```

## Notes

The game is designed so that each run can be different. Randomized cave events mean the player may not see every possible event in one playthrough.
