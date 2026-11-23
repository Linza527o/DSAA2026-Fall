//
// Created by Linza on 2026/11/22.
//
#include<iostream>
#include<algorithm>
using namespace std;
// #define MAXN 1000000 + 5;
int w[1000000 + 5];
int c[1000000 + 5];
int tot = 0;
int ttc = 0; // total of c
int top() {
    return w[1];
}
void swap(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}
void modify(int x) {
    if (x == 1 || w[x] >= w[x/2]) {
        return;
    }
        swap(w[x/2],w[x]);
    // cerr<<"now modify"<<x/2<<endl;
        modify(x/2);

}
void repair(int x) {
    int tar = 2 * x;
    if (x*2 > tot) {
        // 子 左节点 已经超过了总数
        //说明这个是叶节点
        return;
    }
    if (x * 2 + 1 <= tot) {
        // 子右节点 还是小于总数
        // 说明我们不知道这个节点是不是叶结点
        // 但是我们需要在这种情况下 把更小的往上推，因为我们希望这个数是一个小根树
        if (w[2*x] > w[2*x+1]) {
            tar = 2 * x + 1;
        }
        else {
            tar = 2 * x;
        }
        if (w[tar]<w[x]) {
            swap(w[x],w[tar]);
            repair(tar);
        }
    }
    else if (w[x * 2]<w[x] ) {
        swap(w[x * 2],w[x]);
    }
}
void pop() {
    swap(w[1],w[tot--]);
    repair(1);
    // [cerr] cerr<<"now pop"<<w[tot + 1]<<endl;
}
void push(int x) {
    w[++tot] = x;
    modify(tot);
}
void printall() {
    for (int i = 1; i <= tot; i++) {
         // [cerr] cerr<<w[i]<<" ";
    }
    // [cerr] cerr<<endl;
}

void cmodify(int x) {
    if (x == 1 || c[x] >= c[x/2]) {
        return;
    }
    swap(c[x/2],c[x]);
    // cerr<<"now modify"<<x/2<<endl;
    cmodify(x/2);
}

void cpush(int x) {
    c[++ttc] = x;
    cmodify(ttc);
}




int main() {
    int t;
    cin>>t;
    while (t--) {
        tot = 0;
        int sum = 0;
        int ans = 0;
        int nums;
        cin>>nums;
        for (int i = 1; i <= nums; i++) {
            int in;
            cin>>in;
            push(in);
            printall();
        }
        while (tot != 1) {
            int tmptt = tot;
            for (int i = 1; i <= tmptt / 2; i++) {
                int s = 0;
                if (tot != 1) {
                    s += top();
                    pop();
                    s += top();
                    pop();
                    // [cerr] cerr<<"s is now "<<s<<endl;
                }
                else if (tot == 1){
                    s += top();
                    // [cerr] cerr<<"B s is now "<<s<<endl;
                    pop();
                }
                push(s);
                ans+=s;
                printall();
            }

        }
        cout<<ans<<endl;
    }
}