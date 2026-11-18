//
// Created by Linza on 2026/11/5.
//

class LinkedStack {
private:
    struct Node {
        int value;
        Node* next;
    };

    Node* topNode = nullptr;

public:
    void push(int x) {
        Node *temp = new Node;
        temp->value = x;
        temp->next = topNode;
        topNode = temp;
    }
    bool pop() {
        if (topNode == nullptr) {
            cout << "Stack underflow" << endl;
            return false;
        }
        else {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;

            return true;
        }
    }
    ~LinkedStack() {
        while (topNode != nullptr) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
};
