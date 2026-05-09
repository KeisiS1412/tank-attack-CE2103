#include "Queue.h"

Queue::Queue() {
    front = nullptr;
    back = nullptr;
}

Queue::~Queue() {

    Node* curr = front;
    while (curr != nullptr) {
        Node* temp = curr->next;
        delete curr;
        curr = temp;
    }
}

void Queue::enqueue(int value)
{
    Node* newNode = new Node();
    newNode-> data = value;
    newNode-> next = nullptr;
    if (front == nullptr)
    {
        front = newNode;
    }
    else
    {
        back-> next = newNode;
        back = newNode;
    }
}

int Queue::dequeue()
{
    if (front == nullptr) return -1;
    Node* temp = front;
    int value = temp-> data;
    front = temp-> next;
    if (front == nullptr) back = nullptr;
    delete temp;
    return value;
}

bool Queue::isEmpty()
{
    return front == nullptr;
}

int Queue::getFront()
{
    if (front == nullptr) return -1;
    return front-> data;
}