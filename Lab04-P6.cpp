//
// Created by Linza on 2026/11/1.
//
#include <iostream>
#include <vector>
#include <climits>


using namespace std;

struct node {
    int value;
    node *next;
    node *prev;
    node(int value) {
        this->value = value;
    }
};

void mergesuslist(vector<node*>& suslist) {
    vector<node*> tmp;
    tmp.push_back(suslist[0]);

    for (int i = 1;
         i + 1 < suslist.size() - 1;
         i += 2) {

        node* head = suslist[i];
        node* tail = suslist[i + 1];

        if (tmp.size() > 1 &&
            (tmp.back() == head ||
             tmp.back()->next == head)) {

            tmp.back() = tail;
             }
        else {
            tmp.push_back(head);
            tmp.push_back(tail);
        }
         }

    tmp.push_back(suslist.back());
    suslist.swap(tmp);
}

void deletenode(vector<node *> &suslist) {
    for (int i = 1; i < suslist.size() - 2; i+=2) {
        suslist[i]->prev->next = suslist[i+1]->next;
        suslist[i+1]->next->prev = suslist[i]->prev;
    }
}

void fillsuslist(vector<node *> &suslist) {
    if (suslist.size() == 2) {
        return;
    }

    //suslist 的单数放头 双数放尾巴
    mergesuslist(suslist);
    deletenode(suslist);



    //suslist只剩头尾
    vector<node *> tmpsuslist;
    tmpsuslist.push_back(new node(-1));
    for (int i = 1; i < suslist.size() - 2; i+=2) {
        node* head = suslist[i] -> prev;
        node* tail = head -> next;
            if (head->value > tail->value) {
                tmpsuslist.push_back(head);
                tmpsuslist.push_back(tail);
            }
    }
    tmpsuslist.push_back(new node(INT_MAX));
    suslist.swap(tmpsuslist);
    fillsuslist(suslist);
}







int main() {
    int lines;
    cin>>lines;
    for (int i = 0; i < lines; i++) {
        int nums;
        cin>>nums;
        vector<node *> nodes;
        nodes.push_back(new node(-1));
        for (int j = 1; j <= nums; j++) {
            int value;
            cin>>value;
            nodes.push_back(new node(value));
        }
        int max = INT_MAX;
        nodes.push_back(new node(INT_MAX));

        //connect
        for (int i = 1; i <= nums+1; i++) {
            nodes[i]->prev = nodes[i-1];
        }
        for (int i = 0; i < nums+1; i++) {
            nodes[i]->next = nodes[i+1];
        }
        //

        vector<node*> suslist;
        suslist.push_back(nodes[0]);

        for (int i = 1; i < nums; i++) {
            if (nodes[i]->value > nodes[i+1]->value) {
                suslist.push_back(nodes[i]);
                suslist.push_back(nodes[i+1]);
            }
        }

        suslist.push_back(nodes[nums+1]);

        fillsuslist(suslist);


        //cout
        node *cur = nodes[0]->next;
        while (cur -> value != INT_MAX) {

            cout << cur -> value << " ";
            cur = cur -> next;
        }
        cout << endl;
    }
}