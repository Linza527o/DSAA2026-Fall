//
// Created by Linza on 2026/11/5.
//
#include <iostream>
using namespace std;
class LinkedQueue {
private:
    struct Node {
        int data;
        Node* next;
    };

    Node* h = nullptr;
    Node* t = nullptr;

public:
    void enQueue(int data) {
        Node* tmp = new Node{data,nullptr};
        if (h == nullptr) {
            h = tmp;
            t = tmp;
        }
        else {
            t->next = tmp;
            t = tmp;
        }
    }
    bool deQueue() {
        if (h == nullptr) {
            return false;
        }

        Node* to_delete = h;
        h = h->next;
        if (h == nullptr) {
            t = nullptr;
        }
        delete to_delete;
        return true;

    }
    bool isEmpty() {
        if (h == nullptr) {
            return true;
        }
        return false;
    }
    int front() {
        if (h == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        return h->data;
    }
    ~LinkedQueue() {
        while (h != nullptr) {
            Node* to_delete = h;
            h = h->next;
            delete to_delete;
        }
    }
};

int main() {
    LinkedQueue* q = new LinkedQueue();
    q->enQueue(10);
    q->enQueue(20);
    q->enQueue(30);
    cout<<q->front()<<endl;
    q->deQueue();
    cout<<q->front()<<endl;
    q->deQueue();
    cout<<q->front()<<endl;
    q->deQueue();
    cout<<q->isEmpty()<<endl;
}