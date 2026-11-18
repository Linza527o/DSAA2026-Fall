//
// Created by Linza on 2026/9/17.
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
    for (int i = 0; i < len; i++) {
        scanf("%d",&num[i]);
    }



    for (int i = 0; i < lines; i++) {
        int min = 0;
        int max = 0;
        scanf("%d %d",&min,&max);

        int left = 0;
        int right = len - 1;

        int oomin = -1;
        int oomax = -1;


        while (left <= right) {
            int mid = left + (right - left)/2;


            if (num[mid] == min) {
                oomin = mid;
                left = mid + 1;
            }
            if (num[mid] < min) {
                left = mid + 1;
            }
            if (num[mid] > min) {
                right = mid - 1;
            }

        }
        if (oomin == -1) {
            oomin = right;
        }
        // cout<<oomin<<endl;
        left = 0;
        right = len - 1;

        while (left <= right) {
            int mid =  left + (-left+right)/2;

            if (num[mid] == max) {
                oomax = mid;
                right = mid - 1;
            }

            if (num[mid] < max) {
                left = mid + 1;
            }
            if (num[mid] > max) {
                right = mid - 1;
            }



        }
        if (oomax == -1) {
            oomax = left;
        }
        // cout<<oomax<<endl;





        int ans = oomax - oomin - 1;

        if (ans > 0) {
            cout << "YES " << ans << endl;
        }
        else {
            cout << "NO" << endl;
        }

    }
}