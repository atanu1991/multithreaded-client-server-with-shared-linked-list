#include "LinkedList.h"

template <class T>
void LinkedList<T>::init_lock() {
    pthread_rwlock_wrlock(&rwlock);
}

template <class T>
void LinkedList<T>::release_lock() {
    pthread_rwlock_unlock(&rwlock);
}

template <class T>
bool LinkedList<T>::addNode(T data) {
    init_lock();
    try {
        Node<T> * tmp = new Node<T>();
        tmp->data = data;
        tmp->next = head;
        head = tmp;
        ++size;
        release_lock();
        return true;
    } catch (std::exception & ex) {
        release_lock();
        return false;
    }

}

template <class T>
bool LinkedList<T>::deleteNode(T data) {

    init_lock();
    Node<T> *curr = head, *prev = NULL;
    while (curr) {
        if (curr->data == data) break;

        prev = curr;
        curr = curr->next;
    }

    if (curr) {
        if (prev) {
            prev->next = curr->next;
        } else {
            head = curr->next;
        }
        delete(curr);
        --size;
        release_lock();
        return true;
    } else {
        release_lock();
        return false;
    }

}

template <class T>
Node<T> * LinkedList<T>::searchNode(T data) {
    Node<T> * tmp = head;
    while (tmp) {
        if (tmp->data == data) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

template <class T>
void LinkedList<T>::printList() {
    Node<T> * tmp = head;
    bool printNewLine = (tmp) ? true : false;
    while (tmp) {
        std::cout << tmp->data << "|";
        tmp = tmp->next;
    }
    if (printNewLine) {
        std::cerr << std::endl;
    }
}

template <class T>
void LinkedList<T>::destroyList() {
    Node<T> * tmp = NULL;
    while (head) {
        tmp = head;
        head = head->next;
        //std::cout << "deleting data " << tmp->data << std::endl;
        delete(tmp);
    }
}

/*
int main() {

    LinkedList<int> intlist;
    LinkedList<float> floatlist;
    LinkedList<std::string> *stringlist = new LinkedList<std::string>;
    (*stringlist).addNode("atanu");
    (*stringlist).printList();
    return 0;
}*/
