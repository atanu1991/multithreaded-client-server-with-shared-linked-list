#include "LinkedList.h"

template <class T>
void LinkedList<T>::init_lock(int rw) {
    if (rw)
        pthread_rwlock_wrlock(&rwlock);
    else
        pthread_rwlock_rdlock(&rwlock);
}

template <class T>
void LinkedList<T>::release_lock() {
    pthread_rwlock_unlock(&rwlock);
}

template <class T>
bool LinkedList<T>::addNode(T data) {
    if (!check_if_exists(data)) {
        init_lock(1);
        try {
            Node<T> * tmp = new Node<T>();
            tmp->data = data;
            tmp->next = head;
            head = tmp;
            ++size;
            index_map.insert(std::pair<T, Node<T> *>(data, tmp));
            release_lock();
            return true;
        } catch (std::exception & ex) {
            release_lock();
            return false;
        }
    } else
        return true;
}

/*
template <class T>
bool LinkedList<T>::deleteNode(T data) {
    if (check_if_exists(data)) {
        init_lock(1);
        Node<T> *curr = index_map[data];
        index_map.erase(data);
        if (curr->next != NULL) {
            Node<T> *tmp = curr->next;
            index_map.erase(tmp->data);
            curr->data = tmp->data;
            curr->next = tmp->next;
            index_map.insert(std::pair<T, Node<T> *>(curr->data, curr));
            delete tmp;
        } else {
            if (curr == head)
                head = NULL;
            else {
                //Avoid lost pointer problem
                Node<T> *travel = head;
                while (travel->next->next)
                    travel = travel->next;
                travel->next = NULL;
            }
            delete curr;
        }
        --size;
        release_lock();
        return true;
    } else
        return false;
}
*/

template <class T>
bool LinkedList<T>::deleteNode(T data) {
    if (check_if_exists(data)) {
        init_lock(1);
        Node<T> *curr = head, *prev = NULL;
        while (curr) {
            if (curr->data == data)
                break;
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
            index_map.erase(data);
            release_lock();
            return true;
        } else {
            release_lock();
            return false;
        }
    } else
        return false;
}


template <class T>
bool LinkedList<T>::check_if_exists(T data) {
    init_lock(0);
    if (index_map.find(data) == index_map.end()) {
        release_lock();
        return false;
    }
    release_lock();
    return true;
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
    init_lock(1);
    Node<T> * tmp = NULL;
    while (head) {
        tmp = head;
        head = head->next;
        delete(tmp);
    }
    size = 0;
    index_map.clear();
    head = NULL;
    release_lock();
}

