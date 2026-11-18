//
// Created by Linza on 2026/10/31.
//
#include<iostream>
#include<vector>
using namespace std;
struct node {
    int value;
    int index;
    node* prev;
    node* next;
    node(int value, int index) {
        this->value = value;
        this->index = index;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

void mergeSort(vector<node> &nodes, int l, int r) {
    if (l>=r){return;}
    int mid = (l+r)/2;
    mergeSort(nodes, l, mid);
    mergeSort(nodes, mid+1, r);

    vector<node> tmp;
    int i = l;
    int j = mid + 1;
    while (i<=mid && j<=r) {
        if (nodes[i].value < nodes[j].value) {
            tmp.push_back(nodes[i]);
            i++;
        }
        else {
            tmp.push_back(nodes[j]);
            j++;
        }
    }
    while (i<= mid) {
        tmp.push_back(nodes[i]);
        i++;
    }
    while (j<=r) {
        tmp.push_back(nodes[j]);
        j++;
    }

    for (int k = 0;k<tmp.size();k++) {
        nodes[k+l] = tmp[k];
    }


}

void connection(vector<node> &nodes) {
    for (int i = 0; i < nodes.size() - 1; i++) {
        nodes[i].next = &nodes[i+1];
    }
    for (int i = nodes.size() - 1; i > 0; i--) {
        nodes[i].prev = &nodes[i-1];
    }
}


int main() {
    int nums;
    cin>>nums;
    vector<node> nodes;
    vector<node*> nodesOriginalRank(nums+2);
    nodes.reserve(nums+2);
    nodesOriginalRank.reserve(nums+2);
    node head(-1,0);

    nodes.push_back(head);
    for (int i = 1; i <= nums; i++) {
        int value;
        cin>>value;
        node tmp = node(value,i);
        nodes.push_back(tmp);


    }

    node tail(-1,nums+1);
    nodes.push_back(tail);
    mergeSort(nodes, 1, nums);
    // for (int k = 0;k<nodes.size();k++) {
    //     cout<<nodes[k].value<<" ";
    // }
    connection(nodes);
    for (int i = 1; i <= nums; i++) {
        nodesOriginalRank[nodes[i].index] = &nodes[i];
    }
    // for (int i = 1; i <= nums; i++) {
    //     cout<<nodesOriginalRank[i]->value<<" ";
    // }
    for (int i = 1; i < nodesOriginalRank.size() - 2; i++) {
        // cerr<<"current prev: "<<nodesOriginalRank[i]->prev->value<<endl;
        // cerr<<"current next: "<<nodesOriginalRank[i]->next->value<<endl;
        if (nodesOriginalRank[i] ->prev != &nodes.front()) {
            cout<<min(abs(nodesOriginalRank[i]->next->value - nodesOriginalRank[i] ->value),
                abs(nodesOriginalRank[i]->prev->value - nodesOriginalRank[i] ->value));
            cout<<" ";
        }
        else {
            cout<<abs(nodesOriginalRank[i]->next->value - nodesOriginalRank[i] ->value);
            cout<<" ";
        }
        nodesOriginalRank[i]->prev->next = nodesOriginalRank[i]->next;
        nodesOriginalRank[i]->next->prev = nodesOriginalRank[i]->prev;

        // cerr<<"inner status :";
        // node *cur = &nodes.front();
        // while (cur != &nodes.back()) {
        //     cerr<<cur->value<<" ";
        //     cur = cur->next;
        // }
        // cerr<<endl;

    }


}