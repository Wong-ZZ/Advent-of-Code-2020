#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    map<string,int> counter;
    map<string,map<string,int>> possible_words;
    string ingredients_str, allergens_str, allergen, ingredient;
    vector<string> ingredients, allergens;
    int idx_open_bracket, idx_close_bracket, idx_space, idx_comma;
    vector<string> all_ingredients;

    if (input.is_open()) {
        while (getline(input, line)) {
            ingredients.clear();
            allergens.clear();
            idx_open_bracket = line.find_first_of('(');
            idx_close_bracket = line.find_first_of(')');
            allergens_str = line.substr(idx_open_bracket + 10, idx_close_bracket - idx_open_bracket - 10);
            ingredients_str = line.substr(0, idx_open_bracket - 1);
            while (!allergens_str.empty()) {
                idx_comma = allergens_str.find_first_of(',');
                if (idx_comma == -1) {
                    allergens.push_back(allergens_str);
                    allergens_str = "";
                    continue;
                }
                allergen = allergens_str.substr(0, idx_comma);
                allergens.push_back(allergen);
                allergens_str = allergens_str.substr(idx_comma + 2);
            }

            while (!ingredients_str.empty()) {
                idx_space = ingredients_str.find_first_of(" ");
                if (idx_space == -1) {
                    ingredients.push_back(ingredients_str);
                    ingredients_str = "";
                    continue;
                }
                ingredient = ingredients_str.substr(0, idx_space);
                ingredients.push_back(ingredient);
                ingredients_str = ingredients_str.substr(idx_space + 1);
            }

            for (auto& a : allergens) {
                if (counter.count(a) != 1) {
                    counter[a] = 0;
                }
                ++counter[a];

                for (auto& i : ingredients) {
                    if (possible_words[a].count(i) != 1) {
                        possible_words[a][i] = 0;
                    }
                    ++possible_words[a][i];
                }
            }

            all_ingredients.insert(all_ingredients.begin(), ingredients.begin(), ingredients.end());
        }
        input.close();
    }

    set<string> s;
    for (auto& i : counter) {
        string key = i.first;
        int count = i.second;
        for (auto& j : possible_words[key]) {
            if (j.second == count) {
                s.insert(j.first);
            }
        }
    }

    int count = 0;
    for (auto& i : all_ingredients) {
        if (s.count(i) != 1) {
            ++count;
        }
    }

    cout << count << "\n";

    return 0;
}