//
// Created by Linza on 2026/10/10.
//
/*
 * Think from the connecting point
 * what if you have 3 strings
 *  B_1 R_1
 *  B_2 R_2
 *  B_3 R_3
 *  B_4 R_4
 *  B_5 R_5
 *  B_6 R_6
 *  B_7 R_7
 *  ...
 *  B_N-1 R_N-1
 *  B_N R_N
 *
 *  CASE1 R_N-1 > B_N
 *  BECOMES (B_N-1, R_N-1 - B_N + R_N)
 *
 *  CASE2 R_N-1 < B_N
 *  BECOMES (B_N - R_N-1 + B_N-1,R_N)
 *
 *  CASE3 R_N-1 = B_N
 *  BECOMES (B_N-1 R_N)
 *
 *  BRR BBR
 *  BRRBBRBBR ->
 *  BBR
 *
 *  After all concats we got new string.
 *
 *  Start from the base case if we have BBR BRR RRR BBB
 *  BBRBRRRRRBBB ->
 *  BBRR
 *  BRRRRRBBBBBR ->
 *  BR
 *  orders do matter.
 *
 *  we should start with a pool of bead strings
 *  but what is the perfect order?
 *  (R_N-2,B_N-2),(R_N-1,B_N-1),(R_N,B_N),(R_N+1,B_N+1) ->
 *  (R_N-2,B_N-2),(R_N-1,B_N),(R_N+1,B_N+1) ->
 *  (R_N-2,B_N),(R_N+1,B_N+1) ->
 *  (R_N-2,B_N+1)->
 *  (max{0,R_N-2 - B_N+1},max{0,B_N+1-R_N-2}) ->
 *  T
 */

#include<iostream>
#include<vector>
using namespace std;
void mergeSort(vector<vector<int>> &a, int l, int r,int type) {
    if (l>=r) return;
    int m = (l+r)/2;
    mergeSort(a, l, m,type);
    mergeSort(a, m+1, r,type);

    vector<vector<int>> tmp;
    int i = l;
    int j = m + 1;
    if (type == 1) {
        while (i<=m && j<=r) {
            if (a[i][0] <= a[j][0]) {
                tmp.push_back(a[i]);
                i++;
            }
            else if (a[j][0] < a[i][0]) {
                tmp.push_back(a[j]);
                j++;
            }
        }

        while (i<=m) {
            tmp.push_back(a[i]);
            i++;
        }
        while (j<=r) {
            tmp.push_back(a[j]);
            j++;
        }
    }
    if (type == 0) {
        while (i<=m && j<=r) {
            if (a[i][1] < a[j][1]) {
                tmp.push_back(a[j]);
                j++;
            }
            else if (a[j][1] <= a[i][1]) {
                tmp.push_back(a[i]);
                i++;
            }
        }

        while (i<=m) {
            tmp.push_back(a[i]);
            i++;
        }
        while (j<=r) {
            tmp.push_back(a[j]);
            j++;
        }
    }

    for (int k = 0;k<tmp.size();k++) {
        a[l+k] = tmp[k];
    }
}
int main() {
    int lines;
    cin>>lines;
    for (int p = 0; p < lines; p++) {
        int nums = 0;
        cin>>nums;
        vector<vector<int>> medium;
        vector<vector<int>> bluep;
        vector<vector<int>> redp;
        for (int q = 0; q < nums; q++) {
            int r,b;
            cin>>b>>r;
            if (r>b) {
                redp.push_back({b,r});
            }
            if (b>r) {
                bluep.push_back({b,r});
            }
            if (b == r) {
                medium.push_back({b,r});
            }
        }

        mergeSort(redp,0,redp.size()-1,1);
        mergeSort(bluep,0,bluep.size()-1,0);

        long long cnt = 0;
        for (int i  = 1; i < redp.size(); i++) {
            cnt += min(redp[i-1][1],redp[i][0]);
            redp[i][1] = redp[i][1] + max(0,redp[i-1][1] - redp[i][0]);
            redp[i][0] = redp[i-1][0] + max(0,redp[i][0]-redp[i-1][1]);

        }
        for (int i  = 1; i < medium.size(); i++) {
            cnt += min(medium[i-1][1],medium[i][0]);
            medium[i][1] = medium[i][1] + max(0,medium[i-1][1]-medium[i][0]);
            medium[i][0] = medium[i-1][0] + max(0,medium[i][0]-medium[i-1][1]);

        }
        for (int i  = 1; i < bluep.size(); i++) {
            cnt += min(bluep[i-1][1],bluep[i][0]);
            bluep[i][1] = bluep[i][1] + max(0,bluep[i-1][1]-bluep[i][0]);
            bluep[i][0] = bluep[i-1][0] + max(0,bluep[i][0]-bluep[i-1][1]);

        }

        if (!redp.empty() && !medium.empty()) {
            cnt += min(redp.back()[1], medium.back()[0]);
        }

        if (!medium.empty() && !bluep.empty()) {
            int r = medium.back()[1];

            if (!redp.empty()) {
                r += max(0, redp.back()[1] - medium.back()[0]);
            }

            cnt += min(r, bluep.back()[0]);
        }

        if (medium.empty() && !redp.empty() && !bluep.empty()) {
            cnt += min(redp.back()[1], bluep.back()[0]);
        }

        cout << cnt << '\n';
        // cout<<cnt<<endl;



    }
}