#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    map<int, int> bus_numbers;
    int idx = 0, len, substr_len = 0, offset = 0;
    char current_char;

    if (input.is_open()) {
        getline(input, line);
        getline(input, line);
        len = line.size();
        for (int i = 0; i <= line.size(); ++i) {
            current_char = line[i];
            switch (current_char) {
            case 'x':
                idx = i + 2;
                ++i;
                ++offset;
                break;
            case ',':
                bus_numbers[stoi(line.substr(idx, substr_len))] = offset;
                ++offset;
                idx = i + 1;
                substr_len = 0;
                break;
            default:
                ++substr_len;
            }
        }
        if (line[len - 1] != 'x') {
            bus_numbers[stoi(line.substr(idx))] = offset;
        }
        input.close();
    }

    long i, bus_number, product, remainder, count;
    auto init = bus_numbers.rbegin();
    bus_number = init->first;
    offset = init->second;
    product = bus_number;
    remainder = (bus_number - (offset % bus_number)) % bus_number;
    i = remainder;
    for (auto iter = ++bus_numbers.rbegin(); iter != bus_numbers.rend(); ++iter) {
        bus_number = iter->first;
        offset = iter->second;
        remainder = (bus_number - (offset % bus_number)) % bus_number;

        while (i % bus_number != remainder) {
            i += product;
        }

        product *= bus_number;
    }

    cout << i << "\n";

    return 0;
}