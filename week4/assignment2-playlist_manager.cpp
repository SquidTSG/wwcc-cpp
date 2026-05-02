#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

struct Artist {
    string name;
    string hometown;
};

struct Song {
    string title;
    Artist artist;
    string genre;
    int durationSeconds;
};

// Helper to handle bad numeric input
int getValidSeconds() {
    int value;
    while (!(cin >> value) || value <= 0) {
        cout << "   Invalid duration. Please enter a positive whole number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
    return value;
}

string formatDuration(int seconds) {
    int minutes = seconds / 60;
    int secs = seconds % 60;
    return to_string(minutes) + ":" + (secs < 10 ? "0" : "") + to_string(secs);
}

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return tolower(c);
    });
    return str;
}

int main() {
    const int MAX_SONGS = 100; 
    Song playlist[MAX_SONGS];
    int songCount = 0;

    cout << "PERSONAL PLAYLIST MANAGER" << endl;
    cout << "--------------------------" << endl;

    // 1. Force the first 5 songs
    for (songCount = 0; songCount < 5; songCount++) {
        cout << "\nEnter information for Song " << (songCount + 1) << ":" << endl;
        cout << "  Title: ";
        getline(cin >> ws, playlist[songCount].title);
        cout << "  Artist name: ";
        getline(cin, playlist[songCount].artist.name);
        cout << "  Artist hometown: ";
        getline(cin, playlist[songCount].artist.hometown);
        cout << "  Genre: ";
        getline(cin, playlist[songCount].genre);
        cout << "  Duration (seconds): ";
        playlist[songCount].durationSeconds = getValidSeconds();
    }

    // 2. Ask if they want to add MORE after the initial 5
    char choice;
    cout << "\nStandard playlist filled. Add another song? (y/n): ";
    cin >> choice;

    while (tolower(choice) == 'y' && songCount < MAX_SONGS) {
        cout << "\nEnter information for Song " << (songCount + 1) << ":" << endl;
        cout << "  Title: ";
        getline(cin >> ws, playlist[songCount].title);
        cout << "  Artist name: ";
        getline(cin, playlist[songCount].artist.name);
        cout << "  Artist hometown: ";
        getline(cin, playlist[songCount].artist.hometown);
        cout << "  Genre: ";
        getline(cin, playlist[songCount].genre);
        cout << "  Duration (seconds): ";
        playlist[songCount].durationSeconds = getValidSeconds();

        songCount++;

        if (songCount < MAX_SONGS) {
            cout << "Add another? (y/n): ";
            cin >> choice;
        }
    }

    // --- Calculations & Displays ---
    int totalRuntime = 0;
    int longestIdx = 0;
    for (int i = 0; i < songCount; i++) {
        totalRuntime += playlist[i].durationSeconds;
        if (playlist[i].durationSeconds > playlist[longestIdx].durationSeconds) {
            longestIdx = i;
        }
    }

    cout << "\nYOUR PLAYLIST:" << endl;
    cout << "--------------" << endl;
    for (int i = 0; i < songCount; i++) {
        cout << i + 1 << ". " << playlist[i].title << endl;
        cout << "   Artist: " << playlist[i].artist.name << " (" << playlist[i].artist.hometown << ")" << endl;
        cout << "   Genre: " << playlist[i].genre << endl;
        cout << "   Duration: " << formatDuration(playlist[i].durationSeconds) << "\n" << endl;
    }

    cout << "Playlist Stats:" << endl;
    cout << "  Total runtime: " << formatDuration(totalRuntime) << endl;
    cout << "  Longest song:  " << playlist[longestIdx].title << " (" << formatDuration(playlist[longestIdx].durationSeconds) << ")" << endl;

    // Search Logic (Artist)
    string query;
    cout << "\nSearch by artist: ";
    getline(cin >> ws, query);
    bool found = false;
    for (int i = 0; i < songCount; i++) {
        if (toLower(playlist[i].artist.name) == toLower(query)) {
            cout << "  - " << playlist[i].title << " (" << formatDuration(playlist[i].durationSeconds) << ")" << endl;
            found = true;
        }
    }
    if (!found) cout << "  No results found for artist: " << query << endl;

    // Search Logic (Genre)
    cout << "\nSearch by genre: ";
    getline(cin >> ws, query);
    found = false;
    for (int i = 0; i < songCount; i++) {
        if (toLower(playlist[i].genre) == toLower(query)) {
            cout << "  - " << playlist[i].title << " (" << formatDuration(playlist[i].durationSeconds) << ")" << endl;
            found = true;
        }
    }
    if (!found) cout << "  No results found for genre: " << query << endl;

    return 0;
}