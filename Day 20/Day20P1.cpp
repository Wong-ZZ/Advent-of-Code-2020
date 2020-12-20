#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
typedef pair<int,vector<string>> tile_info;

bool matches(string side, vector<string> tile) {
    vector<string> sides;
    string left ="",  right = "";
    sides.push_back(tile.front());
    sides.push_back(tile.back());
    for (auto& i : tile) {
        left += i.front();
        right += i.back();
    }
    sides.push_back(left);
    sides.push_back(right);

    for (int i = 0; i < 4; ++i) {
        string copy(sides[i]);
        reverse(copy.begin(), copy.end());
        sides.push_back(copy);
    }

    for (int i = 0; i < 8; ++i) {
        if (side == sides[i]) {
            return true;
        }
    }

    return false;
}

int main() {
    string line;
    ifstream input("input.txt");
    int tile_num, idx_colon;
    unordered_map<int,vector<string>> tiles;

    if (input.is_open()) {
        vector<string> current_tile;
        while (getline(input, line)) {
            if (line.empty()) {
                continue;
            }
            idx_colon = line.find(':');
            tile_num = stoi(line.substr(5, idx_colon - 5));
            getline(input, line);
            while (line.length() > 1) {
                current_tile.push_back(line);
                getline(input, line);
            }
            tiles[tile_num] = current_tile;
            current_tile.clear();
        }
        input.close();
    }

    vector<string> current_tile, sides;
    string left, right;
    long result = 1;
    for (const tile_info& current_tile_info : tiles) {
        left ="",  right = "";
        current_tile = current_tile_info.second;
        tile_num = current_tile_info.first;

        sides.push_back(current_tile.front()); // top
        sides.push_back(current_tile.back()); // btm
        for (auto& i : current_tile) {
            left += i.front();
            right += i.back();
        }
        sides.push_back(left);
        sides.push_back(right);
        int num_matches = 0;
        for (int i = 0; i < 4; ++i) {
            string side = sides[i];
            for (auto& tile : tiles) {
                if (tile.second == current_tile) {
                    continue;
                }
                bool is_match = matches(side, tile.second);
                if (is_match) {
                    ++num_matches;
                    break;
                }
            }
        }

        if (num_matches == 2) {
            result *= tile_num;
        }

        sides.clear();
    }

    cout << result << "\n";

    return 0;
}