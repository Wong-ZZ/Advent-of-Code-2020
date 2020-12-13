#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    vector<int> bus_numbers;
    int idx = 0, start_time, len, substr_len = 0;
    char current_char;

    if (input.is_open()) {
        getline(input, line);
        start_time = stoi(line);
        getline(input, line);
        len = line.size();
        for (int i = 0; i <= line.size(); ++i) {
            current_char = line[i];
            switch (current_char) {
            case 'x':
                idx = i + 2;
                ++i;
                break;
            case ',':
                bus_numbers.push_back(stoi(line.substr(idx, substr_len)));
                idx = i + 1;
                substr_len = 0;
                break;
            default:
                ++substr_len;
            }
        }
        if (line[len - 1] != 'x') {
            bus_numbers.push_back(stoi(line.substr(idx)));
        }
        input.close();
    }

    int earliest_bus, earliest_time = INT32_MAX, next_bus_time;
    for (int bus_number : bus_numbers) {
        next_bus_time = start_time + (bus_number - (start_time % bus_number));
        if (next_bus_time < earliest_time) {
            earliest_time = next_bus_time;
            earliest_bus = bus_number;
        }
    }

    cout << earliest_bus * (earliest_time - start_time) << "\n";

    return 0;
}