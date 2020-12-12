#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    int waypoint_x = 10, waypoint_y = 1, temp_x, x = 0, y = 0, val;

    if (input.is_open()) {
        while (getline(input, line)) {
            val = stoi(line.substr(1));
            temp_x = waypoint_x;
            switch (line[0]) {
            case 'N':
                waypoint_y += val;
                break;
            case 'S':
                waypoint_y -= val;
                break;
            case 'E':
                waypoint_x += val;
                break;
            case 'W':
                waypoint_x -= val;
                break;
            case 'L':
                waypoint_x = val == 180 ? -waypoint_x : waypoint_y * (val - 180) / 90;
                waypoint_y = val == 180 ? -waypoint_y : temp_x * (val - 180) / -90;
                break;
            case 'R':
                waypoint_x = val == 180 ? -waypoint_x : waypoint_y * (val - 180) / -90;
                waypoint_y = val == 180 ? -waypoint_y : temp_x * (val - 180) / 90;
                break;
            case 'F':
                y += waypoint_y * val;
                x += waypoint_x * val;
                break;
            }
        }
        cout << abs(x) + abs(y) << "\n";
        input.close();
    }

    return 0;
}