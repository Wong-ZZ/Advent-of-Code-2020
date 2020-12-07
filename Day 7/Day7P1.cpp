#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    std::string line;
    std::ifstream input("input.txt");
    std::unordered_map<std::string, std::vector<std::string>> m;

    if (input.is_open()) {
        std::string bag;
        std::vector<std::string> contains;
        int idx;
        while (std::getline (input, line)) {
            idx = line.find("bags contain");
            bag = line.substr(0, idx - 1);
            line = line.substr(idx + 13);
            while (!line.empty()) {
                idx = line.find("bag");
                contains.push_back(line.substr(2, idx - 3));
                idx = line.find(",");
                if (idx == -1) {
                    idx = line.size() - 2;
                }
                line = line.substr(idx + 2);
            }
            m[bag] = contains;
            contains.clear();
        }
        input.close();
    }

    std::vector<std::string> stack, to_add;
    int count = 0;
    std::string current;
    for (auto& it : m) {
        to_add = it.second;
        stack.insert(stack.end(), to_add.begin(), to_add.end());
        while (!stack.empty()) {
            current = stack.back();
            stack.pop_back();
            if (current == "shiny gold") {
                ++count;
                break;
            }

            to_add = m[current];
            stack.insert(stack.end(), to_add.begin(), to_add.end());
        }
        stack.clear();
    }
    std::cout << count << "\n";
    return 0;
}