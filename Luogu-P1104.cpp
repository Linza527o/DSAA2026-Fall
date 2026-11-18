//
// Created by Linza on 2026/10/14.
//
#include <bits/stdc++.h>
#include <cstring>
using namespace std;
struct dataset {
    string name;
    int y,m,d;
};
void mergesort(vector<dataset> &l,int left,int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergesort(l,left,mid);
    mergesort(l,mid+1,right);
    vector<dataset> tmp;

    int i = left;
    int j = mid+1;
    while (i<= mid && j<= right) {
        if (l[i].y>l[j].y || (l[i].y==l[j].y && l[i].m>l[j].m) || (l[i].y==l[j].y && l[i].m == l[j].m && l[i].d>=l[j].d) ) {
            tmp.push_back(l[j]);
            j++;
        }
        else {
            tmp.push_back(l[i]);
            i++;
        }
    }
    while (i<=mid) {
        tmp.push_back(l[i]);
        i++;
    }
    while (j<=right) {
        tmp.push_back(l[j]);
        j++;
    }
    for (int k = 0;k<tmp.size();k++) {
        l[left+k] = tmp[k];
    }

};


int main () {
    int n;
    cin >> n;
    vector<dataset> l;
    for (int i = 0; i < n; i++) {
        string name;
        int y,m,d;
        cin >> name >> y >> m >> d;
        l.push_back({name,y,m,d});
    }

    mergesort(l,0,l.size()-1);
    for (int i = 0; i < l.size(); i++) {
        cout << l[i].name <<endl;
    }


}