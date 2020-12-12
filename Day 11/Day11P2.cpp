#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    unordered_map<int,unordered_map<int,char>> grid, prev;
    char state;

    if (input.is_open()) {
        int row = 0;
        while (getline(input, line)) {
            for (int col = 0; col < line.size(); ++col) {
                state = line[col];
                grid[row][col] = state == 'L' ? '#' : state;
            }
            ++row;
        }
        input.close();
    }

    vector<pair<int,int>> to_toggle;
    int rows = grid.size(), cols = grid[0].size(), count_occupied, adj_row, adj_col;
    while (true) {
        to_toggle.clear();
        for (int i = 0; i < rows; ++ i) {
            for (int j = 0; j < cols; ++j) {
                count_occupied = 0;
                state = grid[i][j];
                if (state == '.') {
                    continue;
                }
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        if (k == 0 && l == 0) {
                            continue;
                        }
                        adj_row = i + k;
                        adj_col = j + l;
                        while (adj_row >= 0 && adj_col >= 0 && adj_row < rows && adj_col < cols) {
                            state = grid[adj_row][adj_col];
                            if (state == '#') {
                                ++count_occupied;
                                break;
                            } else if (state == 'L') {
                                break;
                            }

                            adj_row += k;
                            adj_col += l;
                        }
                        
                    }
                }

                state = grid[i][j];
                if ((state == 'L' && count_occupied == 0) || (state == '#' && count_occupied > 4)) {
                    to_toggle.push_back({i, j});
                }
            }
        }

        if (to_toggle.empty()) {
            break;
        }

        int x, y;
        for (auto& p : to_toggle) {
            int x = p.first;
            int y = p.second;
            state = grid[x][y];
            grid[x][y] = state == '#' ? 'L' : '#';
        }
    }
    int count = 0;
    for (int i = 0; i < rows; ++ i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == '#') {
                ++count;
            }
        }
    }

    cout << count << "\n";

    return 0;
}