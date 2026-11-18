//
// Created by Linza on 2026/9/30.
//
#include <algorithm>
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;


void mergeSort(vector<int> &a,int l,int r) {

    if (l>=r)return;
    int mid = l+(r-l)/2;
    mergeSort(a,l,mid);
    mergeSort(a,mid+1,r);

    vector<int> temp;
    int i = l;
    int j = mid+1;
    while (i<=mid && j<=r) {
        if (a[i] < a[j]) {
            temp.push_back(a[i]);
            // cout<<"now push back a["<<i<<"] = "<<a[i]<<endl;
            i++;
        }
        else {
            temp.push_back(a[j]);
            // cout<<"now push back a["<<j<<"] = "<<a[j]<<endl;
            j++;
        }
    }
    while (i<=mid) {
        temp.push_back(a[i]);
        // cout<<"now push back a["<<i<<"] = "<<a[i]<<endl;
        i++;
    }
    while (j<=r) {
        temp.push_back(a[j]);
        // cout<<"now push back a["<<j<<"] = "<<a[j]<<endl;
        j++;
    }

    for (int k=l;k<=r;k++) {
        a[k]=temp[k-l];
    }


}


int main() {
    int lines = 0;
    scanf("%d",&lines);
    for (int i = 0; i < lines; i++) {
        int nums = 0;
        scanf("%d",&nums);
        vector<int> a(nums,0);
        for (int j = 0; j < nums; j++) {
            scanf("%d",&a[j]);
            // cout<<a[j]<<" ";
        }
        mergeSort(a,0,nums-1);
        // for (int  p = 0; p < a.size(); p++) {
        //     cout<<a[p]<<" ";
        // }
        bool same = false;


        if (nums>3) {
            if (a[nums-4] == a[nums-3]) {
                same = true;
            }
            if (a[nums-2] == a[nums-3]) {
                same = true;
            }
        }
        else {
            if (a[nums-2] == a[nums-3]) {
                same = true;
            }
        }


        if (same) {
            cout<<"wa"<<endl;
        }
        else {
            cout<<a[nums-3]<<endl;
        }
    }
}