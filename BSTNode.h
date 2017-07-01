#ifndef BST_NODE_H
#define BST_NODE_H

template <class key_t, class val_t>
  class BSTNode
{
 protected:
  key_t key;
  val_t val;
  BSTNode<key_t, val_t>* leftChild;
  BSTNode<key_t, val_t>* rightChild;
  BSTNode<key_t, val_t>* parent;
 public:
  BSTNode(const key_t& key, const val_t& val);
  virtual ~BSTNode();
  virtual const val_t& getValue();
  virtual void setValue(const val_t& val);
  virtual const key_t& getKey();
  virtual void setKey(const key_t& key);
  virtual BSTNode<key_t, val_t>* getLeftChild();
  virtual void setLeftChild(BSTNode<key_t, val_t>* lChild);
  virtual BSTNode<key_t, val_t>* getRightChild();
  virtual void setRightChild(BSTNode<key_t, val_t>* rChild);
  virtual BSTNode<key_t, val_t>* getParent();
  virtual void setParent(BSTNode<key_t, val_t>* parent);
};

template <class key_t, class val_t>
  BSTNode<key_t, val_t>::BSTNode(const key_t& key, const val_t& val)
{
  this->key = key;
  this->val = val;
  this->leftChild = 0;
  this->rightChild = 0;
  this->parent = 0;
}

template <class key_t, class val_t>
  BSTNode<key_t, val_t>::~BSTNode()
{
}

template <class key_t, class val_t>
  const val_t& BSTNode<key_t, val_t>::getValue()
{
  return this->val;
}

template <class key_t, class val_t>
  void BSTNode<key_t, val_t>::setValue(const val_t& val)
{
  this->val = val;
}

template <class key_t, class val_t>
  const key_t& BSTNode<key_t, val_t>::getKey()
{
  return this->key;
}

template <class key_t, class val_t>
  void BSTNode<key_t, val_t>::setKey(const key_t& key)
{
  this->key = key;
}

template <class key_t, class val_t>
  BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getLeftChild()
{
  return this->leftChild;
}

template <class key_t, class val_t>
  void BSTNode<key_t, val_t>::setLeftChild(BSTNode<key_t, val_t>* leftChild)
{
  this->leftChild = leftChild;
}

template <class key_t, class val_t>
  BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getRightChild()
{
  return this->rightChild;
}

template <class key_t, class val_t>
  void BSTNode<key_t, val_t>::setRightChild(BSTNode<key_t, val_t>* rightChild)
{
  this->rightChild = rightChild;
}

template <class key_t, class val_t>
  BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getParent()
{
  return this->parent;
}

template <class key_t, class val_t>
  void BSTNode<key_t, val_t>::setParent(BSTNode<key_t, val_t>* parent)
{
  this->parent = parent;
}

#endif


