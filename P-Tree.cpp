//
// Created by Linza on 2026/11/17.
//
#include<iostream>
#include<vector>
struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    int val;
};
struct Tree {

    TreeNode *root;
    int addChild(TreeNode *root, int val) {
        TreeNode *newNode = new TreeNode{nullptr, nullptr, val};
        if (root == nullptr) {
            root = newNode;
            return 1;
        }
        if (root->left == nullptr) {
            root->left = newNode;
            return 1;
        }
        else {
            root->right = newNode;
            return 1;
        }
    }
    int addAt(TreeNode *root,int level,int dir, int val) {
        TreeNode *temp = root;
        for (int i = 0; i < level; i++) {
           temp = temp->left;
        }
    }

    int PreOrderTraversal(TreeNode *root) {
        PreOrderTraversal(root->left);
        if (root->left != nullptr) {
            PreOrderTraversal(root->left);
        }
        else if (root->right != nullptr) {
            PreOrderTraversal(root->right);
        }
        else {
            cout<<root->val<<endl;
            return 1;
        }
    }

};

int main() {
    Tree t;
    TreeNode *root = new TreeNode{nullptr, nullptr, 26};
    vector<in> input = {26,12,4,18,14,24,32};
    for (int i = 0; i < input.size(); i++) {
        addChild(root->left, input[i]);
    }

}