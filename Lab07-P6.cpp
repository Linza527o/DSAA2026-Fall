//
// Created by Linza on 2026/11/23.
//
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Node {

    int e;
    int p;
    int l; //layer
    vector<Node*> nb;
    Node* next;
};

int main() {
    int visited[200000] = {0};
    int isLeaf[200000] = {0};
    Node* lycnt[200000] = {};
    int t = 0;
    cin>>t;
    int pmax = 0;

    Node* nodes[200000] ={};

    for (int m = 0; m < t - 1; m++) {
        t--;
        int a,b;
        cin>>a>>b;
        if (nodes[a] == NULL) {
            nodes[a] = new Node{0,0};
        }
        if (nodes[b] == NULL) {
            nodes[b] = new Node{0,0};
        }
        nodes[a]->nb.push_back(nodes[b]);
        nodes[b]->nb.push_back(nodes[a]);
    }
    for (int m = 0;m<t;m++) {
        int tmp;
        cin>>tmp;
        nodes[m]->p = tmp;
        if (nodes[m]->nb.size() == 1) {
            isLeaf[m] = 1;
            nodes[m]->e = nodes[m]->p;
        }
        pmax = max(pmax,nodes[m]->p);
    }

    //以上是读入，现在我们有了每一个节点之间的连接关系
    //接下来要做的事情是 从最深处往上走

    nodes[pmax]-> l = 0;

    lycnt[0]++;
    vector<Node*> q;
    q.push_back(nodes[pmax]);
    //先保留那个进队的逻辑

    while (q.size()<t) {
        for (Node* child: q.front()->nb) {
            q.push_back(child);
            if (lycnt[q.front()->l+1] == NULL) {
                lycnt[q.front()->l+1] = child;
            }
            else{
                lycnt[q.front()->l+1]->next = lycnt[q.front()->l+1]->next->next;
                lycnt[q.front()->l+1]->next = child;
            }
        }
    }







}
