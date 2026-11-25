//
// Created by Linza on 2026/11/5.
//

class LinkedQueueVer0 {
private:
    struct Node {
        int value;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:
    void enQueue(int x) {
        Node* temp = new Node{x, nullptr};

        if (head == nullptr) {
            head = temp;
            tail = temp;
        }
        else {

            tail -> next = temp;
            tail = temp;
            // 情况 B：原来队列非空
        }
    }

    bool deQueue() {
        if (head == nullptr) {
            return false;
            //检查空队列
        }

        Node* temp = head;
        head = head->next;
            //往前走一步
        if (head == nullptr) {
            //如果往前走一步遇到了空指针
            tail = nullptr;
            //那tail也是空指针
        }

        delete temp;
        //释放内存
        return true;
    }


};
