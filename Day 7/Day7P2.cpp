#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int get_count(unordered_map<string, pair<vector<int>, vector<string>>> m, string bag) {
    int count = 1;
    pair<vector<int>, vector<string>> val;
    vector<int> bag_count;
    vector<string> bags;

    val = m[bag];
    bag_count = val.first;
    bags = val.second;
    if (bag_count[0] == 0) {
        return count;
    }

    for (int i = 0; i < bags.size(); ++i) {
        count += bag_count[i] * get_count(m, bags[i]);
    }

    return count;
}

int main() {
    string line;
    ifstream input("input.txt");
    unordered_map<string, pair<vector<int>, vector<string>>> m;

    if (input.is_open()) {
        string bag, num_bags;
        vector<string> contains;
        vector<int> contains_count;
        int idx, idx_space;
        while (getline (input, line)) {
            idx = line.find("bags contain");
            bag = line.substr(0, idx - 1);
            line = line.substr(idx + 13);
            while (!line.empty()) {
                idx = line.find("bag");
                idx_space = line.find(" ");
                contains.push_back(line.substr(idx_space + 1, idx - 3));
                num_bags = line.substr(0, idx_space);
                contains_count.push_back(num_bags == "no" ? 0 : stoi(num_bags));
                idx = line.find(",");
                if (idx == -1) {
                    idx = line.size() - 2;
                }
                line = line.substr(idx + 2);
            }
            m[bag] = {contains_count, contains};
            contains.clear();
            contains_count.clear();
        }
        input.close();
    }

    pair<vector<int>, vector<string>> val;
    vector<string> stack, to_add;
    int count = 0;
    string current;
    for (auto& it : m) {
        val = it.second;
        to_add = val.second;
        stack.insert(stack.end(), to_add.begin(), to_add.end());
        while (!stack.empty()) {
            current = stack.back();
            stack.pop_back();
            if (current == "shiny gold") {
                ++count;
                break;
            }

            to_add = m[current].second;
            stack.insert(stack.end(), to_add.begin(), to_add.end());
        }
        stack.clear();
    }
    cout << get_count(m, "shiny gold") - 1 << "\n";
    return 0;
}