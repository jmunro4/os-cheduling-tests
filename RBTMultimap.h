#ifndef RBT_MULTIMAP
#define RBT_MULTIMAP

#include "BSTMultimap.h"
#include "RBTNode.h"

#include <string>
#include <fstream>
#include <queue>
#include <iostream>
#include <map>

using namespace std;

template <class key_t, class val_t>
class RBTMultimap : public BSTMultimap<key_t, val_t>
{
  protected:
   //Performs the rotate left operation
   //(assumes node has a right child)
   virtual void rotateLeft(BSTNode<key_t, val_t>* node);

   //Performs the rotate right operation
   //(assumes node has a left child)
   virtual void rotateRight(BSTNode<key_t, val_t>* node);

   //Fix up the tree after an insert
   //(assumes insertedNode is red)
   virtual void insertFixup(RBTNode<key_t, val_t>* insertedNode);

   //Fix up the tree after deleting a node
   //ReplacementNode is the node that replaced the deleted node
   //(possibly the sentinel)
   virtual void deleteFixup(RBTNode<key_t, val_t>* replacementNode);

   //Puts replacementNode in nodeToReplace's position in the tree
   //(replacementNode takes its children along with it)
   //Assumes nodeToReplace is a real node (not the sentinel)
   virtual void transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode);

  public:
   //Creates an empty red-black tree
   RBTMultimap();
   virtual ~RBTMultimap();

   //Inserts (key, value) into the multimap
   virtual void insert(const key_t& key, const val_t& value);

   //Removes the key/value pair pointed to by pos
   //(if pos is off the end, does nothing)
   //Returns an iterator pointing to the next node after the
   //deleted node
   virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);

   //Prints the tree in the "dot" format for visualization
   //using graphviz
   //NOTE: Requires that keys are streamable (values are not printed)
   virtual void printDOT(std::string filename);
};


template <class key_t, class val_t>
  RBTMultimap<key_t, val_t>::RBTMultimap() : BSTMultimap<key_t, val_t>()
{
  this->sentinel = new RBTNode<key_t, val_t>(key_t(), val_t(), false);
  this->root = this->sentinel;
}

template <class key_t, class val_t>
  RBTMultimap<key_t, val_t>::~RBTMultimap()
{
  this->clear();
  delete this->sentinel;
}

template <class key_t, class val_t>
  void RBTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& value)
{
  RBTNode<key_t, val_t>* newNode = new RBTNode<key_t, val_t>(key, value, true);
  this->insertNode(newNode);
  this->insertFixup(newNode);
}

template <class key_t, class val_t>
  BSTForwardIterator<key_t, val_t> RBTMultimap<key_t, val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos)
{
  RBTNode<key_t, val_t>* remove = dynamic_cast<RBTNode<key_t, val_t>*> (pos.current);
  BSTForwardIterator<key_t, val_t> successor = pos;
  successor.next();
  RBTNode<key_t, val_t>* current = dynamic_cast<RBTNode<key_t, val_t>*> (pos.current);
  RBTNode<key_t, val_t>* fix;
  RBTNode<key_t, val_t>* hold = dynamic_cast<RBTNode<key_t, val_t>*> (pos.current);
  bool holdColor = hold->getColor();
  if(current->getLeftChild() == this->sentinel)
    {
      fix = current->getRightChild();
      this->transplant(current, current->getRightChild());
    }
  else if(current->getRightChild() == this->sentinel)
    {
      fix = current->getLeftChild();
      this->transplant(current, current->getLeftChild());
    }
  else
    {
      hold = current->getRightChild();
      while(hold->getLeftChild() != this->sentinel)
	{
	  hold = hold->getLeftChild();
	}
      holdColor = hold->getColor();
      fix = hold->getRightChild();
      if(hold->getParent() == current)
	{
	  fix->setParent(hold);
	}
      else
	{
	  this->transplant(hold, hold->getRightChild());
	  hold->setRightChild(current->getRightChild());
	  hold->getRightChild()->setParent(hold);
	}
      this->transplant(current, hold);
      hold->setLeftChild(current->getLeftChild());
      hold->getLeftChild()->setParent(hold);
      hold->setColor(current->getColor());
    }
  if(not holdColor)
    {
      this->deleteFixup(fix);
    }
  delete remove;
  this->numItems--;
  return successor;
}

