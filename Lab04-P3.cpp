//
// Created by Linza on 2026/10/26.
//
#include <iostream>
#include <vector>
using namespace std;
struct node {
    int num;
    node* next;
    node* prev;
    node(int num) {
        this->num = num;
        prev = nullptr;
        next = nullptr;
    }
    node() {
        prev = nullptr;
        next = nullptr;
    }
};
int main () {
    int lines;
    cin >> lines;
    for (int k = 0; k < lines; k++) {
        int nums,rows;
        cin >> nums >> rows;
        vector<node*> team;
        team.push_back(new node(-1));
        for (int j = 0; j < nums; j++) {
            int tmpnum;
            cin >> tmpnum;
            // cout << tmpnum << " ";
            team.push_back(new node(tmpnum));
        }
        team.push_back(new node(-2));

        for (int j = 0; j <= nums; j++) {
            team[j]->next = team[j+1];
            team[j+1]->prev = team[j];
        }
        vector<node*> arr(nums+1,nullptr);
        for (int i = 1; i <= nums; i++) {
            arr[team[i]->num] = team[i];
        }

        for (int i = 0; i < rows; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            node* xt1 = arr[x1]->prev;
            node* xt2 = arr[x2]->prev;
            node* yt1 = arr[y1]->next;
            node* yt2 = arr[y2]->next;

            if (yt1 == arr[x2]) {

                xt1->next = arr[x2];
                arr[x2]->prev = xt1;

                arr[y2]->next = arr[x1];
                arr[x1]->prev = arr[y2];

                arr[y1]->next = yt2;
                yt2->prev = arr[y1];
            }
            else {

                xt1->next = arr[x2];
                arr[x2]->prev = xt1;

                arr[y2]->next = yt1;
                yt1->prev = arr[y2];

                xt2->next = arr[x1];
                arr[x1]->prev = xt2;

                arr[y1]->next = yt2;
                yt2->prev = arr[y1];
            }
        }
        node* cur = team[0]->next;
        for (int i = 0; i < nums; i++) {
            printf("%d ", cur->num);
            cur = cur->next;
        }
        cout<<endl;
    }
}