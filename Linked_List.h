#include <iostream>
#include <string>

template <class T>

struct Node {
    T data;
    Node * next;
};

template <class T>

class LinkedList {
public:

    LinkedList() : head(NULL), size(0) {
    };

    ~LinkedList() {
        destroyList();
    };
    bool addNode(T data);
    bool deleteNode(T data);
    Node<T> * searchNode(T data);
    void printList();
    void destroyList();
private:
    Node<T> * head;
    int size;
};