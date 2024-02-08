#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Structure to represent a recipe
struct Recipe {
    string name;
    vector<string> ingredients;
    string instructions;
};

class RecipeManager {
private:
    vector<Recipe> recipes;
    const string filename = "recipes.txt"; // File to store recipe data

public:
    // Function to load recipes from file
    void loadRecipesFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            Recipe recipe;
            while (getline(file, recipe.name)) {
                string line;
                getline(file, line);
                stringstream ss(line);
                string ingredient;
                while (getline(ss, ingredient, ',')) {
                    recipe.ingredients.push_back(ingredient);
                }
                getline(file, recipe.instructions);
                recipes.push_back(recipe);
            }
            file.close();
        }
    }

    // Function to add a new recipe
    void addRecipe(const Recipe& recipe) {
        recipes.push_back(recipe);
        saveRecipesToFile(); // Save recipes to file
        cout << "Recipe added successfully!\n";
    }

    // Function to save recipes to file
    void saveRecipesToFile() {
        ofstream file(filename, ios::out | ios::trunc);
        if (file.is_open()) {
            for (const auto& recipe : recipes) {
                file << recipe.name << endl;
                for (const auto& ingredient : recipe.ingredients) {
                    file << ingredient << ",";
                }
                file << endl;
                file << recipe.instructions << endl;
            }
            file.close();
        }
    }

    // Function to display all recipes
    void viewRecipes() {
        cout << "\n===== All Recipes =====\n";
        for (const auto& recipe : recipes) {
            cout << "Name: " << recipe.name << endl;
            cout << "Ingredients: ";
            for (const auto& ingredient : recipe.ingredients) {
                cout << ingredient << ", ";
            }
            cout << endl;
            cout << "Instructions: " << recipe.instructions << endl;
            cout << "-------------------------\n";
        }
    }

    // Function to search recipes by name or ingredients
    void searchRecipes(const string& keyword) {
        cout << "\n===== Search Results =====\n";
        for (const auto& recipe : recipes) {
            if (recipe.name.find(keyword) != string::npos) {
                cout << "Name: " << recipe.name << endl;
                cout << "Ingredients: ";
                for (const auto& ingredient : recipe.ingredients) {
                    cout << ingredient << ", ";
                }
                cout << endl;
                cout << "Instructions: " << recipe.instructions << endl;
                cout << "-------------------------\n";
            } else {
                bool found = false;
                for (const auto& ingredient : recipe.ingredients) {
                    if (ingredient.find(keyword) != string::npos) {
                        found = true;
                        cout << "Name: " << recipe.name << endl;
                        cout << "Ingredients: ";
                        for (const auto& ingredient : recipe.ingredients) {
                            cout << ingredient << ", ";
                        }
                        cout << endl;
                        cout << "Instructions: " << recipe.instructions << endl;
                        cout << "-------------------------\n";
                        break;
                    }
                }
                if (found) continue;
            }
        }
    }

    // Function to update a recipe
    void updateRecipe(const string& name, const Recipe& newRecipe) {
        for (auto& recipe : recipes) {
            if (recipe.name == name) {
                recipe = newRecipe;
                saveRecipesToFile(); // Save recipes to file
                cout << "Recipe updated successfully!\n";
                return;
            }
        }
        cout << "Recipe not found!\n";
    }

    // Function to delete a recipe
    void deleteRecipe(const string& name) {
        auto it = remove_if(recipes.begin(), recipes.end(), [&name](const Recipe& recipe) {
            return recipe.name == name;
        });
        if (it != recipes.end()) {
            recipes.erase(it, recipes.end());
            saveRecipesToFile(); // Save recipes to file
            cout << "Recipe deleted successfully!\n";
        } else {
            cout << "Recipe not found!\n";
        }
    }
};

int main() {
    RecipeManager recipeManager;
    recipeManager.loadRecipesFromFile(); // Load recipes from file
    char choice;

    do {
        cout << "\n===== Recipe Manager =====\n";
        cout << "1. Add Recipe\n";
        cout << "2. View Recipes\n";
        cout << "3. Search Recipes\n";
        cout << "4. Update Recipe\n";
        cout << "5. Delete Recipe\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                Recipe newRecipe;
                cout << "Enter recipe name: ";
                cin.ignore();
                getline(cin, newRecipe.name);
                cout << "Enter ingredients (separated by commas): ";
                string ingredientsStr;
                getline(cin, ingredientsStr);
                stringstream ss(ingredientsStr);
                string ingredient;
                while (getline(ss, ingredient, ',')) {
                    newRecipe.ingredients.push_back(ingredient);
                }
                cout << "Enter instructions: ";
                getline(cin, newRecipe.instructions);
                recipeManager.addRecipe(newRecipe);
                break;
            }
            case '2':
                recipeManager.viewRecipes();
                break;
            case '3': {
                string keyword;
                cout << "Enter keyword to search for recipes: ";
                cin.ignore();
                getline(cin, keyword);
                recipeManager.searchRecipes(keyword);
                break;
            }
            case '4': {
                string name;
                Recipe updatedRecipe;
                cout << "Enter name of recipe to update: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter updated recipe details:\n";
                cout << "Enter recipe name: ";
                getline(cin, updatedRecipe.name);
                cout << "Enter updated ingredients (separated by commas): ";
                string ingredientsStr;
                getline(cin, ingredientsStr);
                stringstream ss(ingredientsStr);
                string ingredient;
                while (getline(ss, ingredient, ',')) {
                    updatedRecipe.ingredients.push_back(ingredient);
                }
                cout << "Enter updated instructions: ";
                getline(cin, updatedRecipe.instructions);
                recipeManager.updateRecipe(name, updatedRecipe);
                break;
            }
            case '5': {
                string name;
                cout << "Enter name of recipe to delete: ";
                cin.ignore();
                getline(cin, name);
                recipeManager.deleteRecipe(name);
                break;
            }
            case '6':
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != '6');

    return 0;
}
