//
// Created by Linza on 2026/11/5.
//


class CircularQueue {
private:
    static constexpr int CAP = 5;
    int Q[CAP];
    int front = 0;
    int rear = 0;
    int count = 0;

public:
    bool enQueue(int x) {
        if (count < CAP) {
            Q[rear] = x;
            rear = (rear + 1) % CAP;
            count++;
            return true;
        }
        else {
            return false;
        }
    }
    bool deQueue() {
        if (count == 0) {
            cout<<"Queue is empty"<<endl;
            return false;
        }
        else {
            front = (front + 1) % CAP;
            count--;
            //delete the value of Q[front] here, as asked, skip this step
            return true;
        }
    }
};
