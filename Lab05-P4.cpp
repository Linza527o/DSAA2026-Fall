//
// Created by Linza on 2026/11/6.
//
#include<iostream>
#include<vector>
#include<climits>
using namespace std;
class ArrayStack {


    int S[300000];
    int topIndex = -1;
public:
    bool push(int x) {
        if (topIndex == 300000 - 1) {
            cout << "Stack overflow" << endl;
            return false;
        }
        else {
            topIndex++;
            S[topIndex] = x;
            return true;
        }
    }
    int pop() {
        if (topIndex == -1) {
            cout << "Stack underflow" << endl;
            return -1;
        }
        else {
            int result = S[topIndex];
            S[topIndex] = 0;
            topIndex--;
            return result;
        }
    }
    int top() {
        if (topIndex == -1) {
            cout << "Stack underflow" << endl;
        }
        else {
            return S[topIndex];
        }
    }
    bool isEmpty() {
        if (topIndex == -1) {
            return true;
        }
        else {
            return false;
        }
    }
};

using namespace std;
int main() {
    int lines;
    cin>>lines;

    for (int i = 0; i < lines; i++) {
        int nums;
        ArrayStack u;

        cin >> nums;
        vector<int> a(nums);
        vector<int> suf(nums + 1,INT_MAX);

        for (int i = 0; i < nums; i++) {
            cin>>a[i];
        }

        for (int i = nums - 1; i >=0; i--) {
            suf[i] = min(suf[i + 1], a[i]);
        }

        for (int i = 0; i < nums; i++) {
            if (a[i] != suf[i]) {
                u.push(a[i]);
            }
            else {
                cout << a[i] << " ";
                while (!u.isEmpty() && u.top() < suf[i + 1] ) {
                    cout<<u.pop()<<" ";
                }
            }
        }



        while (!u.isEmpty()) {
            cout<<u.pop()<<" ";
        }
        cout<<"\n";
    }
}