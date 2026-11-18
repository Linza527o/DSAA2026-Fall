//
// Created by Linza on 2026/10/28.
//
#include <iostream>
#include <vector>

using namespace std;

int main() {
    char tmp;
    int MOD = 514329;
    vector<char> stack;
    vector<int> values;


    stack.push_back(0);
    values.push_back(0);
    while (cin.get(tmp)) {
        if (tmp == '\n') {
            break;
        }
        if (tmp == '(') {
            stack.push_back(tmp);
            values.push_back(0);
        } else if (tmp == ')') {
            stack.pop_back();
            if (values.back() == 0) {
                values.pop_back();
                values.back() = (values.back() + 1) % MOD;
            } else {
                int t = values.back();
                values.pop_back();
                values.back() = (values.back() +  t * 2) % MOD;
            }
        }
    }
    cout << values[0] << endl;
}
