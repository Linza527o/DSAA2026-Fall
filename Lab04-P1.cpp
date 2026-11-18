//
// Created by Linza on 2026/10/26.
//

#include <iostream>
#include <vector>
using namespace std;
struct node {
    int dishnumber;
    node* next;
    node* prev;
    node(int dishnumber, node* next) {
        this->dishnumber = dishnumber;
        this->next = nullptr;
        this->prev = nullptr;
    }

};



int main () {
    int lines;
    cin >> lines;
    for (int i = 0; i < lines; i++) {
        int dishes;
        cin >> dishes;
        int takenum;
        cin >> takenum;
        vector<node*> dishlist;
        dishlist.push_back(new node(-1, nullptr));
        for (int j = 1; j<= dishes; j++) {
            dishlist.push_back(new node(j, nullptr));
        }
        for (int j = 1; j < dishes; j++) {
            dishlist[j]->next = dishlist[j+1];
        }
        for (int j = dishes; j > 1; j--) {
            dishlist[j]->prev = dishlist[j-1];
        }
        dishlist[1]->prev = dishlist[dishes];
        dishlist[dishes]->next = dishlist[1];
        // for (int i = 0; i <= dishes; i++) {
        //     printf("%d ", dishlist[i]->dishnumber);
        //
        // }

        node* cur = dishlist[(takenum - 1) % dishes + 1];
        while (cur->next != cur) {
            printf("%d ", cur->dishnumber);
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            cur = cur->prev;
            for (int j = 0; j < takenum; j++) {
                cur = cur->next;
                // printf("current cur = %d\n", cur->dishnumber);
            }
        }
        printf("%d ", cur->dishnumber);
        cout<<endl;
    }


}
