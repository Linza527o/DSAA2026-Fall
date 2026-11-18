//
// Created by Linza on 2026/9/17.
//
#include<iostream>
#include<vector>
using namespace std;

int main () {
    int inlen = 0;
    int lines = 0;
    scanf ("%d %d", &inlen,&lines);
    vector <int> a(inlen,0);
    vector <int> b(inlen,0);
    for (int i = 0; i < inlen; i++) {
        scanf ("%d", &a[i]);
    }
    for (int i = 0; i < inlen; i++) {
        scanf ("%d", &b[i]);
    }
    for (int m = 0; m < lines; m++) {
        int l = 0;
        int r = 0;
        scanf ("%d %d", &l, &r);

        int k = (r-l+1);
        int cleft = l - 1;
        int dleft = l - 1;
        int kthmin = 0;
        while (k>1) {
            int half = k / 2;
            if (a[cleft + half - 1] < b[dleft + half - 1]) {
                cleft += half;
            }
            else {
                dleft += half;
            }

            k -= half;

        }

        //boundary case:
        kthmin = min(a[cleft], b[dleft]);
        cout<<kthmin<<endl;




    }


}