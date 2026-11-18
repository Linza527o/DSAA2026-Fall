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
        for (int i = 0; i < NN - 1; i++) {
            int par,chi;
            cin>>par>>chi;
            if (a[par] == nullptr) {
                a[par] = new Node{par,nullptr,nullptr};
            }
            else {
                a[chi] = new Node{chi,nullptr,nullptr};
                if (a[par]->left == nullptr) {
                    a[par]->left = a[chi];
                    hasParent[chi] = 1;
                }
                else if (a[par]->right == nullptr) {
                    a[par]->right = a[chi];
                    hasParent[chi] = 1;
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
            while (!queue.isEmpty()) {
                if (queue.front()->left != nullptr) {
                    queue.push_back(queue.front()->left);
                }
                if (queue.front()->right != nullptr) {
                    queue.push_back(queue.front()->right);
                }
                cout<<queue.front()->val<<endl;
                queue.erase(queue.begin());
            }

        }
    }
}