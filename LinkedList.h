#ifndef LinkedList_H
#define LinkedList_H

#include "Globals.h"
#include <iostream>
#include <string>
#include <map>
#include <pthread.h>

template <class T>

struct Node {
    T data;
    Node * next;
};

template <class T>

class LinkedList {
public:

    LinkedList() : head(NULL), size(0) {
        pthread_rwlock_init(&rwlock, NULL);
    };

    ~LinkedList() {
        //destroyList();
    };
    bool addNode(T data);
    bool deleteNode(T data);
    bool check_if_exists(T data);
    Node<T> * searchNode(T data);
    void printList();
    void destroyList();
    int size;

private:

    std::map<T, bool> index_map;
    void init_lock(int);
    void release_lock();
    pthread_rwlock_t rwlock;
    Node<T> * head;
};
#endif