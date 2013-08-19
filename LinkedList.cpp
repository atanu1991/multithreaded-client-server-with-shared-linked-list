#include "LinkedList.h"

template <class T>
void LinkedList<T>::init_lock(int rw)
{
  if (rw)
    pthread_rwlock_wrlock(&rwlock);
  else
    pthread_rwlock_rdlock(&rwlock);
}

template <class T>
void LinkedList<T>::release_lock()
{
  pthread_rwlock_unlock(&rwlock);
}

template <class T>
bool LinkedList<T>::addNode(T data)
{
  if (!check_if_exists(data))
  {
    init_lock(1);
    try
    {
      Node<T> * tmp = new Node<T>();
      tmp->data = data;
      tmp->next = head;
      head = tmp;
      ++size;
      index_un_map.insert(std::pair<T, bool>(data, 1));
      release_lock();
      return true;
    } catch (std::exception & ex)
    {
      release_lock();
      return false;
    }
  } else
    return true;
}

template <class T>
bool LinkedList<T>::deleteNode(T data)
{
  if (check_if_exists(data))
  {
    init_lock(1);
    index_un_map.erase(data);
    --size;
    release_lock();
    return true;
  } else
    return false;
}

template <class T>
bool LinkedList<T>::check_if_exists(T data)
{
  init_lock(0);
  if (index_un_map.find(data) == index_un_map.end())
  {
    release_lock();
    return false;
  }
  release_lock();
  return true;
}

template <class T>
void LinkedList<T>::printList(const char * path)
{
  Node<T> * tmp = head;
  std::ofstream output;
  output.open(path);
  if (output.is_open())
    while (tmp)
    {
      if (check_if_exists(tmp->data))
      {
        output << tmp->data << "\n";
        index_un_map.erase(tmp->data);
      }
      tmp = tmp->next;
    }
  output.close();
  return;
}

template <class T>
void LinkedList<T>::fillList(const char * path)
{
  std::ifstream input;
  input.open(path);
  if (input.is_open())
  {
    std::string line;
    T data;
    while (getline(input, line))
    {
      std::stringstream ss(line);
      ss >> data;
      addNode(data);
    }
  }
  input.close();
  return;

}

template <class T>
void LinkedList<T>::destroyList()
{
  init_lock(1);
  Node<T> * tmp = NULL;
  while (head)
  {
    tmp = head;
    head = head->next;
    delete(tmp);
  }
  size = 0;
  index_un_map.clear();
  head = NULL;
  release_lock();
}

