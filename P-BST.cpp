//
// Created by Linza on 2026/11/24.
//
#include<iostream>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
};
Node* root = nullptr;

Node* insert(Node* x,int val) {
    if (x == nullptr) {
        return new Node{val,nullptr,nullptr};
    }

    if (x->val > val) {
        x->left = insert(x->left,val);
    }
    if (x->val < val) {
        x->right = insert(x->right,val);
    }
    return x;
}

Node* search(Node* x,int tar) {
    if (x == nullptr) {
        return nullptr;
    }
    if (x->val == tar) {
        return x;
    }
    if (x->val > tar) {
        return search(x->left,tar);
    }
    if (x->val < tar) {
        return search(x->right,tar);
    }
}

Node* remove(Node* x,int tar) {
    if (x == nullptr) {
        return nullptr;
    }
    if (x->val > tar) {
        x->left = remove(x->left,tar);
    }
    else if (x->val < tar) {
        x->right = remove(x->right,tar);
    }
    else {
        //判断孩子的情况
        if (x->left == nullptr && x->right == nullptr) {
            return nullptr;
        }
        else if (x->left == nullptr) {
            return x->right;
        }
        else if (x->right == nullptr) {
            return x->left;
        }
        else {

        }
    }
}
