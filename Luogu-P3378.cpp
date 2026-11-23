//
// Created by Linza on 2026/11/22.
//
#include<iostream>
using namespace std;

int w[10000000];
int tot = 0;

void swap(int &x,int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}

void modify(int x) {
    if (x == 1||w[x] >= w[x/2]) {
        return;
    }
    else {
        swap(w[x],w[x/2]);
        modify(x/2);
    }
}
void push(int x) {
    w[++tot] = x;

    modify(tot);
}
int top() {
    return w[1];
}
void repair(int x) {
    int tar;
    if (x * 2> tot) { //说明是叶节点
        return;
    }
    if (x * 2  + 1 <= tot) {
        if (w[x*2]>w[x*2+1]) {
            tar = x * 2 + 1;
        }
        else {
            tar = x * 2;
        }
        if (w[tar]<w[x]) {
            swap(w[x],w[tar]);
            repair(tar);
        }
    }
    else if (w[x*2] < w[x]) {
        swap(w[x], w[x*2]);
    }
}
void pop() {
    swap(w[1],w[tot--]);
    repair(1);
}

int main() {
    int nums;
    int op;
    cin>>nums;



    for (int i = 0;i<nums;i++) {
        cin>>op;
        if (op == 1) {
            int toadd;
            cin>>toadd;
            push(toadd);
        }
        else if (op == 2) {
            cout<<top()<<endl;
        }
        else {
            pop();
        }
    }
}