//
// Created by Linza on 2026/11/20.
//
#include<iostream>
#include<vector>

using namespace std;
struct Node {
    Node* left;
    Node* right;
    Node* far;
    int val;
};

int main() {
    int T;
    cin>>T;
    for (int t = 1; t <= T; t++) {
        int node;
        cin>>node;
        int rt;
        cin>>rt;
        Node root = Node{nullptr,nullptr,nullptr,rt};

        int sum = 0;
        int cost = 0;

        for (int i = 0; i < node - 1; i++) {
            int tmp;
            cin>>tmp;
            Node* newnode = new Node{nullptr,nullptr,nullptr,tmp};
            sum+=tmp;

            while (true) {
                Node* cur = &root;
                if (tmp>cur->val) {
                    if (cur->right == nullptr) {
                        cur->right = newnode;
                        newnode->far = cur;
                        break;
                    }
                    else {
                        cur = cur->right;
                    }
                }
                else {
                    if (cur->left == nullptr) {
                        cur->left = newnode;
                        newnode->far = cur;
                        break;
                    }
                    else {
                        cur = cur->left;
                    }
                }
            }

        }
        int sumcopied = sum;
        // [cerr] cerr<<sum<<endl;

        // the upper part is the read and construct part
        // the following part is the output part, we will traverse from the biggest to the smallest.

        Node* re = &root;

        while (true) {
            if (re->right != nullptr) {
                re = re->right;
            }
            else {
                if (re->left == nullptr) {
                    cost += (sum - re->val);
                    sum -= re->val;
                    // [cerr] cerr<<"A sum is now "<<sum<<endl;
                    // cout<<re->val<<endl;
                    re = re->far;
                    re->right = nullptr;
                }
                else {
                    cost += (sum - re->val);
                    sum -= re->val;
                    // [cerr] cerr<<"B sum is now "<<sum<<endl;
                    // cout<<re->val<<endl;
                    re = re->far;
                    re->right = re->right->left;
                    re->right->far = re;
                }
            }


            if (re == &root && re->left == nullptr && re->right == nullptr) {
                // cout<<re->val<<endl;
                cost+= sumcopied;
                cost-= rt;
                // [cerr] cerr<<"sum is now "<<sum<<endl;
                cout<<cost<<endl;
                break;
            }

        }




    }
}
