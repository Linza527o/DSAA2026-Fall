//
// Created by Linza on 2026/11/5.
//
#include <iostream>
#include <vector>
using namespace std;

class Dequeue {
    private:
         struct Node {
            int data;
            Node* next;
            Node* prev;
         };
    Node* front = nullptr;
    Node* rear = nullptr;
public:
    void enQueue (int data, int direction) {

        if (front == nullptr) {
            front = new Node{data, nullptr, front};
            rear = front;
            return;
        }
        if (direction == 1) {
            rear->next = new Node{data, nullptr, rear};
            rear = rear->next;
        }
        else if (direction == 0) {
            front->prev = new Node{data, front, nullptr};
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

    // Dequeue reveresQueue () {
    //     Dequeue reverse;
    //     while (rear != nullptr) {
    //         reverse.enQueue(rear->data, 1);
    //     }
    // }

   void concatQueues(Dequeue &u, Dequeue &v,int direction) {
        int to_concat = v.deQueue(direction);
        if (direction == 0) {
            // cout<<"read element to concat to the front: "<<to_concat<<endl;
            while (to_concat != -1) {
                // cout<<"concating to the front: "<<to_concat<<endl;
                u.enQueue(to_concat, 1);
                to_concat = v.deQueue(0);
            }
        }
        else {
            // int to_concat = v.deQueue(0);
            // cout<<"read element to concat to the rear: "<<to_concat<<endl;
            while (to_concat != -1) {
                // cout<<"concating to the rear: "<<to_concat<<endl;
                u.enQueue(to_concat, 1);
                to_concat = v.deQueue(1);
            }
        }

    }

    
};


int main() {
    int nums;
    while (cin>>nums) {
        int opes;
        int type;
        cin>>opes;
        vector<Dequeue> v(nums+1);
        for (int i = 0; i < opes; i++) {
            cin>>type;
            int x,y,z;
            switch(type){
                case 1:

                    cin>>x>>y>>z;
                    v[x].enQueue(z,y);
                    break;
                case 2:
                    cin>>x>>y;
                    cout<<v[x].deQueue(y)<<"\n";
                    break;
                case 3:
                    cin>>x>>y>>z;
                    v[x].concatQueues(v[x],v[y],z);
                    break;
                default:
                    break;
            }
        }
    }
}





// Dequeue d;
// Dequeue d2;
// d.enQueue(1, 0);
// d.enQueue(2, 1);
// cout<<d.deQueue(1)<<endl;
// cout<<d.deQueue(1)<<endl;
// cout<<"dequeue completed"<<endl;
// d.enQueue(8, 1);
// cout<<"first front enqueue completed"<<endl;
// d.enQueue(7, 1);
// cout<<"first rear enqueue completed"<<endl;
// d2.enQueue(9, 1);
// d2.enQueue(10, 1);
// cout<<"enqueue completed"<<endl;
// d.concatQueues(d,d2,1);
// cout<<d.deQueue(1)<<endl;
// cout<<d.deQueue(1)<<endl;
// cout<<d.deQueue(1)<<endl;
// cout<<d.deQueue(1)<<endl;