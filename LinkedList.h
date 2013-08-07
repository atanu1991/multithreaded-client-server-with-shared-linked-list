#ifndef LinkedList_H
#define LinkedList_H

#include "Globals.h"
#include <iostream>
#include <string>
#include <map>
#include <pthread.h>
#include <tr1/unordered_map>

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
    };
    bool addNode(T data);
    bool deleteNode(T data);
    bool check_if_exists(T data);
    Node<T> * searchNode(T data);
    void printList();
    void destroyList();
    int size;

private:

    std::tr1::unordered_map<T, bool> index_un_map;
    void init_lock(int);
    void release_lock();
    pthread_rwlock_t rwlock;
    Node<T> * head;
};
#endif