//
// Created by Linza on 2026/11/6.
//
#include <iostream>
#include <vector>
using namespace std;


int main() {
    int lines;
    cin>>lines;
    for (int k = 0; k < lines; k++) {
        int nums;
        cin >> nums;
        vector<int> a(nums);
        for (int j = 0; j < nums; j++) {
            cin >> a[j];
        }
        vector<int> leftmaxpos(nums);
        vector<int> rightmaxpos(nums);
        for (int j = 1; j < nums; j++) {
            int leftcur = j-1;
            int leftmax = 0;
            int lmpos = 0;
            while (a[leftcur] <= a[j] && leftcur >= 0) {
                if (a[leftcur] > leftmax) {
                    leftmax = a[leftcur];
                    lmpos = leftcur + 1;
                }
                leftcur--;
                if (leftcur == -1) {
                    break;
                }
            }
            leftmaxpos[j] = lmpos;

        }
        for (int j = 0; j < nums - 1; j++) {
            int rightcur = j+1;
            int rightmax = 0;
            int rmpos = 0;

            while (a[rightcur] <= a[j] && rightcur <= nums - 1) {
                if (a[rightcur] > rightmax) {
                    rightmax = a[rightcur];
                    rmpos = rightcur + 1;
                }
                rightcur++;
                if (rightcur == nums) {
                    break;
                }

            }

                rightmaxpos[j] = rmpos;


        }

        cout<<"Case "<<k+1<<":"<<"\n";
        for (int j = 0; j < nums; j++) {
            cout<<leftmaxpos[j]<<" ";
            cout<<rightmaxpos[j]<<"\n";
        }
    }
}