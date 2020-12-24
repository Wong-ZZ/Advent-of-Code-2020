#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    int x, y, idx, len;
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
        }

        input.close();
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