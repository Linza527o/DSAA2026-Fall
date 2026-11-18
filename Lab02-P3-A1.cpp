//
// Created by Linza on 2026/9/16.
//
#include<iostream>
#include<vector>
using namespace std;
int main() {
    int len = 0;
    int lines = 0;
    scanf("%d",&len);
    scanf("%d",&lines);
    vector<int> num(len,0);
    for(int i=0;i<len;i++) {
        scanf("%d",&num[i]);
    }

    for (int i=0;i<lines;i++) {
        int min = 0;
        int max = 0;
        scanf("%d %d",&min,&max);
        int left = len-1;
        int right = 0;
        for (int i = 0; i < len-1; i++) {
            if (num[0] > min) {
                left = 0;
            }
            if (num[len-1]<max) {
                right = len-1;
            }

            //boundaries above
            if (num[i] == min && num[i+1] >min) {
                left = i+1;
            }
            if (num[i+1] == max && num[i] <max) {
                right = i;
            }

            if (num[i] < min && min <num[i+1]) {
                left = i+1;
            }
            if (num[i+1] > max && max > num[i]) {
                right = i;
            }


        }
    }
}