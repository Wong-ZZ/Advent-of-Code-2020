#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int play_subgame(vector<int> p1, vector<int> p2, set<pair<vector<int>,vector<int>>>* sub_states) {
    if (p1.empty() || p2.empty()) {
        return p1.empty() ? 2 : 1;
    }

    if ((*sub_states).count({p1,p2}) == 1) {
        return 1;
    }
    (*sub_states).insert({p1,p2});

    int next1 = p1.front();
    int next2 = p2.front();
    p1.erase(p1.begin());
    p2.erase(p2.begin());
    bool p1_wins = next1 > next2;
    if (p1.size() >= next1 && p2.size() >= next2) {
        set<pair<vector<int>,vector<int>>> sub_sub_states;
        vector<int> sub_p1(p1.begin(), p1.begin() + next1);
        vector<int> sub_p2(p2.begin(), p2.begin() + next2);
        p1_wins = play_subgame(sub_p1, sub_p2, &sub_sub_states) == 1;
    }
    if (p1_wins) {
        p1.push_back(next1);
        p1.push_back(next2);
    } else {
        p2.push_back(next2);
        p2.push_back(next1);
    }

    return play_subgame(p1, p2, sub_states);
}

vector<int> play_game(vector<int> p1, vector<int> p2, set<pair<vector<int>,vector<int>>>* states) {
    if (p1.empty() || p2.empty()) {
        return p1.empty() ? p2 : p1;
    }

    if ((*states).count({p1,p2}) == 1) {
        return p2;
    }
    (*states).insert({p1,p2});

    int next1 = p1.front();
    int next2 = p2.front();
    p1.erase(p1.begin());
    p2.erase(p2.begin());
    bool p1_wins = next1 > next2;
    if (p1.size() >= next1 && p2.size() >= next2) {
        set<pair<vector<int>,vector<int>>> sub_states;
        vector<int> sub_p1(p1.begin(), p1.begin() + next1);
        vector<int> sub_p2(p2.begin(), p2.begin() + next2);
        p1_wins = play_subgame(sub_p1, sub_p2, &sub_states) == 1;
    }
    if (p1_wins) {
        p1.push_back(next1);
        p1.push_back(next2);
    } else {
        p2.push_back(next2);
        p2.push_back(next1);
    }
    return play_game(p1, p2, states);
}

int main() {
    string line;
    ifstream input("input.txt");
    vector<int> p1, p2;

    if (input.is_open()) {
        getline(input, line);
        while (getline(input, line)) {
            if (line.empty()) {
                break;
            }
            p1.push_back(stoi(line));
        }
        getline(input, line);
        while (getline(input, line)) {
            if (line.empty()) {
                break;
            }
            p2.push_back(stoi(line));
        }
        input.close();
    }

    int count = 0;
    set<pair<vector<int>,vector<int>>> states;
    vector<int> winner = play_game(p1, p2, &states);
    int len = winner.size();
    for (auto& i : winner) {
        count += i * len;
        --len;
    }

    cout << count << "\n";


    return 0;
}