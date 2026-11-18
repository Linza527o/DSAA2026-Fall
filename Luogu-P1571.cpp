//
// Created by Linza on 2026/9/26.
//
#include<iostream>
#include<vector>
using namespace std;
void mergeSort(vector<int> &a, int l, int r) {
    if (l>=r)return;
    int mid = l + (r-l)/2;
    mergeSort(a,l,mid);
    mergeSort(a,mid+1,r);

    vector<int> tmp;
    int i = l;
    int j = mid + 1;
    while (i<=mid && j<=r) {
        if (a[i] < a[j]) {
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


bool BS(int s, vector<int> &a) {
    int left = 0;
    int right = a.size()-1;
    while (left <= right) {
        int mid = left + (right-left)/2;
        // cout<<"mid  is "<<mid<<endl;
        if (s < a[mid]) {
            right = mid - 1;
        }
        if (s > a[mid]) {
            left = mid + 1;
        }
        if (s == a[mid]) {
            return true;
        }
    }
    return false;
}


int main() {
    int n,m;
    cin>>n>>m;
    vector<int> a(n);

    for (int i = 0;i<n;i++) {
        scanf("%d",&a[i]);
    }
    // mergeSort(a,0,n-1);
    // for (int i = 0;i<n;i++) {
    //     cout<<a[i]<<" ";
    // }
    // cout<<endl;
    vector<int> toFound(m,0);
    for (int i = 0;i<m;i++) {
        int s;
        scanf("%d",&toFound[i]);
        // cout<<s<<" ";
    }
    mergeSort(toFound,0,m-1);
    for (int i = 0;i<n;i++) {
        if (BS(a[i],toFound)) {
            cout<<a[i]<<" ";
        }

    }

}