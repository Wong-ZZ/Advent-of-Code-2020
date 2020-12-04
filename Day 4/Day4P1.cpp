#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string line;
    std::ifstream input("input.txt");
    int num_of_fields, valid_count = 0;
    bool has_cid = false;

    if (input.is_open()) {
        while (std::getline(input, line)) {
            while (line != "") {
                ++num_of_fields;
                has_cid = has_cid || line.find("cid") != -1;
                for (char c : line) {
                    if (c == ' ') {
                        ++num_of_fields;
                    }
                }
                std::getline(input, line);
            }

            if (num_of_fields == 8 || (num_of_fields == 7 && !has_cid)) {
                ++valid_count;
            }
            num_of_fields = 0;
            has_cid = false;
        }

        input.close();
    }

    std::cout << valid_count << "\n";
    return valid_count;
}