template <class key_t, class val_t>
  void RBTMultimap<key_t, val_t>::rotateLeft(BSTNode<key_t, val_t>* node)
{
  BSTNode<key_t, val_t>* newRoot = node->getRightChild();
  node->setRightChild(newRoot->getLeftChild());
  if(newRoot->getLeftChild() != this->sentinel)
    {
      newRoot->getLeftChild()->setParent(node);
    }
  newRoot->setParent(node->getParent());
  if(node->getParent() == this->sentinel)
    {
      this->root = newRoot;
    }
  else if(node == node->getParent()->getLeftChild())
    {
      node->getParent()->setLeftChild(newRoot);
    }
  else
    {
      node->getParent()->setRightChild(newRoot);
    }
  newRoot->setLeftChild(node);
  node->setParent(newRoot);
}

template <class key_t, class val_t>
  void RBTMultimap<key_t, val_t>::rotateRight(BSTNode<key_t, val_t>* node)
{
  BSTNode<key_t, val_t>* newRoot = node->getLeftChild();
  node->setLeftChild(newRoot->getRightChild());
  if(newRoot->getRightChild() != this->sentinel)
    {
      newRoot->getRightChild()->setParent(node);
    }
  newRoot->setParent(node->getParent());
  if(node->getParent() == this->sentinel)
    {
      this->root = newRoot;
    }
  else if(node == node->getParent()->getRightChild())
    {
      node->getParent()->setRightChild(newRoot);
    }
  else
    {
      node->getParent()->setLeftChild(newRoot);
    }
  newRoot->setRightChild(node);
  node->setParent(newRoot);
}

template <class key_t, class val_t>
  void RBTMultimap<key_t, val_t>::insertFixup(RBTNode<key_t, val_t>* insertedNode)
{
  RBTNode<key_t, val_t>* fixing;
  while(insertedNode->getParent()->getColor())
    {
      if(insertedNode->getParent() == insertedNode->getParent()->getParent()->getLeftChild())
	{
	  fixing = insertedNode->getParent()->getParent()->getLeftChild();
	  if(fixing->getColor())
	    {
	      insertedNode->getParent()->setColor(false);
	      fixing->setColor(false);
	      insertedNode->getParent()->getParent()->setColor(true);
	      insertedNode = insertedNode->getParent()->getParent();
	    }
	  else
	    {
	      if(insertedNode == insertedNode->getParent()->getRightChild())
		{
		  insertedNode = insertedNode->getParent();
		  this->rotateLeft(insertedNode);
		}
	      insertedNode->getParent()->setColor(false);
	      insertedNode->getParent()->getParent()->setColor(true);
	      this->rotateRight(insertedNode->getParent()->getParent());
	    }	  
	}
      else
	{
	  fixing = insertedNode->getParent()->getParent()->getRightChild();
	  if(fixing->getColor())
	    {
	      insertedNode->getParent()->setColor(false);
	      fixing->setColor(false);
	      insertedNode->getParent()->getParent()->setColor(true);
	      insertedNode = insertedNode->getParent()->getParent();
	    }
	  else
	    {
	      if(insertedNode == insertedNode->getParent()->getLeftChild())
		{
		  insertedNode = insertedNode->getParent();
		  this->rotateRight(insertedNode);
		}
	      insertedNode->getParent()->setColor(false);
	      insertedNode->getParent()->getParent()->setColor(true);
	      this->rotateLeft(insertedNode->getParent()->getParent());
	    }
	}
      dynamic_cast<RBTNode<key_t, val_t>*> (this->root)->setColor(false);
    }
}  

template <class key_t, class val_t>
  void RBTMultimap<key_t, val_t>::deleteFixup(RBTNode<key_t, val_t>* replacementNode)
{
  RBTNode<key_t, val_t>* fixing;
  while(replacementNode != this->root && not replacementNode->getColor())
    {
      if(replacementNode == replacementNode->getParent()->getLeftChild())
	{
	  fixing = replacementNode->getParent()->getRightChild();
	  if(fixing->getColor())
	    {
	      fixing->setColor(false);
	      replacementNode->getParent()->setColor(true);
	      this->rotateLeft(replacementNode->getParent());
	      fixing = replacementNode->getParent()->getRightChild();
	    }
	  if(not fixing->getLeftChild()->getColor() && not fixing->getRightChild()->getColor())
	    {
	      fixing->setColor(true);
	      replacementNode = replacementNode->getParent();
	    }
	  else
	    {
	      if(not fixing->getRightChild()->getColor())
		{
		  fixing->getLeftChild()->setColor(false);
		  fixing->setColor(true);
		  this->rotateRight(fixing);
		  fixing = replacementNode->getParent()->getRightChild();
		}
	      fixing->setColor(replacementNode->getParent()->getColor());
	      replacementNode->getParent()->setColor(false);
	      fixing->getRightChild()->setColor(false);
	      this->rotateLeft(replacementNode->getParent());
	      replacementNode = dynamic_cast<RBTNode<key_t, val_t>*> (this->root);
	    }
	}
      else
	{
	  fixing = replacementNode->getParent()->getLeftChild();
	  if(fixing->getColor())
	    {
	      fixing->setColor(false);
	      replacementNode->getParent()->setColor(true);
	      this->rotateRight(replacementNode->getParent());
	      fixing = replacementNode->getParent()->getLeftChild();
	    }
	  if(not fixing->getRightChild()->getColor() && not fixing->getLeftChild()->getColor())
	    {
	      fixing->setColor(true);
	      replacementNode = replacementNode->getParent();
	    }
	  else
	    {
	      if(not fixing->getLeftChild()->getColor())
		{
		  fixing->getRightChild()->setColor(false);
		  fixing->setColor(true);
		  this->rotateLeft(fixing);
		  fixing = replacementNode->getParent()->getLeftChild();
		}
	      fixing->setColor(replacementNode->getParent()->getColor());
	      replacementNode->getParent()->setColor(false);
	      fixing->getLeftChild()->setColor(false);
	      this->rotateRight(replacementNode->getParent());
	      replacementNode = dynamic_cast<RBTNode<key_t, val_t>*> (this->root);
	    }
	}
    }
  replacementNode->setColor(false);
}

