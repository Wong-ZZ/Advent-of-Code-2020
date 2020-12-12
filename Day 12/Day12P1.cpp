#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    int x = 0, y = 0, direction = 0, val;

    if (input.is_open()) {
        while (getline(input, line)) {
            val = stoi(line.substr(1));
            switch (line[0]) {
            case 'N':
                y += val;
                break;
            case 'S':
                y -= val;
                break;
            case 'E':
                x += val;
                break;
            case 'W':
                x -= val;
                break;
            case 'L':
                direction = (direction + val) % 360;
                break;
            case 'R':
                direction = (direction - val + 360) % 360;
                break;
            case 'F':
                y += (direction % 180 == 90) * ((direction - 180) / -90) * val;
                x += (direction % 180 == 0) * ((direction - 90) / -90) * val;
                break;
            }
        }
        cout << abs(x) + abs(y) << "\n";
        input.close();
    }

    return 0;
}