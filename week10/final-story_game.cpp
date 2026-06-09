/*
 * Interactive Story Game - In Cave Danger
 * Author: Dillan Widmar
 * Date: June 8, 2026
 *
 * ==== Project Features ====
 * Variables (3+ types): Lines 46-55, 372-379
 * If/else: Lines 94-124, 419-460, 491-507
 * Switch: Line 402
 * Loop: Lines 89-125, 140-142, 155-160, 386-390, 392-557
 * Function w/ return value: Lines 66-74, 76-81, 83-126
 * Void function: Lines 132-143, 169-189, 191-196
 * Function w/ parameters: Lines 83, 128, 132, 169, 215, 265
 * Vector or array: Lines 54, 308-309, 376
 * Struct or class: Lines 45-64
 * Enum: Lines 35-43
 * File reading: Lines 145-167
 * File writing: Lines 169-189
 * Modern feature 1 (lambda): Lines 85-87
 * Modern feature 2 (range-based for): Lines 140-142, 186-188
 * ==========================
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class GameState {
    INTRO,
    FOREST_ESCAPE,
    CAVE_ENTRANCE,
    RANDOM_EVENTS,
    PUZZLE_CHAMBER,
    UNDERGROUND_CITY,
    END_GAME
};

struct Player {
    string name;
    int health = 100;
    int fatigue = 0;
    int policeHeat = 0;
    int scenesCompleted = 0;
    double escapeChance = 0.50;
    bool hasTorch = false;
    bool solvedPuzzle = false;
    vector<string> inventory;
    string ending = "No ending";
};

struct CaveEvent {
    string title;
    string description;
    string optionOne;
    string optionTwo;
    string rewardItem;
};

string trim(const string& text) {
    size_t first = text.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }

    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

int randomNumber(int minValue, int maxValue) {
    static random_device seed;
    static mt19937 generator(seed());
    uniform_int_distribution<int> distribution(minValue, maxValue);
    return distribution(generator);
}

int getChoice(int minChoice, int maxChoice) {
    string input;
    auto isValidChoice = [minChoice, maxChoice](int choice) {
        return choice >= minChoice && choice <= maxChoice;
    };

    while (true) {
        cout << "Enter choice (" << minChoice << "-" << maxChoice << "): ";
        getline(cin, input);
        input = trim(input);

        if (input.empty()) {
            cout << "Blank input is not allowed.\n";
            continue;
        }

        bool onlyDigits = true;
        for (char ch : input) {
            if (!isdigit(static_cast<unsigned char>(ch))) {
                onlyDigits = false;
                break;
            }
        }

        if (!onlyDigits) {
            cout << "Enter numbers only.\n";
            continue;
        }

        int choice = 0;
        try {
            choice = stoi(input);
        } catch (...) {
            cout << "That number is not valid.\n";
            continue;
        }

        if (isValidChoice(choice)) {
            return choice;
        }

        cout << "Choice out of range.\n";
    }
}

bool hasItem(const Player& player, const string& itemName) {
    return find(player.inventory.begin(), player.inventory.end(), itemName) != player.inventory.end();
}

void printInventory(const vector<string>& inventory) {
    cout << "\nInventory:\n";

    if (inventory.empty()) {
        cout << "- Empty\n";
        return;
    }

    for (const auto& item : inventory) {
        cout << "- " << item << '\n';
    }
}

string readPuzzleClue(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: could not open " << filename << ". Using backup clue.\n";
        return "Only the symbol of the moon opens the path below.";
    }

    string line;
    string clue;

    while (getline(file, line)) {
        line = trim(line);
        if (!line.empty()) {
            clue += line + " ";
        }
    }

    if (clue.empty()) {
        return "Only the symbol of the moon opens the path below.";
    }

    return clue;
}

void writeSummary(const Player& player, const string& filename) {
    ofstream out(filename);
    if (!out) {
        cerr << "Error: could not write summary.\n";
        return;
    }

    out << "In Cave Danger - Game Summary\n";
    out << "Player: " << player.name << '\n';
    out << "Ending: " << player.ending << '\n';
    out << "Health: " << player.health << '\n';
    out << "Fatigue: " << player.fatigue << '\n';
    out << "Police Heat: " << player.policeHeat << '\n';
    out << "Scenes Completed: " << player.scenesCompleted << '\n';
    out << "Escape Chance: " << player.escapeChance << '\n';
    out << "Inventory:\n";

    for (const auto& item : player.inventory) {
        out << "- " << item << '\n';
    }
}

void showStatus(const Player& player) {
    cout << "\nStatus: Health " << player.health
         << " | Fatigue " << player.fatigue
         << " | Police Heat " << player.policeHeat << "/4\n";
}

void addItem(Player& player, const string& itemName) {
    if (!itemName.empty() && !hasItem(player, itemName)) {
        player.inventory.push_back(itemName);
        cout << "Item gained: " << itemName << "\n";
    }
}

void clampPlayerStats(Player& player) {
    if (player.health > 100) {
        player.health = 100;
    }

    if (player.fatigue < 0) {
        player.fatigue = 0;
    }
}

void randomHealthLoss(Player& player, int minLoss, int maxLoss, const string& reason) {
    int damage = randomNumber(minLoss, maxLoss);

    if (damage > 0) {
        cout << reason << " Health lost: " << damage << ".\n";
        player.health -= damage;
    } else {
        cout << reason << " You avoid injury this time.\n";
    }
}

void rest(Player& player) {
    cout << "\nYou hide in the dark and rest for a few minutes.\n";
    int recovery = randomNumber(15, 30);
    player.fatigue -= recovery;
    player.policeHeat++;
    clampPlayerStats(player);
    cout << "Fatigue lowered by " << recovery << ", but the police are closer now.\n";
}

bool checkLoss(Player& player) {
    if (player.health <= 0) {
        player.ending = "Lost: the cave injuries were too much to survive.";
        return true;
    }

    if (player.policeHeat >= 4) {
        player.ending = "Lost: the police caught up before the escape was complete.";
        return true;
    }

    if (player.fatigue >= 100) {
        player.ending = "Lost: exhaustion caused collapse in the cave.";
        return true;
    }

    return false;
}

void printTitleArt() {
    cout << "====================================\n";
    cout << "           IN CAVE DANGER           \n";
    cout << "====================================\n";
}

void finishScene(Player& player) {
    player.scenesCompleted++;
    clampPlayerStats(player);
}

bool runCaveEvent(Player& player, const CaveEvent& event) {
    showStatus(player);
    cout << "\nScene " << player.scenesCompleted + 1 << ": " << event.title << "\n";
    cout << event.description << "\n";
    cout << "1. " << event.optionOne << "\n";
    cout << "2. " << event.optionTwo << "\n";
    cout << "3. Rest before choosing\n";

    int choice = getChoice(1, 3);

    if (choice == 3) {
        rest(player);
        return false;
    }

    bool goodOutcome = randomNumber(1, 100) <= 65;

    if (choice == 1 && goodOutcome) {
        cout << "\nYour first plan works. You move through the danger carefully.\n";
        randomHealthLoss(player, 0, 8, "The scene still leaves scrapes and bruises.");
        player.fatigue += randomNumber(8, 18);
        player.escapeChance += 0.05;
        addItem(player, event.rewardItem);
    } else if (choice == 2 && !goodOutcome) {
        cout << "\nYour second plan fails and the cave punishes the mistake.\n";
        randomHealthLoss(player, 5, 18, "The failed move hurts badly.");
        player.fatigue += randomNumber(15, 28);
        player.policeHeat += randomNumber(0, 1);
    } else {
        cout << "\nYou survive, but the path costs time and energy.\n";
        randomHealthLoss(player, 1, 12, "The cave catches you off guard.");
        player.fatigue += randomNumber(10, 22);
    }

    if (player.hasTorch && randomNumber(1, 100) <= 30) {
        cout << "The torch helps you avoid the worst part of the path.\n";
        player.fatigue -= 5;
    }

    finishScene(player);
    return true;
}

vector<CaveEvent> buildCaveEvents() {
    vector<CaveEvent> events = {
        {
            "Cracked Bridge",
            "A broken stone bridge crosses a black pit. Loose rocks fall into darkness below.",
            "Cross quickly before it collapses",
            "Test each stone before stepping",
            "Bridge shard"
        },
        {
            "Underground River",
            "Cold water blocks the tunnel, and the current is stronger than it looks.",
            "Swim across now",
            "Search the wall for a narrow ledge",
            "Wet map scrap"
        },
        {
            "Bone Hall",
            "Old bones cover the floor. Some are arranged like warning arrows.",
            "Follow the bone arrows",
            "Ignore the bones and follow the wind",
            "Carved bone marker"
        },
        {
            "Echo Maze",
            "Every sound repeats from three different tunnels, including distant police radios.",
            "Follow the loudest echo",
            "Follow the quietest tunnel",
            "Echo stone"
        },
        {
            "Crystal Hive",
            "Glowing crystals cover the walls. Touching them could help or hurt.",
            "Break off a glowing crystal",
            "Keep your hands away and move slowly",
            "Glow crystal"
        },
        {
            "Old Campsite",
            "A burned-out campsite sits beside the tunnel. Someone survived here before.",
            "Search the ashes for supplies",
            "Leave fast before wasting time",
            "Rusted canteen"
        },
        {
            "Falling Stairway",
            "A stone stairway shakes each time you step. Dust pours from the ceiling.",
            "Run up the stairs",
            "Crawl along the side wall",
            "Stone stair chip"
        },
        {
            "Silent Shrine",
            "A small shrine has a cracked bowl, old coins, and a warning carved in stone.",
            "Take one coin as proof",
            "Leave the shrine untouched",
            "Ancient coin"
        }
    };

    shuffle(events.begin(), events.end(), mt19937(random_device{}()));
    return events;
}

int main() {
    Player player;
    GameState state = GameState::INTRO;
    string puzzleClue = readPuzzleClue("story.txt");
    vector<CaveEvent> caveEvents = buildCaveEvents();
    int eventsToPlay = randomNumber(3, 6);
    int currentEventIndex = 0;
    bool running = true;

    printTitleArt();
    cout << "Enter your character name: ";
    getline(cin, player.name);
    player.name = trim(player.name);

    while (player.name.empty()) {
        cout << "Name cannot be blank. Enter your character name: ";
        getline(cin, player.name);
        player.name = trim(player.name);
    }

    while (running) {
        if (checkLoss(player)) {
            state = GameState::END_GAME;
        }

        if (player.scenesCompleted >= 10 && state != GameState::END_GAME) {
            player.ending = "Lost: too much time passed in the cave and the police reached the exit.";
            state = GameState::END_GAME;
        }

        switch (state) {
            case GameState::INTRO: {
                cout << "\nYou are an escaped convict sprinting through the forest.\n";
                cout << "Sirens echo behind you. Rain turns the dirt road into mud.\n";
                cout << "A cave opens in the side of a cliff.\n";
                state = GameState::FOREST_ESCAPE;
                break;
            }

            case GameState::FOREST_ESCAPE: {
                showStatus(player);
                cout << "\nScene " << player.scenesCompleted + 1 << ": Forest Escape\n";
                cout << "1. Enter the cave\n";
                cout << "2. Stay on the road and keep running\n";

                int choice = getChoice(1, 2);

                if (choice == 1) {
                    cout << "\nYou duck into the cave before the searchlights reach the trees.\n";
                    randomHealthLoss(player, 0, 6, "Branches and sharp stone scrape you during the escape.");
                    player.fatigue += randomNumber(10, 20);
                    player.escapeChance += 0.10;
                    finishScene(player);
                    state = GameState::CAVE_ENTRANCE;
                } else {
                    cout << "\nYou stay on the road. A spotlight locks onto you.\n";
                    player.ending = "Lost: caught after refusing the cave.";
                    finishScene(player);
                    state = GameState::END_GAME;
                }
                break;
            }

            case GameState::CAVE_ENTRANCE: {
                showStatus(player);
                cout << "\nScene " << player.scenesCompleted + 1 << ": Cave Entrance\n";
                cout << "The cave smells like wet stone. Something wooden lies near the wall.\n";
                cout << "1. Pick up the old torch\n";
                cout << "2. Rush deeper into the cave\n";
                cout << "3. Rest before moving deeper\n";

                int choice = getChoice(1, 3);

                if (choice == 1) {
                    cout << "\nYou take the torch. It may help you see traps.\n";
                    player.hasTorch = true;
                    addItem(player, "Old torch");
                    randomHealthLoss(player, 0, 5, "The rough cave entrance cuts your hands.");
                    player.fatigue += randomNumber(8, 16);
                    finishScene(player);
                    state = GameState::RANDOM_EVENTS;
                } else if (choice == 2) {
                    cout << "\nYou rush forward without checking the cave entrance.\n";
                    randomHealthLoss(player, 4, 14, "Running blind makes the entrance dangerous.");
                    player.fatigue += randomNumber(18, 30);
                    finishScene(player);
                    state = GameState::RANDOM_EVENTS;
                } else {
                    rest(player);
                }
                break;
            }

            case GameState::RANDOM_EVENTS: {
                if (currentEventIndex >= eventsToPlay) {
                    state = GameState::PUZZLE_CHAMBER;
                    break;
                }

                bool completed = runCaveEvent(player, caveEvents.at(currentEventIndex));

                if (completed) {
                    currentEventIndex++;
                }
                break;
            }

            case GameState::PUZZLE_CHAMBER: {
                showStatus(player);
                cout << "\nScene " << player.scenesCompleted + 1 << ": Ancient Door Puzzle\n";
                cout << "A sealed door blocks the path. Symbols glow on the wall.\n";
                cout << "Clue from story.txt: " << puzzleClue << "\n";
                cout << "1. Press the sun symbol\n";
                cout << "2. Press the moon symbol\n";
                cout << "3. Press the flame symbol\n";
                cout << "4. Rest before solving the puzzle\n";

                int choice = getChoice(1, 4);

                if (choice == 2) {
                    cout << "\nThe moon symbol shines. The stone door opens.\n";
                    player.solvedPuzzle = true;
                    addItem(player, "Moon-marked stone");
                    randomHealthLoss(player, 0, 4, "The opening door throws dust and stone chips into the air.");
                    player.fatigue += randomNumber(5, 12);
                    player.escapeChance += 0.20;
                    finishScene(player);
                    state = GameState::UNDERGROUND_CITY;
                } else if (choice == 4) {
                    rest(player);
                } else {
                    cout << "\nThe wrong symbol triggers falling stones.\n";
                    randomHealthLoss(player, 8, 22, "The trap strikes before the door resets.");
                    player.fatigue += randomNumber(10, 25);

                    if (!checkLoss(player)) {
                        cout << "The door resets. You still need to solve it.\n";
                    }
                }
                break;
            }

            case GameState::UNDERGROUND_CITY: {
                showStatus(player);
                printInventory(player.inventory);

                cout << "\nScene " << player.scenesCompleted + 1 << ": Underground Civilization\n";
                cout << "Below the cave, hidden people surround you with lanterns.\n";
                cout << "Their leader offers a secret path beyond the police search line.\n";
                cout << "1. Trust them and follow the secret path\n";
                cout << "2. Refuse help and hide alone\n";
                cout << "3. Demand proof before following\n";

                int choice = getChoice(1, 3);

                if (choice == 1 && player.solvedPuzzle) {
                    cout << "\nThey guide you through tunnels that the police never find.\n";
                    randomHealthLoss(player, 0, 3, "The final tunnel is narrow but mostly safe.");
                    player.ending = "Win: escaped with help from the underground civilization.";
                } else if (choice == 3 && hasItem(player, "Moon-marked stone")) {
                    cout << "\nYou show the moon-marked stone. The leader accepts it as proof you passed the old door.\n";
                    randomHealthLoss(player, 0, 6, "The longer conversation gives the police more time, but you still move out.");
                    player.policeHeat += randomNumber(0, 1);
                    player.ending = "Win: earned the civilization's trust and escaped through the hidden path.";
                } else {
                    cout << "\nYou hide alone until footsteps echo through the chamber.\n";
                    randomHealthLoss(player, 1, 10, "Panic makes the final escape rough.");
                    player.ending = "Lost: refused the only safe escape route.";
                }

                finishScene(player);
                state = GameState::END_GAME;
                break;
            }

            case GameState::END_GAME: {
                cout << "\n========== GAME OVER ==========" << '\n';
                cout << player.ending << '\n';
                showStatus(player);
                writeSummary(player, "game_summary.txt");
                cout << "Summary written to game_summary.txt\n";
                running = false;
                break;
            }
        }
    }

    return 0;
}