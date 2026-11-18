
#include <iostream>
using namespace std;

int main() {
    int lines;
    cin >> lines;

    for (int i = 1; i <= lines; i++) {
        int nodes, child;
        cin >> nodes >> child;

        long long cnt = 0;
        int k = 0;
        long long term = 1;

        while (cnt < nodes) {
            cnt += term;
            k++;

            if (cnt >= nodes) break;

            term *= child;
        }

        if (cnt == nodes) {
            cout << term << endl;
        }
        else {
            cnt -= term;

            long long un =
                (nodes - cnt + child - 1) / child; //usedNodes

            cout << (nodes - cnt)
                 + (term / child - un)
                 << endl;
        }
    }
}
/* TAKEAWAY MSG
 * 使用TERM *= CHILD 而不是POW 来减少计算量
 * 使用 nodes - cnt 能得到最顶上一层有多少个元素
 * 补上一个 child - 1 之后 再除以 child然后向下取整
 * 一定能找到 用了多少个父节点
 * /