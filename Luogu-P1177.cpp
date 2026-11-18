//
// Created by Linza on 2026/9/26.
//
#include<iostream>
#include<vector>
using namespace std;
void mS(vector<int> &a, int left, int right) {
    if(left>=right){return;}
    //告诉计算机 拆分的终点
    int mid = left +  (-left + right) / 2;
    mS(a,left,mid);
    mS(a,mid+1,right);

    vector<int> tmp;
    int i = left;
    int j = mid + 1;
    while (i<=mid && j<=right) {
        if (a[i] > a[j]) {
            tmp.push_back(a[j]);
            j++;
        }
        else {
            tmp.push_back(a[i]);
            i++;
        }
    }
    while (i<=mid) {
        tmp.push_back(a[i]);
        i++;
    }
    while (j<=right) {
        tmp.push_back(a[j]);
        j++;
    }
    //写回原数组
    for (int k = 0;k<tmp.size();k++) {
        a[left+k] = tmp[k];
    }
}

int main() {
    int n;
    scanf("%d",&n);
    // cout << n << endl;
    vector<int> a(n,0);
    for (int i = 0;i<n;i++) {
        scanf("%d",&a[i]);
    }
    mS(a,0,n-1);
    for (int i = 0;i<n;i++) {
        printf("%d ",a[i]);
    }
}