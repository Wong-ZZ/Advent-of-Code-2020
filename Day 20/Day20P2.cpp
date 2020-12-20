#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;
typedef pair<int,vector<string>> tile_info;
typedef pair<int,int> coord;

vector<string> flip_horizontal(vector<string> tile) {
    vector<string> result = tile;
    for (int i = 0; i < tile.size(); ++i) {
        reverse(result[i].begin(), result[i].end());
    }
    return result;
}

vector<string> flip_vertical(vector<string> tile) {
    vector<string> result = tile;
    reverse(result.begin(), result.end());
    return result;
}

vector<string> rotate_tile(vector<string> tile) {
    vector<string> result(tile.size());
    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile.size(); ++j) {
            result[i] += tile[j][tile.size() - i - 1];
        }
    }
    return result;
}

vector<string> rotate_tile(vector<string> tile, int type, int init) {
    vector<string> result(tile);
    for (int i = 0; i < ((6 - init) % 4) + (type % 4); ++i) {
        result = rotate_tile(result);
    }
    if (type < 4) {
        if (init % 2 == 0) {
            result = flip_horizontal(result);
        } else {
            result = flip_vertical(result);
        }
    }
    return result;
}

coord get_new_coord(coord c, int init) {
    coord offsets[4] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    coord offset = offsets[init];
    return {c.first + offset.first, c.second + offset.second};
}

int matches(string side, vector<string> tile) {
    vector<string> sides;
    string left ="",  right = "";
    for (auto& i : tile) {
        left = i.front() + left;
        right += i.back();
    }
    string btm = tile.back();
    reverse(btm.begin(), btm.end());
    sides.push_back(tile.front());
    sides.push_back(right);
    sides.push_back(btm);
    sides.push_back(left);

    for (int i = 0; i < 4; ++i) {
        string copy(sides[i]);
        reverse(copy.begin(), copy.end());
        sides.push_back(copy);
    }

    for (int i = 0; i < 8; ++i) {
        if (side == sides[i]) {
            return i;
        }
    }

    return -1;
}

int main() {
    string line;
    ifstream input("input.txt");
    int idx_colon;
    vector<vector<string>> tiles;

    if (input.is_open()) {
        vector<string> current_tile;
        while (getline(input, line)) {
            if (line.empty()) {
                continue;
            }
            getline(input, line);
            while (line.length() > 1) {
                current_tile.push_back(line);
                getline(input, line);
            }
            tiles.push_back(current_tile);
            current_tile.clear();
        }
        input.close();
    }

    map<pair<int,int>,vector<string>> image;
    image[{0,0}] = tiles.front();
    queue<pair<coord,vector<string>>> q;
    q.push({{0,0},tiles.front()});
    vector<string> sides;
    string left, right, btm;
    set<int> checked;
    checked.insert(0);
    while (!q.empty()) {
        left ="",  right = "";
        pair<coord,vector<string>> tile_info = q.front();
        q.pop();
        vector<string> current_tile = tile_info.second;
        coord c = tile_info.first;
        for (auto& i : current_tile) {
            left = i.front() + left;
            right += i.back();
        }
        btm = current_tile.back();
        reverse(btm.begin(), btm.end());
        sides.push_back(current_tile.front()); // top
        sides.push_back(right);
        sides.push_back(btm); // btm
        sides.push_back(left);
        for (int i = 0; i < 4; ++i) {
            string side = sides[i];
            for (int j = 0; j < tiles.size(); ++j) {
                vector<string> tile = tiles[j];
                if (tile == current_tile || checked.count(j) == 1) {
                    continue;
                }
                int match_type = matches(side, tile);

                if (match_type != -1) {
                    coord new_coord = get_new_coord(c, i);
                    vector<string> rotated_tile = rotate_tile(tile, match_type, i);
                    image[new_coord] = rotated_tile;
                    if (checked.count(j) != 1) {
                        checked.insert(j);
                        q.push({new_coord, rotated_tile});
                    }
                    break;
                }
            }
        }

        sides.clear();
    }

    // print stitched image with borders not removed
    int x_min = image.begin()->first.first;
    int x_max = image.rbegin()->first.first;
    int y_min = image.begin()->first.second;
    int y_max = image.rbegin()->first.second;
    int len = image.begin()->second.size();

    int l = 0;
    vector<string> full_image;
    for (int i = y_max; i >= y_min; --i) {
        for (int j = 1; j < len - 1; ++j) {
            full_image.push_back("");
            for (int k = x_min; k <= x_max ; ++k) {
                string to_add;
                to_add = image[{k,i}][j].substr(1, len - 2);
                full_image.back() += to_add;
            }
        }
        ++l;
    }

    int num_hash = 0;
    for (auto& i : full_image) {
        for (auto& j : i) {
            if (j == '#') {
                ++num_hash;
            }
        }
        cout << i << "\n";
    }

    int num_monsters = 0;
    for (int h = 0; h < 8; ++h) {
        for (int i = 1; i < full_image.size() - 1; ++i) {
            for (int j = 18; j < full_image[0].size() - 1; ++j) {
                int offset = j - 18;
                if (full_image[i - 1][j] != '#') {
                    continue;
                }
                bool found = true;
                for (auto& k : {0, 5, 6, 11, 12, 17, 18, 19}) {
                    if (full_image[i][k + offset] != '#') {
                        found = false;
                        break;
                    }
                }

                if (!found) {
                    continue;
                }
                for (auto& k : {1, 4, 7, 10, 13, 16}) {
                    if (full_image[i + 1][k + offset] != '#') {
                        found = false;
                        break;
                    }
                }
                if (found) {
                    ++num_monsters;
                }
            }
        }

        if (num_monsters > 0) {
            break;
        }
        if (h != 3) {
            full_image = rotate_tile(full_image);
        } else {
            full_image = flip_vertical(full_image);
        }
    }

    cout << num_hash - num_monsters * 15 << "\n";

    return 0;
}