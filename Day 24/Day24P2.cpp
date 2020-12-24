#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int count_black (map<pair<int,int>,bool>* tiles, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == j) {
                continue;
            }
            if ((*tiles)[{x + i, y + j}]) {
                ++count;
            }
        }
    }
    return count;
}

int main() {
    string line;
    ifstream input("input.txt");
    int x, y, idx, len, max_x = INT32_MIN, min_x = INT32_MAX, max_y = INT32_MIN, min_y = INT32_MAX;
    map<pair<int,int>,bool> tiles, temp;
    char current;

    if (input.is_open()) {
        while (getline(input, line)) {
            x = 0, y = 0, idx = 0, len = line.size();

            while (idx < len) {
                current = line[idx];
                switch (current) {
                case 'e':
                    x += 1;
                    break;
                case 'w':
                    x -= 1;
                    break;
                case 's':
                    y -= 1;
                    x += line[idx + 1] == 'e' ? 1 : 0;
                    ++idx;
                    break;
                case 'n':
                    y += 1;
                    x -= line[idx + 1] == 'w' ? 1 : 0;
                    ++idx;
                    break;
                }
                ++idx;
            }

            tiles[{x,y}] = !tiles[{x,y}];
            max_x = max(x, max_x);
            min_x = min(x, min_x);
            max_y = max(y, max_y);
            min_y = min(y, min_y);
        }

        input.close();
    }


    int days = 0;
    int black_count;
    bool current_tile;
    while (days < 100) {
        for (int x = min_x - 1; x <= max_x + 1; ++x) {
            for (int y = min_y - 1; y <= max_y + 1; ++y) {
                black_count = count_black(&tiles, x, y);
                current_tile = tiles[{x, y}];
                if (
                    (current_tile && (black_count == 0 || black_count > 2)) ||
                    (!current_tile && black_count == 2)
                ) {
                    temp[{x, y}] = !current_tile;
                    max_x = max(x, max_x);
                    min_x = min(x, min_x);
                    max_y = max(y, max_y);
                    min_y = min(y, min_y);
                } else {
                    temp[{x, y}] = tiles [{x, y}];
                }
            }
        }
        tiles = temp;
        temp.clear();
        ++days;
    }

    int count = 0;
    for (auto& i : tiles) {
        if (i.second) {
            ++count;
        }
    }

    cout << count << "\n";

    return 0;
}