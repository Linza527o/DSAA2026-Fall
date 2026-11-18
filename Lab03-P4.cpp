//
// Created by Linza on 2026/9/30.
//
/*
 *
 think 4 1 5 0 3 2
 4 go right 4 times
 1 stay
 5 go right 3 times
 0 go left  3 times
 3 go left  1 times
 2 go left  3 times

 the ideal case is
 whenever there is a number going right, there will be a corresponding number
 which need to go left, go left.

 the ideal swap time is 7 for this case.

 CASE 1 start from 4
 1 4 5 0 3 2
 1 4 0 5 3 2
 1 4 0 3 5 2
 1 4 0 3 2 5
 1 4 0 2 3 5
 1 0 4 2 3 5
 1 0 2 4 3 5
 1 0 2 3 4 5
 0 1 2 3 4 5



8 2 5  3 9 6



9steps */


#include <algorithm>
#include<iostream>
#include<vector>
using namespace std;
// void mergeSort(vector<int> &a, int l, int r) {
//     if (l>=r){return;}
//     int mid = (l+r)/2;
//     mergeSort(a, l, mid);
//     mergeSort(a, mid+1, r);
//
//     vector<int> tmp;
//     int i = l;
//     int j = mid+1;
//     while (i<=mid && j<=r) {
//         if (a[i] < a[j]) {
//             tmp.push_back(a[i]);
//             i++;
//         }
//         else{
//             tmp.push_back(a[j]);
//             j++;
//         }
//     }
//
//     while (i<=mid) {
//         tmp.push_back(a[i]);
//         i++;
//     }
//     while (j<=r) {
//         tmp.push_back(a[j]);
//         j++;
//     }
//     for (int i = 0; i <= tmp.size(); i++) {
//         a[i+l] = tmp[i];
//     }
// }

long long countReversedPairs(vector<int> &a,int l ,int r) {
    if (l>=r){return 0;}

    int mid = (l+r)/2;

    long long ans = 0;
    ans += countReversedPairs(a,l,mid);
    ans += countReversedPairs(a,mid+1,r);

    vector<int> tmp;
    long long cost = 0;
    int j = mid+1;
    for(int i = l;i<=mid;i++) {
        while (j<=r && a[i] > a[j]) {
            tmp.push_back(a[j]);
            cost+=a[j];
            j++;

        }
        ans+=cost;
        tmp.push_back(a[i]);
    }
        while (j<=r) {
            tmp.push_back(a[j]);
            j++;
        }
        for (int k = 0;k<tmp.size();k++) {
            a[k+l] = tmp[k];
        }

    return ans;
}

int main() {
    int len = 0;
    cin>>len;
    vector<int> a(len,0);
    for (int i = 0; i < len; i++) {
        cin>>a[i];
    }
    // cout<<len;
    // int j = 0;

    cout<<countReversedPairs(a,0,len-1);
    // while (j< len) {
    //     // cout<<"while entered at j ="<<j<<endl;
    //     for (int i = 0; i < len - 1; i++) {
    //         // cout<<"for entered at i = "<<i<<endl;
    //         if (a[i] > a[i+1]) {
    //             swap(a[i], a[i+1]);
    //             // cout<<"swap "<<a[i]<<" and "<<a[i+1]<<endl;
    //             cnt+= min(a[i],a[i+1]);
    //         }
    //     }
    //     j++;
    // }
}