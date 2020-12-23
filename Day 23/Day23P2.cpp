#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct node {
    int data;
    node *next;
    node *prev;
};

int main() {
    string input = "158937462";
    vector<node*> cups;
    int total_cups = 1000000, first_idx = input[0] - '0' - 1, last_idx = total_cups - 1;

    for (int i = 1; i <= total_cups; ++i) {
        node *temp = new node;
        temp->data = i;
        cups.push_back(temp);
    }
    int len = input.size();
    for (int i = 0; i < len - 1; ++i) {
        cups[input[i] - '0' - 1]->next = cups[input[i + 1] - '0' - 1];
    }
    cups[input[len - 1] - '0' - 1]->next = cups[len];
    for (int i = len; i < last_idx; ++i) {
        cups[i]->next = cups[i + 1];
    }
    cups[last_idx]->next = cups[first_idx];
    for (int i = 1; i < total_cups; ++i) {
        cups[i]->prev = cups[i - 1];
    }
    cups[0]->prev = cups[last_idx];

    int count = 0;
    node *current = cups[first_idx];
    while (count < 10000000) {
        if (count % 1000000 == 0) cout << count <<"\n";
        set<int> current_three;
        node *head = current->next;
        current_three.insert(head->data);
        node *tail = head->next;
        current_three.insert(tail->data);
        tail = tail->next;
        current_three.insert(tail->data);
        node *temp = current->prev;
        current->next = tail->next;
        current = current->next;
        while (current_three.count(temp->data) == 1) {
            temp = temp->prev;
        }
        tail->next = temp->next;
        temp->next = head;
        ++count;
    }

    long result = 1;
    result *= cups[0]->next->data;
    result *= cups[0]->next->next->data;
    cout << cups[0]->next->data << "\n";
    cout << cups[0]->next->next->data << "\n";
    cout << result <<"\n";

    return 0;
}