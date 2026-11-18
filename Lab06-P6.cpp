//
// Created by Linza on 2026/11/15.
//
/*b c d e f g h i j k l m n o p q r s t u v w x y z a
bcdeabc
密文 - 原文
密密文 - 密文
密文 - 原文 - 密密文 - 密文
密文 是 最长公共前后缀
*/

#include <iostream>
#include <vector>
using namespace std;
int main() {
    char cipher[26] ={0};
    char tmp;
    for (int i = 0; i < 26; i++) {
        cin>>tmp;
        if (tmp != ' ') {
            cipher[i] = tmp;
        }
    }
    // for (char c: cipher) {
    //     cout<<c<<" ";
    // }
    // cout<<endl;
    string in;
    cin>>in;
    int n = in.length();

    for (int i = 0; i < n; i++) {
        in += cipher[in[i] - 'a'];
    }
    // cout<<in<<endl;
    vector<int> next(in.length(),-1);
    for (int i = 0; i < in.length(); i++) {
        if (i == 0) {
            next[0] = 0;
        }
        else {
            int j = next[i - 1];

            while (j > 0 && in[j] != in[i]) {
                j = next[j - 1];
            }

            if (in[j] == in[i]) {
                j++;
            }

            next[i] = j;

        }
    }
    int k = next[in.length() - 1];
    while (next[in.length() - 1] > in.length()/4  && k> 0) {
        // cout<<"k is now "<<k<<endl;
        next[in.length() - 1] = k;
        k = next[k - 1];
    }

    // for (int i: next) {
    //     cout<<i<<" ";
    // }
    // cout<<endl;
    int ans = 0;
    if (in.length() / 2 - next[in.length() - 1] != 0) {
        ans = in.length() / 2 - next[in.length() - 1];
    }
    else {
        ans = in.length() / 2;
    }
    cout<< ans << " ";



}