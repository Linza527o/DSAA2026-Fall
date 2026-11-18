//
// Created by Linza on 2026/10/14.
//
/*
 *QuickSelectPseudocode
 * quickselect(arr,int left,int right, int k)
 *      int pivot = random(left,right);
 *      for(int i = left;i<=right;i++){
 *
 *      }
 *
 */
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int QuickSelect(vector<int> &a,int left,int right,int k) {

    int pivot = a[left+rand() % (right - left + 1)];

    vector<int> l;
    vector<int> r;
    int equal = 0;
    for (int i = left;i<=right;i++) {
        if (a[i] < pivot) {
            l.push_back(a[i]);
        }
        if (a[i] > pivot) {
            r.push_back(a[i]);
        }
        if (a[i] == pivot) {
            equal++;
        }
    }
    if (k<l.size()) {
        return QuickSelect(l,0,l.size()-1,k);
    }
    else if (k<l.size()+equal) {
        return pivot;
    }
    else {
        return QuickSelect(r,0,r.size()-1,k-l.size()-equal);
    }


}


int main() {
    int n,k;
    scanf("%d%d",&n,&k);
    vector<int> a(n);
    for (int i=0;i<n;i++) {
        scanf("%d",&a[i]);
    }
    srand((unsigned)time(nullptr));

    cout << QuickSelect(a, 0, n - 1, k);
}