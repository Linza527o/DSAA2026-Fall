//
// Created by Linza on 2026/11/17.
//
#include<iostream>
#include<vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;


};

int main() {
    int lines;
    cin>>lines;
    vector<TreeNode> nodes(1024,{-1,nullptr,nullptr});
    for (int k = 0; k < lines; k++) {
        int nums;
        cin>>nums;
        TreeNode *root = nullptr;
        for (int j = 0; j < nums - 1; j++) {
            int parentval;
            cin>>parentval;
            if (nodes[parentval].val == -1) {
                TreeNode* tmpp = new TreeNode{parentval,nullptr,nullptr};
                nodes[parentval] = *tmpp;
                root = tmpp;
            }
            int tmp;
            cin>>tmp;
            TreeNode *toAdd = new TreeNode{tmp,nullptr,nullptr};
            nodes[tmp] = *toAdd;
            if (nodes[parentval].left == nullptr) {
                nodes[parentval].left = toAdd;
                cout<<"add to left of "<< parentval<<endl;
            }
            else {
                nodes[parentval].right = toAdd;
                cout<<"add to right of "<< parentval<<endl;
            }
        }
    //do the traversal here


        vector<TreeNode> q;
        q.push_back(*root);


        while (!q.empty()) {
            TreeNode tmp = q.front();
            if (tmp.left != nullptr) {
                q.push_back(*tmp.left);
                cout<<"now push back "<< tmp.left->val <<endl;
            }
            if (tmp.right != nullptr) {
                q.push_back(*tmp.right);
                cout<<"now push back "<< tmp.right->val <<endl;
            }
            cout<<q.front().val<<' ';
            q.erase(q.begin());
        }
    }
}
