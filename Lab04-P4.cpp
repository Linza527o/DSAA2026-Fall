//
// Created by Linza on 2026/10/27.
//
#include <iostream>
#include<vector>
using namespace std;
struct node {
    node* prev;
    node* next;
    char val;
    node(char val) {
        next = nullptr;
        prev = nullptr;
        this->val = val;
    }


};
int main() {
    int lines;
    cin>>lines;
    for(int k=0;k<lines;k++) {
        int len = 0;
        cin>>len;
        node head = node(-1);
        node tail = node(-1);
        head.next = &tail;
        tail.prev = &head;
        node* cur = &tail;
        bool replacing = false;
        for(int i=1;i<=len;i++) {
            char tmp;
            cin>>tmp;
            if ('0'<=tmp&&tmp<='9') {
                node* nt = new node(tmp);
                nt->next = cur;
                nt->prev = cur->prev;

                cur->prev->next = nt;
                cur->prev = nt;
                if (replacing) {
                    cur = nt;
                    replacing = false;
                }
            }
            if (tmp == 'r') {
                if (i == len) {
                    continue;
                }
                if (cur != &tail) {
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                    cur = cur->next;
                }
                replacing = true;
            }
            if (tmp == 'I') {
                cur = head.next;
            }
            if (tmp == 'H') {
                if (cur->prev != &head) {
                    cur = cur->prev;
                }
            }
            if (tmp == 'L') {
                if (cur != &tail) {
                    cur = cur->next;
                }
            }
            if (tmp == 'x') {
                if (cur != &tail) {
                    node* deleted = cur;

                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;

                    cur = cur->next;
                    delete deleted;
                }
            }
        }
        cur = head.next;
        while (cur != &tail) {
            printf("%c", cur->val);
            cur = cur->next;
        }
        cout<<endl;


    }

}