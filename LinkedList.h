#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "LinkedListNode.h"
#include "List.h"

template <class item_t>
class LinkedList : public List<item_t>
{
 protected:
  LinkedListNode<item_t>* head;
  LinkedListNode<item_t>* tail;
  int size;
 public:
  LinkedList();
  ~LinkedList();
  virtual void pushBack(const item_t& item);
  virtual void popBack();
  virtual const item_t& getBack() const;
  virtual void pushFront(const item_t& item);
  virtual void popFront();
  virtual const item_t& getFront() const;
  virtual const item_t& getItem(int index) const;
  virtual void setItem(int index, const item_t& item);
  virtual void insert(int index, const item_t& item);
  virtual void remove(int index);
  virtual int getSize() const;
  virtual bool isEmpty() const;
};

template <class item_t>
LinkedList<item_t>::LinkedList()
{
  this->head = 0;
  this->tail = 0;
  this->size = 0;
}

template <class item_t>
LinkedList<item_t>::~LinkedList()
{
  LinkedListNode<item_t>* current = this->head;
  while(this->size != 0)
    {
      LinkedListNode<item_t>* next = current->getNext();
      delete current;
      this->size--;
      current = next;
    }
}

template <class item_t>
void LinkedList<item_t>::pushBack(const item_t& item)
{
  LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(0, item);//1
  if(this->size == 0)
    {
      this->head = newNode;
      this->tail = newNode;
    }
  else
    {
      this->tail->setNext(newNode);
      this->tail = newNode;
    }
  this->size++;
}

template <class item_t>
void LinkedList<item_t>::popBack()
{
  LinkedListNode<item_t>* current = this->head;
  while(current->getNext() != this->tail)
    {
      current = current->getNext();
    }
  delete this->tail;
  current = this->tail;
  this->size--;
}

template <class item_t>
const item_t& LinkedList<item_t>::getBack() const
{
  return this->tail->getItem();
}

template <class item_t>
void LinkedList<item_t>::pushFront(const item_t& item)
{
  LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(this->head, item);//2
  this->head = newNode;
  if(this->size == 0)
    {
      this->tail = newNode;
    }
  this->size++;
}

template <class item_t>
void LinkedList<item_t>::popFront()
{
  LinkedListNode<item_t>* current = this->head;
  this->head = current->getNext();
  delete current;
  this->size--;
}

template <class item_t>
const item_t& LinkedList<item_t>::getFront() const
{
  return this->head->getItem();
}

template <class item_t>
const item_t& LinkedList<item_t>::getItem(int index) const
{
  LinkedListNode<item_t>* current = this->head;
  for(int i = 0; i < index; i++)
    {
      current = current->getNext();
    }
  return current->getItem();
}

template <class item_t>
void LinkedList<item_t>::setItem(int index, const item_t& item)
{
  LinkedListNode<item_t>* current = this->head;
  for(int i = 0; i < index; i++)
    {
      current = current->getNext();
    }
  current->setItem(item);
}

template <class item_t>
void LinkedList<item_t>::insert(int index, const item_t& item)
{
  LinkedListNode<item_t>* current = this->head;
  for(int i = 0; i < index-1; i++)
    {
      current = current->getNext();
    }
  LinkedListNode<item_t>* next = current->getNext(); 
  LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(next, item);//3
  current->setNext(newNode);
  this->size++;
}

template <class item_t>
void LinkedList<item_t>::remove(int index)
{
  LinkedListNode<item_t>* current = this->head;
  for(int i = 0; i < index-1; i++)
    {
      current = current->getNext();
    }
  LinkedListNode<item_t>* remove = current->getNext();
  current->setNext(remove->getNext());
  delete remove;
  this->size--;
}

template <class item_t>
int LinkedList<item_t>::getSize() const
{
  return this->size;
}

template <class item_t>
bool LinkedList<item_t>::isEmpty() const
{
  return this->size == 0;
}

#endif
