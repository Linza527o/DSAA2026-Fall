//
// Created by Linza on 2026/11/25.
//
#include<iostream>
#include<cmath>
using namespace std;
long long w[10000000] = {};
long long Index[10000000] = {};
int tot = 0;
void swap(long long  &a,long long &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
void modify(int x) {
    if (x == 1 || w[x/2] >= w[x]) {
        return;
    }
    swap(w[x/2],w[x]);
    int tmp = Index[x/2];
    Index[x/2] = Index[x];
    Index[x] = tmp;
    modify(x/2);
}

void push(int x) {
    w[++tot]  = x;
    Index[tot] = tot;
    modify(tot);
}

void printall() {
    cerr<<"printall: ";
    int tmp = tot;
    while (tmp--) {
        cerr<<tmp<<": "<<w[tmp]<<endl;

    }

}

int main() {
    int t;
    cin>>t;
    int nums;
    int its; //index to search
    while (t--) {
        tot = 0;
        cin>>nums;
        while (nums--) {
            int tmp;
            cin>>tmp;
            push(tmp);
        }
        // printall();
        cin>>its;

        // 寻找原始编号为 its 的节点
        int pos = 1;
        while (Index[pos] != its) {
            pos++;
        }

        // 计算层数及层内位置
        int p = 0;
        while ((1 << (p + 1)) <= pos) {
            p++;
        }

        cout << p + 1 << " "
             << pos - (1 << p) + 1 << endl;

    }

}