/****************************************************************************/
/*                                                                          */
/* This is a AVLtree Data structure                                         */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : AVLtree.h                                                    */
/*                                                                          */
/****************************************************************************/

#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <cmath>
#include <cassert>
#include "utils.h"

#define LEFT 0
#define RIGHT 1
//________________________________________________________________________
//  AVL tree tamplate class.
//________________________________________________________________________
//  key : The type of key objects in the tree. The key type must
//  implement a copy constructor.
//  type : The type of elements in the tree. The type must 
//  implement a copy constructor
//  compare: A comparator for the key type. It should implement the 
//  operator(key1,key2) and return true iff key1<key2. 
//________________________________________________________________________
template <typename key, typename type, typename compare> class AVLtree {
public:
//________________________________________________________________________
//  AVL node class.
//________________________________________________________________________
//  Simply implements a node in the AVL tree. It has trivial constructors
//  and a function that calculates the height and balance. Its 
//  destructor also destructs the key and value objects. 
//________________________________________________________________________
  class AVLNode {
  public:
    friend class AVLtree<key, type, compare>;
    key *keyValue;
    type *value;
    AVLNode *parent;
    AVLNode *left;
    AVLNode *right;
    int height;
    int balance;
    AVLNode()
        : keyValue(NULL), value(NULL), parent(NULL), left(NULL), right(NULL),
          height(0), balance(0) {}
    void calculateHeightAndBalance() {
      int leftHeight;
      int rightHeight;
      if (this->left) {
        leftHeight = this->left->height;
      } else {
        leftHeight = -1;
      }
      if (this->right) {
        rightHeight = this->right->height;
      } else {
        rightHeight = -1;
      }
      this->height = maxInt(leftHeight, rightHeight) + 1;
      this->balance = leftHeight - rightHeight;
    }
    AVLNode(key *keyValue, type *value, AVLNode *parent, AVLNode *left,
            AVLNode *right)
        : keyValue(keyValue), value(value), parent(parent), left(left),
          right(right),height(0),balance(0) {
      this->calculateHeightAndBalance();
    }
    ~AVLNode() {
      delete keyValue;
      delete value;
    }
  };
  AVLNode *dummy; //Dummy parent for special cases regarding the root.
  AVLNode *root; //The root of the tree.
  compare comp; //The comparator object.
  int numOfElements; //This value will always hold the number of elements in the tree.
//________________________________________________________________________
//  AVL tree constructor.
//________________________________________________________________________
//  Simply constructs an AVL tree. Notice that it allocates memory for
//  the key and value. 
//________________________________________________________________________
  AVLtree() : comp(), numOfElements(0) {
    root = new AVLNode();
    dummy = new AVLNode();
    root->parent = dummy;
    dummy->right = root;
    root->keyValue = NULL;
    dummy->keyValue = NULL;
    root->value = NULL;
    dummy->value = NULL;
  }
//________________________________________________________________________
//  Empty AVL tree builder.
//________________________________________________________________________
//  Allocates empty nodes to form an empty full AVL tree from the root,
//  given a desired height.
//________________________________________________________________________
  void buildEmptyTree(AVLNode *root, int height) {
    if (height == 0) {
      return;
    }
    AVLNode *left = new AVLNode();
    left->parent = root;
    left->height = height - 1;
    AVLNode *right = new AVLNode();
    right->parent = root;
    right->height = height - 1;
    root->left = left;
    root->right = right;
    root->calculateHeightAndBalance();
    buildEmptyTree(root->left, height - 1);
    buildEmptyTree(root->right, height - 1);
  }
//________________________________________________________________________
//  Deleting nodes.
//________________________________________________________________________
//  This function should be used on a full empty AVL tree built with
//  the buildEmptyTree() function. It deletes the leaves to get a half
//  full AVL tree with -size- nodes. 
//________________________________________________________________________
  void deleteNodes(int size) {
    int numOfNodes = 0;
    AVLNode **array = this->inorderNodes(&numOfNodes); // put the nodes in an array.
    int height = floor(log2(size)); //calculation of height.
    int numOfNodesToDelete = exp2(height+1)-1 - size; //calculate how many nodes should be deleted to get
													  // a tree with -size- nodes.
    bool right = true; //left right leaf switch.
    while (numOfNodesToDelete > 0) { //delete the leaves.
      if(right){
        array[numOfNodes-1]->parent->right=NULL; //don't forget (to bring a towel) to update the parent.
        delete array[numOfNodes-1];
      }else{
        array[numOfNodes-1]->parent->left=NULL; //don't forget (to bring a towel) to update the parent.
        delete array[numOfNodes-1];
      }
      numOfNodes -= 2; //next leaf.
      --numOfNodesToDelete;
      --this->numOfElements;
      right=!right;
    }
    delete[] array;
    //update all nodes height and balance.
    AVLNode **upadatingArray = this->postorder(); 
    for (int i = 0; i < size; ++i) {
      upadatingArray[i]->calculateHeightAndBalance();
    }
    delete[] upadatingArray;
  }
//________________________________________________________________________
//  Empty AVL tree with -size- nodes constructor.
//________________________________________________________________________
//  This constructs an Empty AVL tree with -size- nodes constructor.
//________________________________________________________________________
  AVLtree(int size) : comp() {
    root = new AVLNode();
    dummy = new AVLNode();
    root->parent = dummy;
    dummy->right = root;
    if (size != 0) { // if you want an empty tree with no nodes.
      int height = floor(log2(size));
      buildEmptyTree(root, height); //build full tree.
      numOfElements = exp2(height+1)-1; 
      this->deleteNodes(size);  //delete leaves.
    }else{
      numOfElements = 0;
    }
  }
//________________________________________________________________________
//  isEmpty() function
//________________________________________________________________________
//  Checks if the tree is empty. Returns true if it is, and false otherwise.
//________________________________________________________________________
  bool isEmpty() {
    if (!this->numOfElements) {
      return true;
    }
    return false;
  }
//________________________________________________________________________
//  Finds a node in the tree.
//________________________________________________________________________
//  This function finds a node with the -k- key. You should supply it with
//  a root (in the first argument), the key to find (the second argument)
//  and an address to AVLNode* to return to you the last node in the 
//  path.
//________________________________________________________________________
  AVLNode *find(AVLNode *node, key *k, AVLNode **lastNode) {
    if ((!node) || (!(node)->keyValue)) {
      return NULL;
    }
    key *y = (node->keyValue);
    if (!(comp(y, k)) && !((comp(k, y)))) { // if x==y
      return node;
    } else if (comp(k, y)) {
      *(lastNode) = node;
      return find(node->left, k, lastNode);
    } else {
      *(lastNode) = node;
      return find(node->right, k, lastNode);
    }
    return NULL;
  }
//________________________________________________________________________
//  L roll
//________________________________________________________________________
//  Rolls the node to keep the AVL tree balanced. This roll is used in
//  the rollNode function.
//________________________________________________________________________
  void Lroll(AVLNode *node) {
    AVLNode *a = node;
    AVLNode *b = a->right;
    AVLNode *bLeft;
    if (b != NULL) {
      bLeft = b->left;
      b->parent = a->parent;
      b->calculateHeightAndBalance();
    } else {
      bLeft = NULL;
    }
    if (a->parent->left == NULL) {
      a->parent->right = b;
    } else if (a->parent->left == a) {
      a->parent->left = b;
    } else {
      a->parent->right = b;
    }
    a->parent = b;
    if (b != NULL) {
      b->left = a;
    } else {
    }
    a->right = bLeft;
    if (bLeft != NULL) {
      bLeft->parent = a;
      bLeft->calculateHeightAndBalance();
    }
    a->calculateHeightAndBalance();
  }
//________________________________________________________________________
//  R roll
//________________________________________________________________________
//  Rolls the node to keep the AVL tree balanced. This roll is used in
//  the rollNode function.
//________________________________________________________________________
  void Rroll(AVLNode *node) {
    AVLNode *b = node;
    AVLNode *a = b->left;
    AVLNode *aRight;
    if (a != NULL) {
      aRight = a->right;
      a->parent = b->parent;
      a->calculateHeightAndBalance();
    } else {
      aRight = NULL;
    }

    if (b->parent->left == NULL) {
      b->parent->right = a;
    } else if (b->parent->left == b) {
      b->parent->left = a;
    } else {
      b->parent->right = a;
    }
    b->parent = a;
    if (a != NULL) {
      a->right = b;
    } else {
    }
    b->left = aRight;
    if (aRight != NULL) {
      aRight->parent = b;
      aRight->calculateHeightAndBalance();
    }
    b->calculateHeightAndBalance();
  }
//________________________________________________________________________
//  Rolls the node.
//________________________________________________________________________
//  Rolls the node to keep the AVL tree balanced. This function calculates
//  which roll should be done and calls the Lroll and Rroll accordingly.
//________________________________________________________________________
  void rollNode(AVLNode *node) {
    if (node->balance == 2) {         // left rolls
      if (node->left->balance >= 0) { // left left roll
        Rroll(node);
      } else if (node->left->balance == -1) { // left right roll
        Lroll(node->left);
        Rroll(node);
      }
    } else if (node->balance == -2) {  // right rolls
      if (node->right->balance <= 0) { // right right roll
        Lroll(node);
      } else if (node->right->balance == 1) { // right left roll
        Rroll(node->right);
        Lroll(node);
      }
    }
  }
//________________________________________________________________________
//  Insertion function
//________________________________________________________________________
//  Inserts an element to the tree.
//  Returns true if the element was inserted or false otherwise.
//  Notice that this function allocates memory for the new element.
//  !!You can't insert NULL as a key!!
//________________________________________________________________________
  bool insert(key *k, type *v) {
    key *newKey = new key(*k);
    type *newValue;
    if (v != NULL) { // value can be inserted as null.
      newValue = new type(*v);
    } else {
      newValue = NULL;
    }
    if (this->isEmpty()) { // if the tree is empty insert as root.
      this->root->keyValue = newKey;
      this->root->value = newValue;
      ++(this->numOfElements);
      return true;
    }
    AVLtree<key, type, compare>::AVLNode *lastNode = (this->root);
    AVLtree<key, type, compare>::AVLNode *result =
        find((this->root), k, &lastNode); // find me if the key exists.
    if (result) {                         // found
      delete newKey;
      delete newValue;
      return false;
    } else {                       // not found do insertion
      key *y = lastNode->keyValue; // save key for compartion
      AVLtree<key, type, compare>::AVLNode *newNode =
          new AVLtree<key, type, compare>::AVLNode(
              newKey, newValue, lastNode, NULL,
              NULL);    // allocate the node to insert
      if (comp(k, y)) { // compare and update parent
        lastNode->left = newNode;
        ++(this->numOfElements);
      } else {
        lastNode->right = newNode;
        ++(this->numOfElements);
      }
      //fixing AVL tree.
      while (lastNode != this->dummy) { // go over the path to root
        int oldHeight = lastNode->height;
        lastNode->calculateHeightAndBalance();
        if (lastNode->balance == 2 ||
            lastNode->balance == -2) { // fixing balance
          this->rollNode(lastNode);;
        }
        lastNode->calculateHeightAndBalance();
        lastNode = lastNode->parent; //next node on path
        lastNode->calculateHeightAndBalance();
        if (oldHeight ==
            lastNode->height) { // check to see if height is different
          break;
        }
      }
      this->root = this->dummy->right;//keep the dummy and root as they should be.
      return true;
    }
  }
//________________________________________________________________________
//  Remove leaf
//________________________________________________________________________
//  This is a basic removal function to remove a leaf.
//________________________________________________________________________
  static void removeLeaf(AVLNode *leaf, compare comp) {
    if ((leaf->parent->right)) { // if there is a right son to the parent
      if ((!comp((leaf->parent->right->keyValue), leaf->keyValue) &&
           (!comp(leaf->keyValue,
                  (leaf->parent->right->keyValue))))) { // is that son me?
        leaf->parent->right = NULL;
      } else { // I'm the left son
        leaf->parent->left = NULL;
      }
    } else { // there is no right son, so I am the left son.
      leaf->parent->left = NULL;
    }
  }
//________________________________________________________________________
//  Remove a node with one son.
//________________________________________________________________________
//  This is a basic removal function to remove a node with one son.
//  You should know which son the node has and use the definitions:
//  #define LEFT 0
//  #define RIGHT 1
//________________________________________________________________________
  static void removeOnlyOneSon(AVLNode *v, compare comp, int sonSide) {
    switch (sonSide) {//check
    case RIGHT:
      if ((v->parent->right)) { // if there is a right son to the parent
        if ((!comp((v->parent->right->keyValue), v->keyValue) &&
             (!comp(v->keyValue,
                    (v->parent->right->keyValue))))) { // is that son me?
          v->right->parent = v->parent;
          v->parent->right = v->right;
        } else { // I'm the left son
          v->right->parent = v->parent;
          v->parent->left = v->right;
        }
      } else { // there is no right son, so I am the left son.
        v->right->parent = v->parent;
        v->parent->left = v->right;
      }
      break;
    case LEFT:
      if ((v->parent->right)) { // if there is a right son to the parent
        if ((!comp((v->parent->right->keyValue), v->keyValue) &&
             (!comp(v->keyValue,
                    (v->parent->right->keyValue))))) { // is that son me?
          v->left->parent = v->parent;
          v->parent->right = v->left;
        } else { // I'm the left son
          v->left->parent = v->parent;
          v->parent->left = v->left;
        }
      } else { // there is no right son, so I am the left son.
        v->left->parent = v->parent;
        v->parent->left = v->left;
      }
      break;
    }
  }
//________________________________________________________________________
//  Remove an element from the tree.
//________________________________________________________________________
//  This function removes an element from the tree. It returns true if
//  the element was removed and false otherwise.
//  Notice that it can remove only with the removeLeaf() and
//  removeOnlyOneSon() functions so it switches the keys if the node has 
//  two sons to meet the requirements of those functions. then it calls 
//  the remove(AVLNode* node,AVLNode* lastNode) function to finish 
//  the removal.
//________________________________________________________________________
  bool remove(key *k) { // remove function
    if (this->isEmpty()) {
      return false;
    }
    AVLtree<key, type, compare>::AVLNode *lastNode =
        (this->root); // find the key to remove
    AVLtree<key, type, compare>::AVLNode *result =
        find((this->root), k, &lastNode);
    if (!result) { // key doesn't exist
      return false;
    } else {
      if (this->numOfElements == 1) {//has only root.
        delete this->root;
        AVLNode *newRoot = new AVLNode(NULL, NULL, dummy, NULL, NULL);
        this->root = newRoot;
        dummy->right = newRoot;
        --(this->numOfElements);
        return true;
      }
      if (!(result->left) && !(result->right)) { // leaf
        this->removeLeaf(result, comp);
        --(this->numOfElements);
      } else if (!(result->left)) { // result has only right son
        this->removeOnlyOneSon(result, comp, RIGHT);
        --(this->numOfElements);
      } else if (!(result->right)) { // result has only left son
        this->removeOnlyOneSon(result, comp, LEFT);
        --(this->numOfElements);
      } else { // result has two sons
        AVLNode *replacement = NULL;
        replacement = result->right;
        while (replacement->left) {//find the next node. 
          replacement = replacement->left;
        }
        //switch keys
        key *tempKey = result->keyValue;
        type *tempValue = result->value;
        result->keyValue = replacement->keyValue;
        result->value = replacement->value;
        replacement->keyValue = tempKey;
        replacement->value = tempValue;
        //call again to remove.
        this->remove(replacement,lastNode);
        delete replacement;
        return true;
      }
      while (lastNode != this->dummy) { // go over the path to root
        int oldHeight = lastNode->height;
        lastNode->calculateHeightAndBalance();
        if (lastNode->balance == 2 ||
            lastNode->balance == -2) { // fixing balance
          this->rollNode(lastNode);
        }
        lastNode->calculateHeightAndBalance();
        lastNode = lastNode->parent;
        lastNode->calculateHeightAndBalance();
        if (oldHeight == lastNode->height) {
          break;
        }
      }
      this->root = this->dummy->right;
      delete result;
      return true;
    }
    return true;
  }
//________________________________________________________________________
//  Remove a node (only leaf or a node with one son).
//________________________________________________________________________
//  This function is used in the remove(key *k) function to remove a node with 
//  two sons after the replacment of keys(see remove(key *k) documentation).
//  You should suppy it with the last node in the path.
//________________________________________________________________________
  bool remove(AVLNode* node,AVLNode* lastNode) {
    if (this->isEmpty()) {
      return false;
    }
    if (this->numOfElements == 1) {
      delete this->root;
      AVLNode *newRoot = new AVLNode(NULL, NULL, dummy, NULL, NULL);
      this->root = newRoot;
      dummy->right = newRoot;
      --(this->numOfElements);
      return true;
    }
    if (!node) { // key doesn't exist
      return false;
    } else {
      if (!(node->left) && !(node->right)) { // leaf
        this->removeLeaf(node, comp);
        --(this->numOfElements);
      } else if (!(node->left)) { // node has only right son
        this->removeOnlyOneSon(node, comp, RIGHT);
        --(this->numOfElements);
      } else  { // node has only left son
        this->removeOnlyOneSon(node, comp, LEFT);
        --(this->numOfElements);
      } 
      //fixing AVL tree.
      while (lastNode != this->dummy) { // go over the path to root
        int oldHeight = lastNode->height;
        lastNode->calculateHeightAndBalance();
        if (lastNode->balance == 2 ||
            lastNode->balance == -2) { // fixing balance
          this->rollNode(lastNode);
        }
        lastNode->calculateHeightAndBalance();
        lastNode = lastNode->parent; //next node in path.
        lastNode->calculateHeightAndBalance();
        if (oldHeight == lastNode->height) {
          break;
        }
      }
      this->root = this->dummy->right;
      return true;
    }
    return true;
  }
//________________________________________________________________________
//  Internal recursive inorder.
//________________________________________________________________________
//  This function outputs a sorted array (outputArray) of keys.
//  It also returns the size of the array (counter).
//________________________________________________________________________
  void inorderInternal(AVLNode *node, int *counter, key **outputArray) {
    if (!node) {
      return;
    }
    inorderInternal(node->left, counter, outputArray);
    outputArray[(*counter)++] = node->keyValue;
    inorderInternal(node->right, counter, outputArray);
  }
//________________________________________________________________________
//  Recursive inorder.
//________________________________________________________________________
//  This function outputs a sorted array (outputArray) of keys.
//  It also returns the size of the array (numOfElements).
//  !!Notice that you should delete the array!!
//________________________________________________________________________
  key **inorder(int *numOfElements) {
    if(this->isEmpty()){
      return NULL;
    }
    key **outputArray = new key *[this->numOfElements];
    int counter = 0;
    inorderInternal((this->root), &counter, outputArray);
    if (numOfElements) {
      *numOfElements = this->numOfElements;
    }
    return outputArray;
  }
//________________________________________________________________________
//  Internal recursive postorder.
//________________________________________________________________________
//  This function outputs an array (outputArray) of keys (with postorder travel).
//  It also returns the size of the array (counter).
//________________________________________________________________________
  void postorderInternal(AVLNode *node, int *counter, AVLNode **outputArray) {
    if (!node) {
      return;
    }
    postorderInternal(node->left, counter, outputArray);
    postorderInternal(node->right, counter, outputArray);
    outputArray[(*counter)++] = node;
  }
//________________________________________________________________________
//  Recursive postorder.
//________________________________________________________________________
//  This function outputs an array (outputArray) of keys (with postorder travel).
//  It also returns the size of the array (numOfElements).
//  !!Notice that you should delete the array!!
//________________________________________________________________________
  AVLNode **postorder() {
    AVLNode **outputArray = new AVLNode *[this->numOfElements];
    int counter = 0;
    postorderInternal((this->root), &counter, outputArray);
    return outputArray;
  }
//________________________________________________________________________
//  Internal recursive inorder.
//________________________________________________________________________
//  This function outputs a sorted array (outputArray) of AVLNodes.
//  It also returns the size of the array (counter).
//________________________________________________________________________
  void inorderInternalNodes(AVLNode *node, int *counter,
                            AVLNode **outputArray) {
    if (!node) {
      return;
    }
    inorderInternalNodes(node->left, counter, outputArray);
    outputArray[(*counter)++] = node;
    inorderInternalNodes(node->right, counter, outputArray);
  }
//________________________________________________________________________
//  Recursive inorder.
//________________________________________________________________________
//  This function outputs a sorted array (outputArray) of AVLNodes.
//  It also returns the size of the array (numOfElements).
//  !!Notice that you should delete the array!!
//________________________________________________________________________
  AVLNode **inorderNodes(int *numOfElements) {
    if(this->isEmpty()){
      return NULL;
    }
    AVLNode **outputArray = new AVLNode *[this->numOfElements];
    int counter = 0;
    inorderInternalNodes((this->root), &counter, outputArray);
    if (numOfElements) {
      *numOfElements = this->numOfElements;
    }
    return outputArray;
  }

//________________________________________________________________________
//  merge nodes.
//________________________________________________________________________
//  simple merge function.
//________________________________________________________________________
  void mergeNodesArrays(AVLNode **a, AVLNode **b,
                         AVLNode **c, int m, int n) {
    int i = 0, j = 0, k = 0;
    while (i < m && j < n) {
      if ((comp((a[i]->keyValue), (b[j]->keyValue)))) {
        c[k] = a[i];
        i++;
      } else {
        c[k] = b[j];
        j++;
      }
      k++;
    }
    if (i < m) {
      for (int p = i; p < m; p++) {
        c[k] = a[p];
        k++;
      }
    } else {
      for (int p = j; p < n; p++) {
        c[k] = b[p];
        k++;
      }
    }
  }
//________________________________________________________________________
//  merge AVLtrees.
//________________________________________________________________________
//  This function operates on two AVLtrees. It returns a new AVLtree with
//  the elements from the two trees.
//  !!This function deletes the two trees!!
//________________________________________________________________________
  AVLtree* merge(AVLtree** tree){
    //allocate the new tree
    AVLtree* newTree = new AVLtree(this->numOfElements+(*tree)->numOfElements);
    //get arrays of nodes from the two trees.
    AVLNode** thisTreeArray = this->inorderNodes(NULL);
    AVLNode** otherTreeArray = (*tree)->inorderNodes(NULL);
    AVLNode** mergedTreeArray;
    bool mergedTreeArrayAllocated = false;//for deletion
    //check empty tree cases
    if(thisTreeArray==NULL&&otherTreeArray!=NULL){
      mergedTreeArray = otherTreeArray;
    }else if(thisTreeArray!=NULL&&otherTreeArray==NULL){
      mergedTreeArray = thisTreeArray;
    }else if(thisTreeArray==NULL&&otherTreeArray==NULL){
      return newTree;
    }else{//both trees have elements
      //allocate array for the merged nodes. 
      mergedTreeArray = new AVLNode*[this->numOfElements+(*tree)->numOfElements];
      mergedTreeArrayAllocated = true; // for deletion
      }
      //merge the arrays.
      this->mergeNodesArrays(thisTreeArray,otherTreeArray,mergedTreeArray,this->numOfElements,(*tree)->numOfElements);
      AVLNode** newTreeArray = newTree->inorderNodes(NULL);//get empty nodes from the new tree.
      for(int i=0;i<this->numOfElements+(*tree)->numOfElements;++i){//update all the nodes.
        newTreeArray[i]->keyValue=mergedTreeArray[i]->keyValue;
        mergedTreeArray[i]->keyValue=NULL;
      }
      if(mergedTreeArrayAllocated){//deallocate the merged array if needed
        delete[] mergedTreeArray;
      }
      //delete arrays and old trees.
      delete[] thisTreeArray; 
      delete[] otherTreeArray;
      delete[] newTreeArray;
      delete this;
      delete (*tree);
      return newTree;
  }
//________________________________________________________________________
//  AVLtree destructor
//________________________________________________________________________
//  Simple AVLtree destructor.
//  !!Notice that the destructor destroys key and value!!
//________________________________________________________________________
  ~AVLtree() {
    if (!this->isEmpty()) {
      int numOfNodes=0;
      AVLNode **array = this->inorderNodes(&numOfNodes);
      for (int i = 0; i < numOfNodes; ++i) {
        delete array[i];
      }
      delete[] array;
      delete this->dummy;
    }else{
      delete this->root;
      delete this->dummy;
    }
  }
};

#endif /* AVLTREE_H */
