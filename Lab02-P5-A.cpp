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
            cout << a[i] << " ";
        }



        int left = 0, right = L;
        // cout<<left<<" "<<right<<endl;
        while (left <= right) {



            a:
                int mid = left + (right-left)/2;
                bool flag = true;
                cout<<"mid is now adjusted to be "<<mid<<endl;
                for (int i = 0; i < n + 1; i++) {
                if ((a[i + 1] - a[i]) > mid) {
                    left = mid + 1;
                    cout<<"step is too short"<<endl;
                    cout<<"left is now adjusted to be "<<left<<endl;
                    flag = false;
                    break;
                    }
                }





            if (!flag) {
                goto a;
            }
            if (flag) {

                    bool allLowerthan = true;
                    for (int i = 0; i < n + 2; i++) {

                        if (a[i+1] - a[i] == mid) {
                            allLowerthan = false;
                            break;
                        }
                    }
                    if (allLowerthan) {
                        cout<<"step is too long"<<endl;
                        right = mid - 1;
                        cout<<"right is now adjusted to be "<<right<<endl;
                        goto a;
                        break;
                    }
                    else {
                        cout<<"step is found to be "<<mid<<endl;
                        break;
                    }

            }



        }
        cout<<"step is found to be "<<left + (right - left) /2 <<endl;
    }


    //这一版的问题是 没有考虑racer的数量是有限的
    //所以要更改判断条件
}