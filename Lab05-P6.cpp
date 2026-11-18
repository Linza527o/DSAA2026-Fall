//
// Created by Linza on 2026/11/6.
//
#include <iostream>
using namespace std;
class Dequeue {
private:
    struct Node {
        int data;
        Node* next;
        Node* prev;
        int pos;
    };
    Node* front = nullptr;
    Node* rear = nullptr;
public:
    void enQueue (int data, int direction,int pos) {

        if (front == nullptr) {
            front = new Node{data, nullptr, front,pos};
            rear = front;
            return;
        }
        if (direction == 1) {
            rear->next = new Node{data, nullptr, rear,pos};
            rear = rear->next;
        }
        else if (direction == 0) {
            front->prev = new Node{data, front, nullptr,pos};
            front = front->prev;
        }
    };

    int deQueue (int direction) {
        if (front == nullptr) {
            return -1;
        }
        if (front == rear) {
            int x = front->data;
            delete front;
            front = rear = nullptr;
            return x;
        }
        if (direction == 1) {
            Node* to_delete = rear;
            int getresult =  rear->data;
            rear = rear->prev;
            rear->next = nullptr;
            delete to_delete;
            return getresult;
        }
        else{
            Node* to_delete = front;

            int getresult =  front->data;
            front = front->next;
            front->prev = nullptr;
            delete to_delete;
            return getresult;
        }
    }
    // int getRear() {
    //     return rear->data;
    // }
    // int getFront() {
    //     return front->data;
    // }



    Node* getFront() {

            return front;

        }
    Node* getRear() {
        return rear;
    }

    void printAll() {
        Node* cur = front;
        while (cur!= nullptr) {
            cout<<cur->data<<"("<<cur->pos<<")";
            cur = cur->next;
        }
        cout<<endl;
    }

};

void checkGap(Dequeue &qmin,Dequeue &qmax,int gap, int &left) {
    // cout<<"get qmax front pos = "<<qmax.getFront()->pos<<endl;
    // cout<<"get qmin front pos = "<<qmin.getFront()->pos<<endl;
    while (qmax.getFront()->data - qmin.getFront()->data > gap ) {

        if (qmax.getFront()->pos > qmin.getFront()->pos) {
            left = qmin.getFront()->pos + 1;
            qmin.deQueue(0);
        }
        else {
            left = qmax.getFront()->pos + 1;
            qmax.deQueue(0);
        }
    }
}


int main() {
    int diff = 0;
    int nums = 0;
    cin>>diff;
    cin>>nums;
    Dequeue qmax;
    Dequeue qmin;
    int ans = 0;
    int left = 0;
    for (int i = 0; i < nums; i++) {
        int data;

        cin>>data;
        if (qmax.getRear() == nullptr) {
            qmax.enQueue(data, 1,i);
            qmin.enQueue(data, 1,i);
            // cout<<"test sentence A"<<endl;
            // qmax.printAll();
            // qmin.printAll();
            // cout<<"sentence end"<<endl;
        }
        else {
            // if (data == qmax.getRear()->data) {
            //     qmax.deQueue(1);
            //     qmax.enQueue(data, 1,i);
            // }
            while (qmax.getRear() != nullptr && data >= qmax.getRear()->data  ) {
                qmax.deQueue(1);

            }
            qmax.enQueue(data, 1,i);
            // cout<<"test sentence B"<<endl;
            // qmax.printAll();
            // qmin.printAll();
            // cout<<"sentence end"<<endl;
            // if (data < qmax.getRear()->data) {
            //     qmax.enQueue(data, 1,i);
            //     cout<<"test sentence C"<<endl;
            //     qmax.printAll();
            //     qmin.printAll();
            //     cout<<"sentence end"<<endl;
            // }
            //

            // if (data == qmin.getFront()->data) {
            //     qmax.deQueue(1);
            //     qmax.enQueue(data, 1,i);
            // }
            while (qmin.getRear() != nullptr  && data <= qmin.getRear()->data) {
                qmin.deQueue(1);
            }
            qmin.enQueue(data, 1,i);
            // cout<<"test sentence D"<<endl;
            // qmax.printAll();
            // qmin.printAll();
            // cout<<"sentence end"<<endl;
            // if (data > qmin.getRear()->data) {
            //     qmin.enQueue(data, 1,i);
            //     cout<<"test sentence E"<<endl;
            //     qmax.printAll();
            //     qmin.printAll();
            //     cout<<"sentence end"<<endl;
            // }
            checkGap(qmin,qmax,diff,left);
            // cout<<"test sentence F"<<endl;
            // qmax.printAll();
            // qmin.printAll();
            // cout<<"sentence end"<<endl;

        }
        // int curmax  = max(max(abs(qmax.getRear()->pos - qmin.getFront()->pos  + 1),
        //     abs(qmax.getFront()->pos - qmin.getFront()->pos  + 1)),
        //     max( abs(qmax.getRear()->pos - qmin.getRear()->pos + 1),
        //         abs(qmax.getFront()->pos - qmin.getRear()->pos + 1)));
        if ( i - left + 1 > ans) {
            ans = i - left + 1;
        }
        // if (qmax.getFront()->pos == qmin.getFront()->pos) {
        //     ans = qmax.getFront()->pos + 1;
        // }

    }
    cout<<ans<<endl;
};