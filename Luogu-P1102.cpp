//
// Created by Linza on 2026/9/22.
//
#include<iostream>
#include<vector>
using namespace std;
void mergeSort(vector<int>& a,int l,int r) {
    if (l>=r)return;
    int mid = l+(r-l)/2;
    mergeSort(a,l,mid);
    mergeSort(a,mid+1,r);


    vector<int> tmp;
    int i = l;
    int j = mid+1;
    while(i<=mid&&j<=r) {
        if (a[i] <= a[j]) {
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
        a[l+k]= tmp[k];
    }


}




int main() {
    int n,c;
    scanf("%d %d",&n,&c);
    vector<int>a(n,0);
    for(int i=0;i<n;i++) {
        scanf("%d",&a[i]);
    }
    mergeSort(a,0,n-1);

    // for (int i=0;i<n;i++) {
    //     cout << a[i] << " ";
    // }
    // cout<<endl;

    long long cnt = 0;
    for(int i=0;i<n;i++) {
        int left = i + 1;
        int right = n - 1;
        int leftr = 0;
        int rightr = 0;

        while (left <= right) {
            int mid = left+(right-left)/2;
            if (a[mid] - a[i] >= c) {
                right = mid - 1;
            }
            if (a[mid] - a[i] < c) {
                left = mid + 1;
            }

        }
        rightr = left;

         left = i + 1;
         right = n - 1;


        while (left <= right) {
            int mid = left+(right-left)/2;
            if (a[mid] - a[i] > c) {
                right = mid - 1;

            }
            if (a[mid] - a[i] <= c) {
                left = mid + 1;
            }

        }
        leftr = left;
        if (rightr != 0) {
            cnt+=(leftr - rightr);
        }

    }
    cout << cnt << endl;
}

