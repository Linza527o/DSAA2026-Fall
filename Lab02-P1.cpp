//
// Created by Linza on 2026/9/16.
//
#include<iostream>
#include <vector>
using namespace std;
int main() {

    int len = 0;
    scanf("%d",&len);
    vector<int> num(len,0);
    for(int i=0;i<len;i++) {
        scanf("%d",&num[i]);

    }

    








    //这上边应该先分个类

    int lines = 0;
    scanf("%d",&lines);
    for(int i=0;i<lines;i++) {
        int right = len -1;
        int left = 0;
        bool isFound = false;

        int intinput;
        scanf("%d",&intinput);
        // printf("%d",intinput);
        while (left <= right) {
            int mid = left + (right - left)/2;

            if (num[mid] == intinput) {
                isFound = true;
                break;
            }
            if (num[mid] < intinput) {
                left = mid + 1;
            }
            if (num[mid] > intinput) {
                right = mid - 1;
            }
        }
        if (isFound) {
            cout<<"YES"<<endl;
        }
        else {
            cout<<"NO"<<endl;
        }
    }

}