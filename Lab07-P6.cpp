#include<iostream>
#include<vector>
using namespace std;
#define MAXN 1000000 + 5
int rootNode = 1;
long long totalEnergy = 0;
int at[MAXN]; //ACTIVATION THRESHOLD
int stm[MAXN]; //SUBTREE MAX
vector<int> adj[MAXN];
void dfs(int node,int parent) {
    int largestE = 0;
    int secondlargestE = 0;
    for (int c:adj[node]) {
        if (c == parent) {
            continue;
        }
        dfs(c,node);
    }
    for (int c:adj[node]) {
        if ( c == parent) {
            continue;
        }
        int cE = stm[c];
        if (cE > largestE) {
            secondlargestE = largestE;
            largestE = cE;
        }
        else if (cE > secondlargestE) {
            secondlargestE = cE;
        }
        // [cerr] cerr<<"now largest and second largest: "<<largestE<<" "<<secondlargestE<<endl;
    }

    if (node == rootNode) {
        totalEnergy += at[node] - secondlargestE;
        totalEnergy += at[node] - largestE;
    }
    else {
        totalEnergy += max(0, at[node] - largestE);
        stm[node] = max(at[node],largestE);

    }
}
int main() {
    int t;
    cin>>t;
    int i = 0;
    int maxAT = 0;
    for (int k = 1;k<t;k++) {
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        // [cerr] cerr<<"connection confirmed "<<a<<" "<<b<<endl;
    }
    for(int k = 1;k<=t;k++) {
        cin>>at[k];
        maxAT = max(maxAT,at[k]);
        if (maxAT == at[k]) {
            rootNode = k;
            // [cerr] cerr<<"rootNode is now "<<rootNode<<endl;
        }
    }
    dfs(rootNode,0);
    cout<<totalEnergy<<endl;
}