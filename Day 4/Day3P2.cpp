#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>

bool validate_field(std::string field, std::string val) {
    if (field == "byr") {
        int year = std::stoi(val);
        return year >= 1920 && year <= 2002;
    }

    if (field == "iyr") {
        int year = std::stoi(val);
        return year >= 2010 && year <= 2020;
    }

    if (field == "eyr") {
        int year = std::stoi(val);
        return year >= 2020 && year <= 2030;
    }

    if (field == "hgt") {
        int len = val.size();
        std::string unit = val.substr(len - 2, len);
        if (unit == "cm") {
            int height = std::stoi(val.substr(0, len - 2));
            return height >= 150 && height <= 193;
        } else if (unit == "in") {
            int height = std::stoi(val.substr(0, len - 2));
            return height >= 59 && height <= 76;
        } else {
            return false;
        }
    }

    if (field == "hcl") {
        std::regex regex("#[a-f0-9]{6}");
        return std::regex_match(val, regex);
    }

    if (field == "ecl") {
        std::unordered_set<std::string> colors { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
        return colors.count(val);
    }

    if (field == "pid") {
        std::regex regex("[0-9]{9}");
        return std::regex_match(val, regex);
    }

    if (field == "cid") {
        return true;
    }

    return false;
}

bool validate(std::string line) {
    int idx_colon = line.find_first_of(':');
    int idx_space = line.find_first_of(' ');
    std::string field, val;
    while (idx_colon != -1) {
        if (idx_space == -1) {
            idx_space = line.size();
        }
        field = line.substr(0, idx_colon);
        val = line.substr(idx_colon + 1, idx_space - idx_colon - 1);

        if (!validate_field(field, val)) {
            return false;
        }

        if (idx_space == line.size()) {
            line = line.substr(idx_space - 1);
        } else {
            line = line.substr(idx_space + 1);
        }
        idx_colon = line.find_first_of(':');
        idx_space = line.find_first_of(' ');
    }
    return true;
}

int main() {
    std::string line;
    std::ifstream input("input.txt");
    int num_of_fields, valid_count = 0;
    bool has_cid = false;
    bool is_valid = true;

    if (input.is_open()) {
        while (std::getline(input, line)) {
            while (line != "") {
                is_valid = is_valid && validate(line);
                ++num_of_fields;
                has_cid = has_cid || line.find("cid") != -1;
                for (char c : line) {
                    if (c == ' ') {
                        ++num_of_fields;
                    }
                }

                std::getline(input, line);
            }

            if (is_valid && (num_of_fields == 8 || (num_of_fields == 7 && !has_cid))) {
                ++valid_count;
            }
            num_of_fields = 0;
            has_cid = false;
            is_valid = true;
        }

        input.close();
    }

    std::cout << valid_count << "\n";
    return valid_count;
}