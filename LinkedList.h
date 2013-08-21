#ifndef LinkedList_H
#define LinkedList_H

#include "Globals.h"
#include <iostream>
#include <string>
#include <map>
#include <pthread.h>
#include <tr1/unordered_map>

template <class T>

struct Node
{
  T data;
  Node * next;
} ;

template <class T>
class LinkedList
{
public:

  LinkedList() : head(NULL), size(0)
  {
    pthread_rwlock_init(&rwlock, NULL);
  };

  ~LinkedList()
  {
    destroyList();
  };
  bool addNode(T data);
  bool deleteNode(T data);
  bool check_if_exists(T data);
  void printList(const char *);
  void fillList(const char *);
  void destroyList();
  int size;

private:

  /* unordered_map is similar to hash_map O(1) lookup, insert, delete
   faster than map which is O(log n)

   */
  std::tr1::unordered_map<T, bool> index_un_map;
  void init_lock(int);
  void release_lock();
  pthread_rwlock_t rwlock;      /* Read-Write Lock for the LinkedList */
  Node<T> * head;               /* Head of the LinkedList */

} ;
#endif