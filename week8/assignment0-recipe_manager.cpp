#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

struct Recipe {
    string name;
    vector<string> ingredients;
    vector<string> steps;
};

string getValidString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        bool hasContent = false;
        for (char c : input) {
            if (!isspace(c)) {
                hasContent = true;
                break;
            }
        }
        
        if (!hasContent) {
            cout << "Error: Input cannot be empty or just spaces. Please try again." << endl;
            continue;
        }
        return input;
    }
}

int getValidInt(const string& prompt, int minVal) {
    string input;
    int number;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        stringstream ss(input);
        if (ss >> number) {
            char extra;
            if (!(ss >> extra) && number >= minVal) {
                return number;
            }
        }
        cout << "Error: Invalid numeric input. Please enter a number greater than or equal to " << minVal << "." << endl;
    }
}

int getMenuChoice(const string& prompt, int minVal, int maxVal) {
    string input;
    int number;
    while (true) {
        cout << prompt;
        getline(cin, input);
        
        stringstream ss(input);
        if (ss >> number) {
            char extra;
            if (!(ss >> extra) && number >= minVal && number <= maxVal) {
                return number;
            }
        }
        cout << "Error: Invalid choice. Please enter a number between " << minVal << " and " << maxVal << "." << endl;
    }
}

string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

int main() {
    vector<Recipe> collection;
    
    while (true) {
        cout << "\nDYNAMIC RECIPE MANAGER" << endl;
        cout << "---------------------" << endl;
        cout << "1. Add Recipe" << endl;
        cout << "2. Display All Recipes" << endl;
        cout << "3. Search Recipes" << endl;
        cout << "4. Remove Recipe" << endl;
        cout << "5. Show Statistics" << endl;
        cout << "6. Exit" << endl;
        cout << endl;
        
        int choice = getMenuChoice("Enter choice: ", 1, 6);
        cout << endl;
        
        if (choice == 1) {
            Recipe newRecipe;
            newRecipe.name = getValidString("Enter recipe name: ");
            
            int numIngredients = getValidInt("How many ingredients? ", 1);
            for (int i = 0; i < numIngredients; ++i) {
                string prompt = "Enter ingredient " + to_string(i + 1) + ": ";
                newRecipe.ingredients.push_back(getValidString(prompt));
            }
            
            int numSteps = getValidInt("How many steps? ", 1);
            for (int i = 0; i < numSteps; ++i) {
                string prompt = "Enter step " + to_string(i + 1) + ": ";
                newRecipe.steps.push_back(getValidString(prompt));
            }
            
            collection.push_back(newRecipe);
            cout << "\nRecipe added successfully!" << endl;
        }
        else if (choice == 2) {
            if (collection.empty()) {
                cout << "The recipe collection is currently empty." << endl;
                continue;
            }
            
            cout << "ALL RECIPES" << endl;
            cout << "-----------" << endl;
            for (size_t i = 0; i < collection.size(); ++i) {
                const Recipe& recipe = collection.at(i);
                cout << i + 1 << ". " << recipe.name << endl;
                cout << "   Ingredients:" << endl;
                for (const string& ing : recipe.ingredients) {
                    cout << "     - " << ing << endl;
                }
                cout << "   Steps:" << endl;
                for (size_t j = 0; j < recipe.steps.size(); ++j) {
                    cout << "     " << j + 1 << ". " << recipe.steps.at(j) << endl;
                }
                cout << "---------------------" << endl;
            }
        }
        else if (choice == 3) {
            if (collection.empty()) {
                cout << "The recipe collection is currently empty." << endl;
                continue;
            }
            
            string searchTerm = getValidString("Enter search term (name or ingredient): ");
            string lowerSearch = toLower(searchTerm);
            bool foundAny = false;
            
            cout << "\nSEARCH RESULTS" << endl;
            cout << "--------------" << endl;
            
            for (size_t i = 0; i < collection.size(); ++i) {
                const Recipe& recipe = collection.at(i);
                bool matchFound = false;
                
                if (toLower(recipe.name).find(lowerSearch) != string::npos) {
                    matchFound = true;
                } else {
                    for (const string& ing : recipe.ingredients) {
                        if (toLower(ing).find(lowerSearch) != string::npos) {
                            matchFound = true;
                            break;
                        }
                    }
                }
                
                if (matchFound) {
                    foundAny = true;
                    cout << "Found: " << recipe.name << endl;
                    cout << "   Ingredients:" << endl;
                    for (const string& ing : recipe.ingredients) {
                        cout << "     - " << ing << endl;
                    }
                    cout << "   Steps:" << endl;
                    for (size_t j = 0; j < recipe.steps.size(); ++j) {
                        cout << "     " << j + 1 << ". " << recipe.steps.at(j) << endl;
                    }
                    cout << "---------------------" << endl;
                }
            }
            
            if (!foundAny) {
                cout << "No recipes found matching your search term." << endl;
            }
        }
        else if (choice == 4) {
            if (collection.empty()) {
                cout << "The recipe collection is currently empty. Nothing to remove." << endl;
                continue;
            }
            
            cout << "RECIPES AVAILABLE FOR REMOVAL" << endl;
            cout << "-----------------------------" << endl;
            for (size_t i = 0; i < collection.size(); ++i) {
                cout << i + 1 << ". " << collection.at(i).name << endl;
            }
            cout << endl;
            
            int removeChoice = getMenuChoice("Enter the number of the recipe to remove: ", 1, collection.size());
            
            collection.erase(collection.begin() + (removeChoice - 1));
            cout << "Recipe removed successfully!" << endl;
        }
        else if (choice == 5) {
            if (collection.empty()) {
                cout << "COLLECTION STATISTICS" << endl;
                cout << "--------------------" << endl;
                cout << "Total recipes: 0" << endl;
                cout << "Average ingredients per recipe: 0.0" << endl;
                cout << "Average steps per recipe: 0.0" << endl;
                continue;
            }
            
            double totalIngredients = 0;
            double totalSteps = 0;
            double totalRecipes = collection.size();
            
            for (size_t i = 0; i < collection.size(); ++i) {
                totalIngredients += collection.at(i).ingredients.size();
                totalSteps += collection.at(i).steps.size();
            }
            
            cout << "COLLECTION STATISTICS" << endl;
            cout << "--------------------" << endl;
            cout << "Total recipes: " << collection.size() << endl;
            cout << fixed << setprecision(1);
            cout << "Average ingredients per recipe: " << (totalIngredients / totalRecipes) << endl;
            cout << "Average steps per recipe: " << (totalSteps / totalRecipes) << endl;
        }
        else if (choice == 6) {
            cout << "Exiting Dynamic Recipe Manager" << endl;
            break;
        }
    }
    
    return 0;
}