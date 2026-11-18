//
// Created by Linza on 2026/9/17.
//
#include<iostream>
#include<vector>
using namespace std;

// void Msort(vector <int> &a,int left, int right) {
//
//     if(left >= right) {
//         return;
//     }
//
//     int mid = left + (right - left)/2;
//
//     Msort(a,left,mid);
//     Msort(a,mid+1,right);
//
//     vector<int> tmp;
//     int i = left;
//     int j = mid+1;
//     while(i <= mid && j <= right) {
//         if (a[i] <= a[j]) {
//             tmp.push_back(a[i]);
//             i++;
//         }
//         else {
//             tmp.push_back(a[j]);
//             j++;
//         }
//     }
//     //下面是在这个与条件跳出之后的补充检查
//
//     while (i <= mid) {
//         tmp.push_back(a[i]);
//         i++;
//     }
//
//     while (j<=right) {
//         tmp.push_back(a[j]);
//         j++;
//     }
//
//     for (int k = 0;k < tmp.size();k++) {
//         a[left+k] = tmp[k];
//     }
//
// }
int main () {
    int inlen = 0;
    int lines = 0;
    scanf ("%d %d", &inlen,&lines);
    vector <int> a(inlen,0);
    vector <int> b(inlen,0);
    for (int i = 0; i < inlen; i++) {
        scanf ("%d", &a[i]);
    }
    for (int i = 0; i < inlen; i++) {
        scanf ("%d", &b[i]);
    }
    for (int i = 0; i < lines; i++) {
        int l = 0;
        int r = 0;
        scanf ("%d %d", &l, &r);
        vector <int> c(2*(r-l+1),0);
        vector <int> d(2*(r-l+1),0);
        int cnt = 0;
        for (int j = l-1;j <= r-1;j++) {
            c[cnt] = a[j];
            cnt++;
        }
        cnt = 0;
        for (int j = l-1;j <= r-1;j++) {
            d[cnt] = b[j];
            cnt++;
        }

        // for (int i = 0; i < c.size(); i++) {
        //     cout << c[i] << " ";
        // }
        // for (int i = 0; i < d.size(); i++) {
        //     cout << d[i] << " ";
        // }

        vector <int> aftersort(2*(r-l+1),0);
        int p = 0;
        int q = 0;
        int rank = 0;
        while (rank<=r-l) {
            if (c[p] <= d[q]) {
                aftersort[rank] = c[p];
                // cout<<aftersort[rank]<<endl;
                p++;
                rank++;

            }
            else {
                aftersort[rank] = d[q];
                q++;
                rank++;
            }
        }
        // for (int i = 0; i < aftersort.size(); i++) {
        //     cout << aftersort[i] << " ";
        // }
        cout<<aftersort[r-l]<<endl;




        // //use a merge sort to solve the problem
        // Msort(c,0,2*(r-l) + 1);
        // cout<<c[r-l]<<endl;
    }


}
