//
// Created by Linza on 2026/11/25.
//
#include<iostream>
int w[1919810 * 2];
using namespace std;
int main() {
    int nums;
    cin>>nums;

    int tmp = nums;
    int maxh = 0;
    int minh = 0;
    int neither = 0;
    while (nums--) {

        int index = tmp-nums;
        cin>>w[index];
        // [cerr] cerr<<index<<": "<<w[index]<<endl;
    }
    nums = tmp;
    while (nums--) {
        int index = tmp-nums;
        if (index * 2 > tmp) {
            break;
        }
        else if (index * 2 == tmp) {
            if (w[index * 2] > w[index]) {
                if (maxh == 1) {
                    neither = 1;
                    break;
                }
                minh = 1;
            }
            else {
                if (minh == 1) {
                    neither = 1;
                    break;
                }
                maxh = 1;
            }
        }
        else {
            if (w[index * 2] > w[index] && w[index * 2 + 1] > w[index]) {
                if (maxh == 1) {
                    neither = 1;
                    break;
                }
                minh = 1;
            }
            else if (w[index * 2] < w[index] && w[index * 2 + 1] < w[index]) {
                if (minh == 1) {
                    neither = 1;
                    break;
                }
                maxh = 1;
            }
            else {
                neither = 1;
            }
        }

    }
    if (neither) {
        cout << "Neither";
    }
    else if (minh) {
        cout << "Min";
    }
    else if (maxh) {
        cout << "Max";
    }
    else {
        cout<<"error";
    }
}