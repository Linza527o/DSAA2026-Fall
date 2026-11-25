//
// Created by Linza on 2026/11/23.
//

#include<iostream>
#include<vector>
using namespace std;
struct Node {
    int sta;
    int nbcnt;
    int cn; //city number
    vector<Node*> nb;
};




int main() {
    int cities;
    cin>>cities;
    Node* city[400000] = {new Node{-1,0,0}};
    int cnt = 0;
    while (cities--) {
        int a,b;
        cin>>a>>b;
        if (city[a]->sta == -1) {
            city[a] = new Node{0,0,a};
            cerr<<"done read in city "<<a<<endl;
        }
        if (city[b]->sta == -1) {
            city[b] = new Node{0,0,};
            cerr<<"done read in city "<<b<<endl;
        }
        city[a]->nb[city[a]->nbcnt++] = city[b];
        city[b]->nb[city[b]->nbcnt++] = city[a];
    }

    cerr<<"done read in cities"<<endl;
    // 接下来记录巨人的分布

    int ng = 0; //numofgiants
    cin>>ng;
    int gn = 0;//giant number
    while (ng--) {
        cin>>gn;
        city[gn]->sta = 1;
    }

    cerr<<"done read in giants"<<endl;


    // 这里层序遍历
    int nt = city[1]->nbcnt; //numoftrees
    // 数组越界问题？
    while (nt--) {
        Node* q[400000];
        //q是所有节点的队列
        int lcnt[400000];
        //lcnt是层级节点计数器
        int depth[400000];
        int rear = 0;
        //队列的尾巴
        int front = 0;
        //head

        q[rear] = city[1]->nb[nt];
        depth[rear] = 1;
        rear++;
        int deepest = 0;
        while (front < rear) {
            Node* cur = q[front];
            int layer = depth[front];
            front++;

            if (cur->sta == 1) {
                lcnt[front]++;
            }

            for (int j = 0;j<cur->nbcnt;j++) {
                Node* child = cur->nb[j];
                q[rear] = child;
                depth[rear] = layer + 1;
                rear++;
            }
            if (layer > deepest) {
                deepest = layer;
            }
        }

        for (int i = 0;i<deepest;i++) {
            if (lcnt[i] >=2) {
                lcnt[i+1]+= lcnt[i] - 1;
            }
        }
        cout<<deepest+lcnt[deepest]<<endl;
    }



}
