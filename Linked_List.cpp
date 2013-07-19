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

template <class T>
bool LinkedList<T>::addNode(T data) {

    try {
        Node<T> * tmp = new Node<T>();
        tmp->data = data;
        tmp->next = head;
        head = tmp;
        ++size;
        return true;
    } catch (std::exception & ex) {
        return false;
    }
}

template <class T>
bool LinkedList<T>::deleteNode(T data) {
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
        return true;
    } else {
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
        std::cout << std::endl;
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

int main() {

    LinkedList<int> intlist;
    LinkedList<float> floatlist;
    LinkedList<std::string> stringlist;

    stringlist.addNode("atanu");
    stringlist.printList();

    return 0;
}
