//
// Created by Linza on 2026/11/7.
//
#include<vector>
#include<iostream>
using namespace std;
int main() {
    char tmp;
    vector<char> s;

    while (cin.get(tmp)&& tmp != '\n') {
        if (tmp != '\r') {
            s.push_back(tmp);
        }
    }
    vector<int> next(s.size());
    for (int i = 0; i < s.size(); i++) {
        if (i == 0) {
            next[i] = 0;
        }
        else {
           int j = next[i-1];
           while (s[j] != s[i] && j>0) {
               j = next[j-1];
               //继续向前查找可能可以匹配的前缀
           }
           if (s[j] == s[i]) {
               j++;
               //如果从原来的next值那里能够匹配上 则长度++
           }

            next[i] = j;
        }
        cout<<next[i]<<endl;
    }
}
/*
 * 我的理解是这样的
 *  a b a b a c
 *  0 1 2 3 4 5
 *  0 0 1 2 3 0
 *
 *  a b a b a
 *  0 1 2 3 4
 *  0 0 1 2 3
 *
 *  a b a b
 *  0 1 2 3
 *  0 0 1 2
 *  假设我们现在加上c 我们需要判断的事情是 加上c之后 现在的真后缀 和真前缀 他们的最大值是多少
 *  那我们就考虑一下 假设 加上了c 前面一位说 到这里 我能够确保最长的是长度为三的前缀和后缀
 *  现在 检查我们能不能增大最长匹配真前缀和真后缀的长度， 我们在0123 的情况下 增加了 第 5位 a 假设
 *  假设这个a可以增大我们的最长匹配缀值 那我们就应该检查并且确保 新增的这一位至少在 第 a[next[j-1]]位上是和它相等的
 *
 *  举一个另外的例子
 *  a b c a
 *  0 1 2 3
 *  0 0 0 1
 *  这时候我们增加一位 就应该去 b那一位检查
 *
 *  a b b a d c
 *  0 0 1 2 0 0
 *  这时候我们新增一位 就应该去第一位那里检查
 *
 *  a b b a
 *  0 1 2 3
 *  0 0 0 1
 *  这时候我们新增一位就应该去第三位 a[1]那里检查
 *  假设 新增的是 a
 *  发现不匹配 那我们就 去a[0]那里检查
 *  发现匹配
 *  更新数值为 0 + 1 = 1;
 */

