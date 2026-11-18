//
// Created by Linza on 2026/10/10.
//
/*
 * 1 2 3 4 5 6
 * X O O X O O
 * 1 3 4 2 5 6
 *
 * 1 2 2 4 5 6
 * X O O X O O
 * 1 2 4 2 5 6
 *
 *
 */

#include<vector>
#include<iostream>
using namespace std;
void mergeSort(vector<int>&a,int l,int r) {
    if (l>=r) return;
    int mid = (l+r)/2;
    mergeSort(a,l,mid);
    mergeSort(a,mid+1,r);

    int i = l;
    int j = mid +1;
    vector<int>tmp;
    while (i<=mid && j<=r) {
        if (a[i]<a[j]) {
            tmp.push_back(a[i]);
            i++;
        }
        else {
            tmp.push_back(a[j]);
            j++;
        }
    }
    while (i<=mid) {
        tmp.push_back(a[i]);
        i++;
    }
    while (j<=r) {
        tmp.push_back(a[j]);
        j++;
    }

    for (int k = 0;k<tmp.size();k++) {
        a[l+k] = tmp[k];
    }
}
int main() {
    int nums;
    cin>>nums;
    // cout<<nums<<endl;
    vector<int> a(nums,-1);
    for (int i = 0;i<nums;i++) {
        cin>>a[i];
    }
    // cout<<a[0]<<" ";
    mergeSort(a,0,nums-1);
    // for (int i = 0;i<nums;i++) {
    //     cout<<a[i]<<" ";
    // }


    vector<int> b(nums,-1);
    int numOfBlanks = nums / 3;
    int j = 0;
    int k = numOfBlanks;
    while (a[k-1] == a[k]) {
        k--;
    }
    // cout<<k;

        for (int i = 0;j<k;i+=3) {
            b[i] = a[j];
            j++;
        }
        for (int i = 0;i<nums;i++) {
            if (b[i] == -1) {
                b[i] = a[j];
                j++;
            }
        }







    cout<<a[numOfBlanks]<<endl;
    for (int i = 0;i<nums;i++) {
        cout<<b[i]<<" ";
    }
}