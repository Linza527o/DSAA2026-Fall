//
// Created by Linza on 2026/11/4.
//
#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main() {
    int lines;
    cin >> lines;
    // cerr << lines << endl;

    for (int k = 0; k < lines; k++) {
        // cout<<k<<endl;
        string tmp;
        cin>>tmp;
        // cerr << tmp << endl;
        // vector<string> strs;
        // for (int i = 1; i <= tmp.size(); i++) {
        //     for (int j = 0;j + i  - 1< tmp.size(); j++) {
        //         strs.push_back(tmp.substr(j,j+i-1));
        //         // cerr<<"pushed back "<<j<<"to"<<j+i-1<<endl;
        //     }
        // }
        // for (int i = 0; i < strs.size() - 1; i++) {
        //     for (int j = i + 1;j< strs.size(); j++) {
        //         if (strs[j] == strs[i]) {
        //             strs.erase(strs.begin() + j);
        //         }
        //
        //     }
        // }
        int s = tmp.length();
        cout << (s+1)*(s)/2 << endl;
    }
}