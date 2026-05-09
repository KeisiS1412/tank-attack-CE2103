#ifndef P2_CE2103_TANKATTACK_QUEUE_H
#define P2_CE2103_TANKATTACK_QUEUE_H


class Queue
{
private:
    struct Node
    {
        int data;
        Node* next;
    };
    Node* front;
    Node* back;

public:
    Queue();
    ~Queue();
    void enqueue(int value);
    int dequeue();
    bool isEmpty();
    int getFront();
};


#endif