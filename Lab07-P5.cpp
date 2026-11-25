
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int sta = 0;
    int cn = 0;
    vector<int> nb;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cities;
    cin >> cities;

    vector<Node> city(cities + 1);

    for (int i = 1; i <= cities; i++) {
        city[i].cn = i;
    }

    // 建立邻接表
    for (int i = 0; i < cities - 1; i++) {
        int a, b;
        cin >> a >> b;

        city[a].nb.push_back(b);
        city[b].nb.push_back(a);
    }

    // 记录巨人的位置
    int ng;
    cin >> ng;

    while (ng--) {
        int gn;
        cin >> gn;
        city[gn].sta = 1;
    }

    // 城市 1 的子树数量
    int nt = city[1].nb.size();

    vector<int> visited(cities + 1, 0);
    int stamp = 0;

    int deepestofall = 0;

    while (nt--) {
        ++stamp;

        vector<pair<int, int>> q;
        vector<int> lcnt(2, 0);

        int front = 0;

        int start = city[1].nb[nt];

        visited[1] = stamp;
        visited[start] = stamp;

        q.push_back({start, 0});

        int deepest = 0;

        while (front < (int)q.size()) {
            int i = q[front].first;
            int layer = q[front].second;
            front++;

            // 确保层级数组大小足够
            if (layer >= (int)lcnt.size()) {
                lcnt.resize(layer + 1, 0);
            }

            // 统计当前层的巨人
            if (city[i].sta == 1) {
                lcnt[layer]++;
            }

            // BFS 遍历相邻城市
            for (int child : city[i].nb) {
                if (visited[child] == stamp) {
                    continue;
                }

                visited[child] = stamp;
                q.push_back({child, layer + 1});
            }

            deepest = max(deepest, layer);
        }

        // 层级统计
        for (int i = 1; i < deepest; i++) {
            if (lcnt[i] >= 2) {
                lcnt[i + 1] += lcnt[i] - 1;
            }
        }
        deepest = deepest + lcnt[deepest];
        // [cerr] cerr<<"the deepest is "<<deepest<<endl;

        deepestofall = max(
            deepestofall,
            deepest
        );
    }

    cout << deepestofall << '\n';

    return 0;
}
