#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iomanip>

using namespace std;

enum class EventCategory { CONCERT, CONFERENCE, SPORTS, WORKSHOP };

struct Event {
    string name;
    string date;          // format: "YYYY-MM-DD"
    EventCategory category;
    int attendees;
    double ticketPrice;
};

// Returns the display name for a category
string categoryName(EventCategory cat) {
    switch (cat) {
        // BUG: CONCERT and WORKSHOP returned swapped string labels
        // FIX: swapped the string literals so CONCERT returns Concert and WORKSHOP returns Workshop
        case EventCategory::CONCERT:    return "Concert";   // Bug 5
        case EventCategory::CONFERENCE: return "Conference";
        case EventCategory::SPORTS:     return "Sports";
        case EventCategory::WORKSHOP:   return "Workshop";    // Bug 5
        default:                        return "Unknown";
    }
}

// Display a single event
void printEvent(const Event& e) {
    cout << left << setw(30) << e.name         
         << setw(12) << e.date         
         << setw(12) << categoryName(e.category)         
         << "Attendees: " << setw(5) << e.attendees         
         << " Price: $" << fixed << setprecision(2) << e.ticketPrice         
         << "\n";
}

// Display all events
void displayAll(const vector<Event>& events) {
    cout << "\n=== All Events ===\n";
    cout << left << setw(30) << "Name" << setw(12) << "Date"         
         << setw(12) << "Category" << "\n";
    cout << string(70, '-') << "\n";
    for (const auto& e : events) {
        printEvent(e);
    }
}

// Calculate total revenue across all events
double totalRevenue(const vector<Event>& events) {
    return accumulate(events.begin(), events.end(), 0.0,
        [](double sum, const Event& e) {

            // BUG: only added e.attendees to the total, ignoring the ticket price
            // FIX: multiplied e.attendees by e.ticketPrice to accurately accumulate revenue
            return sum + (e.attendees * e.ticketPrice);   // Bug 1: missing * e.ticketPrice
        });
}

// Calculate average ticket price across all events
double averageTicketPrice(const vector<Event>& events) {
    if (events.empty()) return 0.0;


    // BUG: total was declared as an int, and the division was integer division, truncating decimals
    // FIX: changed total to a double to accumulate precise ticket prices and prevent integer truncation during division
    double total = 0.0;                      // Bug 2: should be double
    for (const auto& e : events) {
        total += e.ticketPrice;         // Bug 2: fractional part truncated
    }
    return total / events.size(); // Bug 2: integer division
}

// Sort events by date, oldest first
void sortByDateAscending(vector<Event>& events) {
    sort(events.begin(), events.end(),
        [](const Event& a, const Event& b) {
            // BUG: using the > operator sorted the dates in descending order
            // FIX: changed the operator to < to sort them in ascending chronological order
            return a.date < b.date;     // Bug 3: > sorts descending, not ascending
        });
}

// Search for events whose name contains the search term (case-sensitive)
void searchByName(const vector<Event>& events, const string& term) {
    cout << "\n=== Search Results for \"" << term << "\" ===\n";

 // Bug 4: only prints first match, not all

    // BUG: std::find_if stops after finding the first match, missing subsequent matching items
    // FIX: replaced std::find_if tracking with a loop to check all events and print every match found
    bool foundAny = false;
    for (const auto& e : events) {
        if (e.name.find(term) != string::npos) {
            printEvent(e);
            foundAny = true;
        }
    }
    if (!foundAny) {
        cout << "No events found.\n";
    }
}


void sortByAttendees(vector<Event>& events) {
    // sorting by descending attendee count
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.attendees > b.attendees;
    });

    cout << "\n=== Events by Popularity ===\n";
    for (const auto& e : events) {
        printEvent(e);
    }
}

void filterByCategory(const vector<Event>& events, EventCategory cat) {
    cout << "\n=== " << categoryName(cat) << "s ===\n";
    
    // pulling out matches into a temporary vector to display
    vector<Event> filteredEvents;
    copy_if(events.begin(), events.end(), back_inserter(filteredEvents), [cat](const Event& e) {
        return e.category == cat;
    });

    for (const auto& e : filteredEvents) {
        printEvent(e);
    }
}


void exportUpcomingEvents(const vector<Event>& events, const string& filename) {
    ofstream outFile(filename);
    
    // basic sanity check to ensure the file actually opens
    if (!outFile) {
        cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    for (const auto& e : events) {
        if (e.date >= "2025-06-01") {
            outFile << e.name << " | " 
                    << e.date << " | " 
                    << categoryName(e.category) << " | " 
                    << e.attendees << " | $" 
                    << fixed << setprecision(2) << e.ticketPrice << "\n";
        }
    }

    cout << "\nUpcoming events saved to " << filename << "\n";
    outFile.close();
}

// Bonus Challenge: filterByMinAttendees
// Display only events with more than minCount attendees using copy_if and capturing minCount.
void filterByMinAttendees(const vector<Event>& events, int minCount) {
    cout << "\n=== Events with More Than " << minCount << " Attendees ===\n";
    
    vector<Event> crowdedEvents;
    copy_if(events.begin(), events.end(), back_inserter(crowdedEvents), [minCount](const Event& e) {
        return e.attendees > minCount;
    });

    if (crowdedEvents.empty()) {
        cout << "No events meet this criteria.\n";
    } else {
        for (const auto& e : crowdedEvents) {
            printEvent(e);
        }
    }
}

int main() {
    vector<Event> events = {
        {"Spring Music Fest",     "2025-04-12", EventCategory::CONCERT,    1200, 45.50},
        {"Tech Summit 2025",      "2025-06-20", EventCategory::CONFERENCE,  350, 129.00},
        {"City 5K Run",           "2025-05-03", EventCategory::SPORTS,      800, 25.25},
        {"Watercolor Workshop",   "2025-07-15", EventCategory::WORKSHOP,     40, 60.00},
        {"Jazz Under the Stars",  "2025-08-02", EventCategory::CONCERT,     600, 35.75},
        {"Leadership Workshop",   "2025-06-28", EventCategory::WORKSHOP,     75, 89.00},
        {"Regional Soccer Cup",   "2025-09-14", EventCategory::SPORTS,     2500, 18.00},
        {"Dev Conf Northwest",    "2025-10-05", EventCategory::CONFERENCE,   420, 199.00},
    };

    cout << "=== Community Event Scheduler ===\n";
    displayAll(events);

    cout << "\nTotal revenue (all events): $"         
         << fixed << setprecision(2) << totalRevenue(events) << "\n";

    cout << "Average ticket price: $"         
         << fixed << setprecision(2) << averageTicketPrice(events) << "\n";

    sortByDateAscending(events);
    cout << "\n=== Events sorted by date (oldest first) ===\n";
    for (const auto& e : events) {
        printEvent(e);
    }

    searchByName(events, "Workshop");

    // Uncomment after implementing features:
    sortByAttendees(events);
    filterByCategory(events, EventCategory::CONCERT);
    exportUpcomingEvents(events, "upcoming_events.txt");

    // Bonus Challenge Call
    filterByMinAttendees(events, 500);

    return 0;
}