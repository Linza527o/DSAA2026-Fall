//
// Created by Linza on 2026/11/18.
//
#include<iostream>
#include<vector>
using namespace std;
struct Node {
    int val;
    Node* left;
    Node* right;
};

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int NN;
        Node *root;
        cin>>NN;
        vector<Node*> a(1024,nullptr);
        vector<int> hasParent(1024);
        if (NN == 1) {
            int tmp;
            cin>>tmp;
            a[tmp] = new Node{tmp,nullptr,nullptr};
        }
        else {
            for (int i = 0; i < NN - 1; i++) {
                int par,chi;
                cin>>par>>chi;
                if (a[par] == nullptr) {
                    a[par] = new Node{par,nullptr,nullptr};
                }
                if (a[chi] == nullptr) {
                    a[chi] = new Node{chi,nullptr,nullptr};
                }

                if (a[par]->left == nullptr) {
                    a[par]->left = a[chi];
                    hasParent[chi] = 1;
                }
                else {
                    a[par]->right = a[chi];
                    hasParent[chi] = 1;
                }


            }
        }
        for (int j = 0; j < 1024; j++) {
            if (hasParent[j] == 0 && a[j] != nullptr) {
                root = a[j];
                break;
            }
        }

        vector<Node*> queue;
        queue.push_back(root);
        while (!queue.empty()) {
            if (queue.front()->left != nullptr) {
                queue.push_back(queue.front()->left);
            }
            if (queue.front()->right != nullptr) {
                queue.push_back(queue.front()->right);
            }
            cout<<queue.front()->val<<" ";
            queue.erase(queue.begin());
        }
        cout<<"\n";
    }

}