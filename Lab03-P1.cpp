//
// Created by Linza on 2026/9/30.
//
#include<iostream>
#include<vector>
using namespace std;
void merge(vector<int> &a, vector<int> &b, int m, int n) {
    int i = 0, j =0;
    vector<int> temp;
    while (i < m && j < n) {
        if (a[i] < b[j]) {
            temp.push_back(a[i]);
            //  cout<<"ai is now "<<a[i]<<"and bj is now "<<b[j]<<endl;
            // cout <<"now push back a"<< a[i] << endl;
            i++;
        }
        if (a[i] >= b[j]) {
             // cout<<"ai is now "<<a[i]<<"and bj is now "<<b[j]<<endl;
            temp.push_back(b[j]);
            // cout <<"now push back b"<< b[j] << endl;
            j++;
        }
    }
    while (i < m) {
        temp.push_back(a[i]);
        // cout <<"now push back a"<< a[i] << endl;
        i++;
    }
    while (j < n) {
        temp.push_back(b[j]);
        // cout <<"now push back b"<< b[j] << endl;
        j++;
    }

    for (int k = 0; k < temp.size(); k++) {
        cout << temp[k] << " ";
    }

}

int main() {
    int lines = 0;
    scanf ("%d", &lines);
    for (int  l= 0; l < lines; l++) {
        int m = 0, n = 0;
        scanf("%d %d", &m, &n);
        vector<int> a(m,0);
        vector<int> b(n,0);
        // cout<<m<<" "<<n<<endl;
        for (int j = 0;j<m;j++) {
            scanf("%d", &a[j]);
            // cout<<a[i]<<" ";
        }
        for (int j = 0;j<n;j++) {
            scanf("%d", &b[j]);
            // cout<<b[j]<<" ";
        }
        merge(a,b,m,n);
        cout<<endl;
    }

}
