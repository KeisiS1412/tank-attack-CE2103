#include "PowerUpQueue.h"

PowerUpQueue::PowerUpQueue() {
    front = nullptr;
    back = nullptr;
}

PowerUpQueue::~PowerUpQueue() {
    Node* curr = front;
    while (curr != nullptr) {
        Node* temp = curr->next;
        delete curr->data;
        delete curr;
        curr = temp;
    }
}

void PowerUpQueue::enqueue(PowerUpType type) {
    Node* newNode = new Node();
    newNode->data = new PowerUp(type);
    newNode->next = nullptr;
    if (front == nullptr) {
        front = newNode;
        back = newNode;
    } else {
        back->next = newNode;
        back = newNode;
    }
}

PowerUp* PowerUpQueue::dequeue() {
    if (front == nullptr) return nullptr;
    Node* temp = front;
    PowerUp* value = temp->data;
    front = temp->next;
    if (front == nullptr) back = nullptr;
    delete temp;
    return value;
}

PowerUp* PowerUpQueue::peek() {
    if (front == nullptr) return nullptr;
    return front->data;
}

bool PowerUpQueue::isEmpty() {
    return front == nullptr;
}