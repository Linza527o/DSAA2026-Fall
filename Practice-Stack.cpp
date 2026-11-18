//
// Created by Linza on 2026/11/5.
//

class ArrayStack {
private:
    static constexpr int CAP = 5;
    int S[CAP];
    int topIndex = -1;

public:
    bool push(int x) {
        if (topIndex == CAP - 1) {
            cout << "Stack overflow" << endl;
            return false;
        }
        else {
            topIndex++;
            S[topIndex] = x;
            return true;
        }
    }
    bool pop() {
        if (topIndex == -1) {
            cout << "Stack underflow" << endl;
            return false;
        }
        else {
            topIndex--;
            return true;
        }
    }
};
