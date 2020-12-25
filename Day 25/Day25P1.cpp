#include <iostream>

using namespace std;

int main() {
    long key1 = 15733400, key2 = 6408062;
    long num = 1;
    int loop_size;
    bool s1 = false, s2 = false;
    int i = 0;
    while (true) {
        num = (num * 7) % 20201227;
        if (num == key1) {
            s1 = true;
            loop_size = i + 1;
        }

        if (num == key2) {
            s2 = true;
        }
        if (s1 && s2) {
            break;
        }
        ++i;
    }

    num = 1;
    for (int i = 0; i < loop_size; ++i) {
        num = (num * key2) % 20201227;
    }

    cout << num << "\n";


    return 0;
}