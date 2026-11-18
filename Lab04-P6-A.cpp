//
// Created by Linza on 2026/10/31.
//
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
struct node {
    node* prev;
    node* next;
    int value;
    node(int value) {
        this->value = value;
        this->next = nullptr;
    }
};

node* eliminator(vector<node*>& nodes, node* start) {
    node* headcur = start;
    node* tailcur = start->next;
    node* firsteli;
    while (tailcur->value != INT_MAX ) {
        if (tailcur->value >= headcur->value) {
            tailcur = tailcur->next;
            headcur = headcur->next;
        }
        else if (tailcur->value < headcur->value) {
            firsteli = headcur->prev;
            node* keephead = headcur;
            // cerr<<"keep the head now to be "<<keephead->value<<endl;
            while (tailcur->value < headcur->value) {
                tailcur= tailcur->next;
                // cerr<<"tailcur updated to "<<tailcur->value<<endl;
                headcur = headcur->next;
                // cerr<<"headcur updated to "<<headcur->value<<endl;
            }
            tailcur->prev = keephead->prev;

            keephead->prev->next = tailcur;
            headcur = tailcur;

            if (tailcur->value == INT_MAX) {
                break;
            }

            tailcur = tailcur->next;
            // cerr<<"headcur updated to "<<headcur->value<<"after eli"<<endl;
            // // tailcur = tailcur->next;
            // cerr<<"tailcur updated to "<<tailcur->value<<"after eli"<<endl;
        }

    }
    return firsteli;
}

bool checkOrder(vector<node*>& nodes,node* start) {
    node* cur = start;
    while (cur->value != INT_MAX) {
        if (cur->next->value < cur->value) {
            return false;
        }
        cur = cur->next;
    }
    return true;
}


int main() {
    int lines;
    cin>>lines;
    for (int i = 1; i <= lines; i++) {
        int nums;
        cin>>nums;

        vector<node*> nodes(nums + 2);
        nodes[0] = new node(0);
        node *cur = nodes[0];
        nodes[nums+1] = new node(INT_MAX);






        for (int i = 1; i <= nums; i++) {
            int tvalue;
            cin>>tvalue;
            nodes[i] = new node(tvalue);
        }




        for (int i = 0; i <= nums; i++) {
            nodes[i]->next = nodes[i + 1];
        }
        for (int i = nums+1; i > 0; i--) {
            nodes[i]->prev = nodes[i - 1];
        }

        // while (cur!=nodes[nums+1]->prev) {
        //
        //     cur = cur->next;
        //     cout<<cur->value<<" ";
        // }
        // cout<<endl;

        node *chkstart = nodes[0];
        while (!checkOrder(nodes,chkstart)) {
            chkstart = eliminator(nodes,chkstart);
        }



        while (cur->next->value != INT_MAX) {

            cur = cur->next;
            cout<<cur->value<<" ";
        }
        cout<<endl;
    }

}