template <class key_t, class val_t>
  void RBTMultimap<key_t, val_t>::transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode)
{
  if(nodeToReplace->getParent() == this->sentinel)
    {
      this->root = replacementNode;
    }
  else if(nodeToReplace == nodeToReplace->getParent()->getLeftChild())
    {
      nodeToReplace->getParent()->setLeftChild(replacementNode);
    }
  else
    {
      nodeToReplace->getParent()->setRightChild(replacementNode);
    }
  replacementNode->setParent(nodeToReplace->getParent());
}

// Don't mess

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::printDOT(std::string filename)
{
   using namespace std;
   ofstream fout(filename.c_str());

   long long counter = 1;
   map<RBTNode<key_t, val_t>*, long long> nodeToCounter;
   nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] = counter;
   counter++;

   fout << "digraph RBTMultimap {" << endl;

   fout << "\t node" << nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] << " [label=\"nil\", style=filled, color=grey, fontcolor=white];" << endl;

   if(this->root != this->sentinel)
   {
      RBTNode<key_t, val_t>* rt = dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
      if(!nodeToCounter[rt])
      {
	 nodeToCounter[rt] = counter;
	 counter++;
      }
      if(!nodeToCounter[rt->getParent()])
      {
	 nodeToCounter[rt->getParent()] = counter;
	 counter++;
      }
      fout << "\t node" << nodeToCounter[rt] << " -> node" << nodeToCounter[rt->getParent()] << " [constraint=false, tailport=n, headport=s";
      if(rt->getParent() == this->sentinel)
      {
	 fout << ", color=grey];" << endl;
      }
      else
      {
	 //The root's parent is something weird!! Make the arrow orange so it sticks out
	 fout << ", color=orange];" << endl;
      }

      map<RBTNode<key_t, val_t>*, bool> printed;
   
      queue<RBTNode<key_t, val_t>* > q;
      q.push(rt);
      while(!q.empty())
      {
	 RBTNode<key_t, val_t>* node = q.front();
	 q.pop();

	 printed[node] = true;
      
	 //Set up node's appearance
	 if(!nodeToCounter[node])
	 {
	    nodeToCounter[node] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " [label=\"k: " << node->getKey() << "\", style=filled, color=";
	 if(node->getColor())
	 {
	    fout << "red";
	 }
	 else
	 {
	    fout << "black, fontcolor=white";
	 }
	 fout << "];" << endl;

	 //Set up child links
	 //First the left node
	 if(!nodeToCounter[node->getLeftChild()])
	 {
	    nodeToCounter[node->getLeftChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getLeftChild()] << " [tailport=sw";    
	 if(node->getLeftChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getLeftChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getLeftChild());
	 }

	 if(node->getLeftChild() != this->sentinel)
	 {
	    if(node->getLeftChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getLeftChild()->getParent()])
	       {
		  nodeToCounter[node->getLeftChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getLeftChild()] << " -> node" << nodeToCounter[node->getLeftChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }

	 //Now the right node
	 if(!nodeToCounter[node->getRightChild()])
	 {
	    nodeToCounter[node->getRightChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getRightChild()] << " [tailport=se";    
	 if(node->getRightChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getRightChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getRightChild());
	 }

	 if(node->getRightChild() != this->sentinel)
	 {
	    if(node->getRightChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getRightChild()->getParent()])
	       {
		  nodeToCounter[node->getRightChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getRightChild()] << " -> node" << nodeToCounter[node->getRightChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }
      }
   }
   fout << "}" << endl;
}

#endif
