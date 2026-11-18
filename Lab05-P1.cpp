//
// Created by Linza on 2026/10/28.
//
#include <vector>
#include<iostream>
using namespace std;

int main() {
    int lines;
    cin >> lines;
    for (int i = 0; i < lines; i++) {
        int nums;
        cin >> nums;
        vector<char> s(nums+2);
        char tmp;
        int top = 1;
        bool valid = true;
        for (int i = 0; i < nums; i++) {
            cin >> tmp;
            // cout<<"read "<<tmp<<endl;
            if (tmp == '(' || tmp == '{' || tmp == '[') {
                s[top] = tmp;
                top++;
            }
            else if (top == 1) {
                valid = false;
            }
            else if (tmp == ')' ) {
                if (s[top-1] == '(') {
                    s[top] = ' ';
                    top--;
                }
            }
            else if (tmp == '}') {
                if (s[top-1] == '{') {
                    s[top] = ' ';
                    top--;
                }
            }
            else if (tmp == ']'){
                if (s[top-1] == '[') {
                    s[top] = ' ';
                    top--;
                }
            }
            else {
                valid = false;
            }
        }
        if (top != 1 || !valid) {
            cout<<"NO"<<endl;
        }
        else {
            cout<<"YES"<<endl;
        }
    }

}