//
// Created by Linza on 2026/9/30.
//
#include<iostream>
#include<cstdio>
#include <vector>
using namespace std;
void mergesort(vector<long long>& a, int l, int r) {
    if (l>=r)return;
    int m = (l+r)/2;
    mergesort(a,l,m);
    mergesort(a,m+1,r);
    vector<int> t;
    int i = l;
    int j = m + 1;
    while (i<=m && j<=r) {
        if (a[i]<a[j]) {
            t.push_back(a[i]);
            i++;
        }
        else {
            t.push_back(a[j]);
            j++;
        }
    }
    while (i<=m) {
        t.push_back(a[i]);
        i++;
    }
    while (j<=r) {
        t.push_back(a[j]);
        j++;
    }
    for (int k = 0; k<t.size(); k++) {
        a[k + l] = t[k];
    }

}

int main() {
    // cout << 2346 << " " << 3 << '\n';
    // for (int i = 0; i < 2346; i++) {
    //     cout << 1 << " ";
    // }
    int len  = 0;
    long long m;
    scanf("%d",&len);
    scanf("%lld",&m);
    vector<long long> a(len,0);
    for (int i = 0; i < len; i++) {
        scanf("%lld",&a[i]);
    }

    //merge sort the inputd
    mergesort(a,0,len-1);
    // for (int i = 0; i < len; i++) {
    //     printf("%d ",a[i]);
    // }
    long long cnt = 0;
    //take the first number
    for (int i = 0; i < len; i++) {
        if (a[i] > m)break;
        long long news = 0;
        news = m - a[i];
        int l = i;
        int r = len - 1;
        while(l<r) {
            if (l == i ) {
                l++;
            }
            if (r == i) {
                r--;
            }

            //skip the one we take out.
            if (a[r] + a[l] > news) {
                r--;
                continue;
            }
            if (a[l] + a[r] < news) {
                l++;
                continue;
            }
            if (a[l] + a[r] == news) {
                // case 1 two ends have more than 1 number that can add up to
                if (a[l] != a[r]) {
                    long long L = 1;
                    long long R = 1;
                    while (l + 1 <r && a[l] == a[l+1] ) {
                        l++;
                        L++;
                    }
                    while (r - 1 > 0 && a[r - 1] == a[r]) {
                        r--;
                        R++;
                    }
                    cnt += L*R;
                    l++;
                    r--;
                }
                else {
                    long long n = r - l + 1;
                    cnt += n * (n - 1) / 2;
                    break;
                }
                //CASE 2 two ends are the same number
            }
            // in the middle, judge which way to go

            //
        }

    }
    cout << cnt << endl;
    //new s = m - a_i
    //1. check if the middle of the rest can have a sum that equals to s
    //2. judge if the middle is whether
    //3.   smaller: the right pointer move to the right until we find
    //4    larger: the left pointer move to the left until we find
    //
    //
    //5            once we find we store the index
    //              cnt++;
    //6             print the result
}