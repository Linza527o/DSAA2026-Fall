//
// Created by Linza on 2026/11/7.
//
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    int lines;
    cin>>lines;
    for (int k = 0;k<lines;k++) {
        string tmp;
        cin>>tmp;
        vector<char> in(tmp.begin(),tmp.end());
        vector<int> next(tmp.size(),0);
        for (int i = 0;i<tmp.size();i++) {
            if (i == 0) {
                next[i] = 0;
            }
            else {
                int j = next[i-1];
                while (in[j] != in[i] &&j>0) {
                    j = next[j-1];
                }
                if (in[j] == in[i]) {
                    j++;
                }
                next[i] = j;
            }
        }

        int n = tmp.size();
        int result = n;

        int p = next[n - 1];

        while (p > 0) {
            int len = n - p;
            int need = (len - n % len) % len;

            result = min(result, need);

            p = next[p - 1];
        }

        cout << result << '\n';


    }

}

/* 举个例子
 * w a w a w a
 * 0 0 1 2 1 2
 * a b c d a b c
 * 0 0 0 0 1 2 3
 * f a i l e d
 * 0 0 0 0 0 0
 * s u b w a y s u b w
 * 0 0 0 0 0 0 1 2 3 4
 * w a y s u b w a y
 * 0 0 0 0 0 0 1 2 3
 * a b a a
 * 0 0 1 1
 * a a c b a a a
 * 0 1 0 0 1 2 2
 */