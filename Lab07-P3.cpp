//
// Created by Linza on 2026/11/19.
//
#include<iostream>
#include<vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int edge,num = 0;
    cin>>edge>>num;
    vector<vector<pair<int,int>>> adj(edge + 1,vector<pair<int,int>>());
    for (int i = 0;i < edge - 1;i++) {
        int a,b,w;
        cin>>a>>b>>w;
        adj[a].push_back({b,w});
        adj[b].push_back({a,w});
    }


    // the first very lines are for the construction of the tree
    // [cerr] cerr<<"input complete"<<endl;
    vector<int> cost(edge+1,0);
    vector<int> ans;
    vector<int> checked(edge+1,0);
    vector<int> queue;
    int i = 1;
    queue.push_back(i);
    checked[1] = 1;
    int j = 0;
    while (j<queue.size()) {
        i = queue[j];
        // [cerr] cerr<<"i is now "<<i<<endl
        j++;
        for (int j = 0;j < adj[i].size();j++) {
            if (checked[adj[i][j].first] == 0) {
                cost[adj[i][j].first] = (adj[i][j].second + cost[i]);
                // [cerr] cerr<<"cost of "<<adj[i][j].first<<" is now "<<cost[adj[i][j].first]<<endl;
                // 被连接数的cost 为上一节点的cost + 这条边的长度
                queue.push_back(adj[i][j].first);
                // [cerr] cerr<<"queue add "<<adj[i][j].first<<endl;
                // 队列添加此项 便于层序遍历
                checked[adj[i][j].first] = 1;
               //标记已检查状态，防止反复计数
            }
        }
        if (adj[i].size() == 1 && cost[i] == num) {
            //前一个条件判断是否为叶节点 如果是叶节点 那么第二个条件判断是否满足长度要求
            ans.push_back(i);
            //如果是 则添加到答案集
        }
    }
    cout<<ans.size()<<endl;
}