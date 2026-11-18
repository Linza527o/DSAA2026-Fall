//
// Created by Linza on 2026/10/14.
//
#include <algorithm>
#include<iostream>
#include<vector>
using namespace std;
void mergesort(vector<long long> &a,long long l,long long r) {
    if (l>=r) return;
    long long mid = (l+r)/2;
    mergesort(a,l,mid);
    mergesort(a,mid+1,r);
    vector<long long> tmp;
    int i = l;
    int j = mid+1;
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
    int n,k;
    cin>>n>>k;
    vector<long long> a(n);
    for(int i=0;i<n;i++) {
        cin>>a[i];
    }
    mergesort(a,0,n-1);
    int order = 1;
    int pointer = 0;
    bool flag = false;
    while (order !=k) {
        if (a[pointer+1] != a[pointer]) {
            order++;
            pointer++;
        }
        else {
            pointer++;
        }
        if (pointer>=n) {
            flag = true;
            break;
        }
    }
    if (!flag) {
        cout<<a[pointer]<<endl;
    }

    else {
        cout<<"NO RESULT"<<endl;
    }
}