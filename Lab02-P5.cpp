//
// Created by Linza on 2026/9/18.
//
#include <algorithm>
#include<iostream>
#include<vector>

using namespace std;

int main () {
    int L = 0;
    int n = 0;
    int m = 0;
    while (cin>>L>>n>>m) {


        // cout<<L<<" "<<n<<" "<<m<<endl;
        vector<int> a(n + 2, 0);
        for (int i = 1; i < n + 1; i++) {
            scanf("%d", &a[i]);
        }
        a[n+1] = L;
        sort(a.begin(), a.end());

        for (int i = 0; i < n + 2; i++) {
            //cout << a[i] << " ";
        }



        int left = 0, right = L;


        // cout<<left<<" "<<right<<endl;
        while (left < right) {
            int mid = left + (right -left) /2;
            int j = 0;
            int racer = 1;
            bool flag = true;
            for (int i = 1;i<n+2;i++) {
                if (a[i] - a[j] > mid) {
                    j = i -1;
                    /*
                     现在假设运动员跑的是一条直线 从左向右跑
                     我们先看 数组第 i 个和第 j 个 之间的距离
                     是否大于我们的值
                     如果是的话 就说明这一步之前是可以的
                     但是这一步之后就到不了了
                     所以就选择i-1作为racer放的位置
                     */
                    racer++;

                    //racer被放了下来，所以计算racer数量的计数器++
                    if (a[i] - a[j] > mid) {
                        flag = false;
                        break;
                    }
                    if (racer>m) {
                        flag = false;
                        break;
                    }

                }
                /*
                 如果没有触发上面的if 那就说明i还可以继续往右走
                 牛逼
                 */

            }
            if (flag) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        cout<<left <<endl;
    }


}
