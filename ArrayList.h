#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "List.h"

template <class item_t>
class ArrayList : public List<item_t>
{
  protected:
   item_t* items;
   int size;
   int capacity;
   virtual void resize();
   
  public:
   //Creates an empty list with capacity 10
   ArrayList();
   //Creates a list with the given capacity
   ArrayList(int capacity);
   ~ArrayList();

   //Pushes item to the back of the list
   virtual void pushBack(const item_t& item);   
   //Removes, but does not return, the last item
   virtual void popBack();
   //Returns a reference to the last item (does not remove it).
   virtual const item_t& getBack() const;
   
   //Pushes item to the front of the list
   virtual void pushFront(const item_t& item);
   //Removes, but does not return, the first item
   virtual void popFront();
   //Returns a reference to the first item (does not remove it).
   virtual const item_t& getFront() const;

   //Returns a reference to the item at the given index
   virtual const item_t& getItem(int index) const;
   //Sets the item at the given index
   virtual void setItem(int index, const item_t& item);

   //Inserts the given item at the given index
   //(items at index or beyond shift up one position)
   virtual void insert(int index, const item_t& item);
   //Removes the item at the given index
   //(items beyond index shift down one position)
   virtual void remove(int index);

   //Returns the number of items in the list
   virtual int getSize() const;
   //Returns true if the list is empty (false otherwise)
   virtual bool isEmpty() const;
   //Returns the size of the array that contains the list
   virtual int getCapacity() const;
};

template <class item_t>
ArrayList<item_t>::ArrayList()
{
  this->capacity = 10;
  this->size = 0;
  this->items = new item_t[10];
}

template <class item_t>
ArrayList<item_t>::ArrayList(int capacity)
{
  this->capacity = capacity;
  this->size = 0;
  this->items = new item_t[capacity];
}

template <class item_t>
ArrayList<item_t>::~ArrayList()
{
  delete[] this->items;
}

template <class item_t>
void ArrayList<item_t>::resize()
{
  if(this->size == this->capacity)
    {
      item_t* temp = new item_t[2*this->capacity];
      for(int i = 0; i < this->size; i++)
	{
	  temp[i] = this->items[i];
	}
      item_t* temp2 = this->items;
      this->items = temp;
      temp = temp2;

      this->capacity *= 2;
    }
}

//Pushes item to the back of the list
template <class item_t>
void ArrayList<item_t>::pushBack(const item_t& item)
{
  this->resize();
  this->items[size] = item;
  this->size++;
}

//Removes, but does not return, the last item
template <class item_t>
void ArrayList<item_t>::popBack()
{
  this->size--;
}

//Returns a reference to the last item (does not remove it).
template <class item_t>
const item_t& ArrayList<item_t>::getBack() const
{
  return this->items[this->size - 1];
}
   
//Pushes item to the front of the list
template <class item_t>
void ArrayList<item_t>::pushFront(const item_t& item)
{
  this->resize();
  for(int i = this->size; i > 0; i--)
    {
      this->items[i] = this->items[i-1];
    }
    this->items[0] = item;
    this->size++;
}

//Removes, but does not return, the first item
template <class item_t>
void ArrayList<item_t>::popFront()
{
  for(int i = 0; i < this->size - 1; i++)
    {
      this->items[i] = this->items[i+1];
    }
  this->size--;
}

//Returns a reference to the first item (does not remove it).
template <class item_t>
const item_t& ArrayList<item_t>::getFront() const
{
  return this->items[0];
}

//Returns a reference to the item at the given index
template <class item_t>
const item_t& ArrayList<item_t>::getItem(int index) const //this is somehow bugged FUCK
{
  return this->items[index];
}

//Sets the item at the given index
template <class item_t>
void ArrayList<item_t>::setItem(int index, const item_t& item)
{
  this->items[index] = item;
}

//Inserts the given item at the given index
//(items at index or beyond shift up one position)
template <class item_t>
void ArrayList<item_t>::insert(int index, const item_t& item)
{
  this->resize();
  for(int i = this->size; i > index; i--)
    {
      this->items[i] = this->items[i-1];
    }
  this->items[index] = item;
  this->size++;
}

//Removes the item at the given index
//(items beyond index shift down one position)
template <class item_t>
void ArrayList<item_t>::remove(int index)
{
  for(int i = index; i < this->size - 1; i++)
    {
      this->items[i] = this->items[i+1];
    }
  this->size--;
}

//Returns the number of items in the list
template <class item_t>
int ArrayList<item_t>::getSize() const
{
  return this->size;
}

//Returns true if the list is empty (false otherwise)
template <class item_t>
bool ArrayList<item_t>::isEmpty() const
{
  return this->size == 0;
}

//Returns the size of the array that contains the list
template <class item_t>
int ArrayList<item_t>::getCapacity() const
{
  return this->capacity;
}

#endif
