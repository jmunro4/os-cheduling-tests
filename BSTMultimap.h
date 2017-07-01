#ifndef BST_MULTIMAP_H
#define BST_MULTIMAP_H

#include "BSTNode.h"
#include "ArrayList.h"
#include "BSTForwardIterator.h"
#include <iostream>
#include <queue>

using namespace std;

template <class key_t, class val_t>
  class BSTMultimap
{
 protected:
  BSTNode<key_t, val_t>* root;
  BSTNode<key_t, val_t>* sentinel;
  int numItems;
  void transplant(BSTNode<key_t, val_t>* orig, BSTNode<key_t, val_t>* swap);
 public:
  BSTMultimap();
  virtual ~BSTMultimap();
  virtual void insert(const key_t& key, const val_t& val);
  virtual int getSize();
  virtual bool isEmpty();
  virtual void printTree();
  virtual bool contains(const key_t& key) const;
  virtual void clear();
  virtual BSTForwardIterator<key_t, val_t> getMin() const;
  virtual BSTForwardIterator<key_t, val_t> getMax() const;
  virtual BSTForwardIterator<key_t, val_t> findFirst(const key_t& key) const;
  virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);
  virtual void insertNode(BSTNode<key_t, val_t>* newNode);
};

template <class key_t, class val_t>
  BSTMultimap<key_t, val_t>::BSTMultimap()
{
  this->numItems = 0;
  this->sentinel = 0;
  this->root = this->sentinel;
}

template <class key_t, class val_t>
  BSTMultimap<key_t, val_t>::~BSTMultimap()
{
  this->clear();
}

template <class key_t, class val_t>
  void BSTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& val)
{
  BSTNode<key_t, val_t>* newNode = new BSTNode<key_t, val_t>(key, val);
  this->insertNode(newNode);
}

template <class key_t, class val_t>
  void BSTMultimap<key_t, val_t>::insertNode(BSTNode<key_t, val_t>* newNode)
{
  BSTNode<key_t, val_t>* nnParent = this->sentinel;
  BSTNode<key_t, val_t>* nnNext = this->root;
  
  while(nnNext != this->sentinel)
    {
      nnParent = nnNext;
      if(newNode->getKey() < nnNext->getKey())
	{
	  nnNext = nnNext->getLeftChild();
	}
      else
	{
	  nnNext = nnNext->getRightChild();
	}
    }
  newNode->setParent(nnParent);
  if(nnParent == this->sentinel)
    {
      this->root = newNode;
    }
  else if(newNode->getKey() < nnParent->getKey())
    {
      nnParent->setLeftChild(newNode);
    }
  else
    {
      nnParent->setRightChild(newNode);
    }
  this->numItems++;
}

template <class key_t, class val_t>
  int BSTMultimap<key_t, val_t>::getSize()
{
  return this->numItems;
}

template <class key_t, class val_t>
  bool BSTMultimap<key_t, val_t>::isEmpty()
{
  return this->numItems == 0;
}

template <class key_t, class val_t>
  void BSTMultimap<key_t, val_t>::printTree()
{
  queue<BSTNode<key_t, val_t>*> printq;
  if(this->isEmpty())
    {
      cout << "Empty Tree" << endl;
    }
  else
    {
      printq.push(this->root);
      while(printq.size() != 0)
	{
	  BSTNode<key_t, val_t>* current = printq.front();
	  if(current != this->sentinel)
	    {
	      cout << "key: " << current->getKey() << endl;
	      cout << "val: " << current->getValue() << endl << endl;
	      printq.push(current->getLeftChild());
	      printq.push(current->getRightChild());
	    }
	  else
	    {
	      cout << "End of Branch" << endl << endl;
	    }
	  printq.pop();
	}
    }
}

template <class key_t, class val_t>
  bool BSTMultimap<key_t, val_t>::contains(const key_t& key) const
{
  BSTNode<key_t, val_t>* current = this->root;
  while(current != this->sentinel)
    {
      if(current->getKey() == key)
	{
	  return true;
	}
      else if(current->getKey() > key)
	{
	  current = current->getLeftChild();
	}
      else
	{
	  current = current->getRightChild();
	}
    }
  return false;
}

template <class key_t, class val_t>
  void BSTMultimap<key_t, val_t>::clear()
{
  queue<BSTNode<key_t, val_t>*> clearq;
  if(not this->isEmpty())
    {
      clearq.push(this->root);
      while(clearq.size() != 0)
	{
	  BSTNode<key_t, val_t>* current = clearq.front();
	  if(current != this->sentinel)
	    {
	      clearq.push(current->getLeftChild());
	      clearq.push(current->getRightChild());
	      delete current;
	      this->numItems--;
	    }
	  clearq.pop();
	}
    }
  this->root = this->sentinel;
}

template <class key_t, class val_t>
  BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMin() const
{
  BSTNode<key_t, val_t>* current = this->root;
  while(current != this->sentinel && current->getLeftChild() != this->sentinel)
    {
      current = current->getLeftChild();
    }
  return BSTForwardIterator<key_t, val_t>(current, this->sentinel);
}

template <class key_t, class val_t>
  BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMax() const
{
  BSTNode<key_t, val_t>* current = this->root;
  while(current != this->sentinel && current->getRightChild() != this->sentinel)
    {
      current = current->getRightChild();
    }
  return BSTForwardIterator<key_t, val_t>(current, this->sentinel);
}

template <class key_t, class val_t>
  BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::findFirst(const key_t& key) const
{  
  BSTNode<key_t, val_t>* current = this->root;
  BSTNode<key_t, val_t>* keyed = this->sentinel;
  while(current != this->sentinel)
    { 
      if(current->getKey() == key)
	{
	  keyed = current;
	  current = current->getLeftChild();
	}
      else if(current->getKey() > key)
	{
	  current = current->getLeftChild();
	}
      else if(current->getKey() < key)
	{
	  current = current->getRightChild();
	}
    }
  return BSTForwardIterator<key_t, val_t>(keyed, this->sentinel);
}

template <class key_t, class val_t>
  BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos)
{
  BSTForwardIterator<key_t, val_t> remove = pos;
  BSTForwardIterator<key_t, val_t> successor = pos;
  successor.next();
  if(pos.current->getLeftChild() == this->sentinel)
    {
      this->transplant(pos.current, pos.current->getRightChild());
    }
  else if(pos.current->getRightChild() == this->sentinel)
    {
      this->transplant(pos.current, pos.current->getLeftChild());
    }
  else
    {
      BSTNode<key_t, val_t>* min = pos.current->getRightChild();
      while(min->getLeftChild() != this->sentinel)
	{
	  min = min->getLeftChild();
	}
      if(min->getParent() != pos.current)
	{
	  this->transplant(min, min->getRightChild());
	  min->setRightChild(pos.current->getRightChild());
	  min->getRightChild()->setParent(min);
	}
      this->transplant(pos.current, min);
      min->setLeftChild(pos.current->getLeftChild());
      min->getLeftChild()->setParent(min);
    }
  delete remove.current;
  this->numItems--;
  return successor;
}


template <class key_t, class val_t>
  void BSTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* orig, BSTNode<key_t, val_t>* swap)
{
  if(orig->getParent() == this->sentinel)
    {
      this->root = swap;
    }
  else if(orig == orig->getParent()->getLeftChild())
    {
      orig->getParent()->setLeftChild(swap);
    }
  else
    {
      orig->getParent()->setRightChild(swap);
    }
  if(swap != this->sentinel)
    {
      swap->setParent(orig->getParent());
    }
}
  
#endif
