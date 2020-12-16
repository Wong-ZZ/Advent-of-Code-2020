#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

int main() {
    string line;
    ifstream input("input.txt");
    unordered_map<string,vector<pair<int,int>>> constraints;

    if (input.is_open()) {
        getline(input, line);
        while (line.find("your ticket:") == -1) {
            if (line.length() <= 1) {
                getline(input, line);
                continue;
            }
            int idx_colon = line.find_first_of(':');
            string constraint = line.substr(0, idx_colon);
            line = line.substr(idx_colon + 2);
            while (!line.empty()) {
                int idx_or = line.find_first_of("or");
                int idx_dash = line.find_first_of('-');
                int lower_limit = stoi(line.substr(0, idx_dash));
                int upper_limit = idx_or == -1 ? stoi(line.substr(idx_dash + 1)) : stoi(line.substr(idx_dash + 1, idx_or - 1));
                constraints[constraint].push_back({lower_limit, upper_limit});
                line = idx_or == -1 ? "" : line.substr(idx_or + 3);
            }
            getline(input, line);
        }

        getline(input, line);
        string my_ticket_info = line;

        while (line.find("nearby tickets:") == -1) {
            getline(input, line);
        }

        unordered_map<int,set<string>> m;
        while (getline(input, line)) {
            int field_num = 0;
            while (!line.empty()) {
                set<string> possible_fields;
                ++field_num;
                int idx_comma = line.find_first_of(',');
                int current_num = stoi(line.substr(0, idx_comma == -1 ? line.length() : idx_comma));
                bool meets_any_constraint = false;
                for (auto& key_value : constraints) {
                    string constraint = key_value.first;
                    vector<pair<int,int>> ranges = key_value.second;
                    for (auto& range : ranges) {
                        int lower = range.first;
                        int upper = range.second;
                        if (current_num >= lower && current_num <= upper) {
                            possible_fields.insert(constraint);
                            meets_any_constraint = true;
                        }
                    }
                }

                line = line.substr(idx_comma == -1 ? line.length() : idx_comma + 1);

                if (!meets_any_constraint) {
                    break;
                }

                if (m.count(field_num) != 1) {
                    m[field_num] = possible_fields;
                    continue;
                }

                vector<string> to_erase;
                for (auto& field : m[field_num]) {
                    if (possible_fields.count(field) != 1) {
                        to_erase.push_back(field);
                    }
                }
                for (auto& i : to_erase) {
                    m[field_num].erase(i);
                }
            }
        }

        while (!m.empty()) {
            string constraint_to_erase;
            int key_to_erase;
            for (auto& i : m) {
                if (i.second.size() == 1) {
                    key_to_erase = i.first;
                    constraint_to_erase = *i.second.begin();
                    cout << key_to_erase << ":" << constraint_to_erase << "\n";
                    break;
                }
            }
            m.erase(key_to_erase);
            for (auto& i : m) {
                i.second.erase(constraint_to_erase);
            }
        }

        unordered_map<int,long> my_ticket_fields;
        int field_num = 0;
        while (!my_ticket_info.empty()) {
            ++field_num;
            int idx_comma = my_ticket_info.find_first_of(',');
            int current_num = stoi(my_ticket_info.substr(0, idx_comma == -1 ? my_ticket_info.length() : idx_comma));
            my_ticket_fields[field_num] = current_num;
            my_ticket_info = my_ticket_info.substr(idx_comma == -1 ? my_ticket_info.length() : idx_comma + 1);
        }

        long result = my_ticket_fields[5] * my_ticket_fields[6] * my_ticket_fields[7] * my_ticket_fields[16] * my_ticket_fields[18] * my_ticket_fields[19];
        cout << result << "\n";

        input.close();
    }


    return 0;
}