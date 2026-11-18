//
// Created by Linza on 2026/10/21.
//
#include<iostream>
using namespace std;
struct node {
    int coe;
    int exp;
    node* next;
    node(int coe, int exp) {
        this->coe = coe;
        this->exp = exp;
        this->next = NULL;
    }
};

int main() {
    int lines;
    cin>>lines;
    for (int k = 0; k < lines; k++) {
        int n;
        int coe,exp;
        cin>>n;
        node* head = new node(-1,-1);
        node* cur = head;
        for (int j = 0; j < n; j++) {
            cin>>coe>>exp;
            node* temp =new node(coe,exp);
            cur->next = temp;
            cur = cur->next;
        }
        node* tail = new node(1000000001,1000000001);
        cur->next = tail;
        int m;
        cin>>m;

        cur = head;

        for (int j = 0; j < m; j++) {
            cin >> coe >> exp;
            node* temp = new node(coe, exp);

            while (cur->next != tail &&
                   cur->next->exp < temp->exp) {
                cur = cur->next;
                   }

            if (cur->next != tail &&
                temp->exp == cur->next->exp) {
                cur->next->coe += temp->coe;
                delete temp;
                }
            else {
                temp->next = cur->next;
                cur->next = temp;
            }
        }

        int q;
        cin >> q;
        cur = head->next;

        for (int j = 0; j < q; j++) {
            int i;
            cin >> i;

            while (cur != tail && cur->exp < i) {
                cur = cur->next;
            }

            if (cur != tail && cur->exp == i) {
                cout << cur->coe<<" ";
            }
            else {
                cout << 0 << " ";
            }
        }
    cout << endl;
    }

}