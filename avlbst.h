#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void removeFix(AVLNode<Key,Value>* n, int8_t diff);
    void rotateRight(AVLNode<Key,Value>* n);
    void rotateLeft(AVLNode<Key, Value>* n);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    //if root is null, need to add one to start because there is nothing in this tree
    if (this->root_ == nullptr)
    {
        //make new avl node (by default sets balance_ to 0)
       this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);

    }

    else
    {
        //make a temp node set to root
        AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);

        //flag for if insertion  done
        bool inserted = false;
        while (!inserted)
        {
            //if the inserting one is less than temp, we go left of temp
            if (new_item.first < temp->getKey())
            {
                //check if the left of my temp is null, bc then we'll put into my temp's left
                if (temp->getLeft() == nullptr)
                {
                    AVLNode<Key, Value>* baby = new AVLNode<Key, Value>(new_item.first, new_item.second, temp);
                    temp->setLeft(baby);
                    if (temp->getBalance() == 1 || temp->getBalance() == -1)
                    {
                        temp->setBalance(0);
                    }
                    else if (temp->getBalance() == 0)
                    {
                        insertFix(temp, baby);
                    }
                    inserted = true;
                }

                //otherwise move downwards again to check next one
                else
                {
                    temp = temp->getLeft();
                }
            }
            else if (new_item.first > temp->getKey())
            {
                //check if the Right of my temp is null/empty, bc then we'll put into my temp's Right
                if (temp->getRight() == nullptr)
                {
                    AVLNode<Key, Value>* baby = new AVLNode<Key, Value>(new_item.first, new_item.second, temp);
                    temp->setRight(baby);
                    if (temp->getBalance() == 1 || temp->getBalance() == -1)
                    {
                        temp->setBalance(0);
                    }
                    else if (temp->getBalance() == 0)
                    {
                        insertFix(temp, baby);
                    }
                    inserted = true;
                }

                //othewise, move down to the right to check again
                else
                {
                    temp = temp->getRight();
                }
            }
            
            //otherwise they are equal so overwrite
            else
            {
                temp->setValue(new_item.second);
                inserted = true;
            }
        }
    }
}

//make insertFix function, passed parent node and also the node that was just inserted
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
    if (p == nullptr || p->getParent() == nullptr)
    {
        return;
    }

    //make g the parent of p
    AVLNode<Key, Value>* g = p->getParent();

    //handle case where p is the left child of p
    if (g->getLeft() == p)
    {
        //update g's balance by 1 negative since is left added
        g->updateBalance(-1);
        //case where g's balance is 0
        if (g->getBalance() == 0)
        {
            return;
        }
        //case where g's balance is -1, so recurse up
        else if (g->getBalance() == -1)
        {
            insertFix(g, p);
        }
        //case where g's balance is -2
        else if (g->getBalance() == -2)
        {
            //means zig-zig case so handle as such
            if (n == p->getLeft())
            {
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
            }

            //zig-zag case
            else if (n == p->getRight())
            {
                //do the rotations
                rotateLeft(p);
                rotateRight(g);
                //case where balance is -1
                if (n->getBalance() == -1)
                {
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                }
                //case where balance is 0
                else if (n->getBalance() == 0)
                {
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                //case where balance is 1
                else if (n->getBalance() == 1)
                {
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);
                }

            }
        }
    }
    //handle case where p is right child of g
    else
    {
        //update balance by 1 positive since is right added
        g->updateBalance(1);
        //handle case where is 0, done so exit
        if (g->getBalance() == 0)
        {
            return;
        }
        //handle case where balance is 1, so recurse up
        else if (g->getBalance() == 1)
        {
            insertFix(g, p);
        }
        //handle case where balance is off
        else if (g->getBalance() == 2)
        {
            //zig-zig case
            if (n == p->getRight())
            {
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            //zig-zag case  
            else if (n == p->getLeft())
            {
                //do the rotations
                rotateRight(p);
                rotateLeft(g);
                //case where balance is 1
                if (n->getBalance() == 1)
                {
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                }
                    //case where balance is 0
                    else if (n->getBalance() == 0)
                {
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                //case where balance is -1
                else if (n->getBalance() == -1)
                {
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);
                }

            }
        }
    }


}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO

    //if root is null, cannot remove anything so just return out
    if (this->root_ == nullptr)
    {
        return;
    }

    //attempt to find the key in the tree
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));

    //check to see if key not found in tree, so then can just return
    if (curr == nullptr)
    {
        return;
    }

    //if has both children
    if (curr->getLeft() != nullptr && curr->getRight() != nullptr)
    {
        //swap the predecessor and curr, because this will  conver to 0 or 1 child case which below will handle
        nodeSwap(static_cast<AVLNode<Key, Value>*>(this->predecessor(curr)), curr);
    }

    //now that know are not 2 children, check if left child exists and then work with that
    if (curr->getLeft() != nullptr)
    {
        AVLNode<Key, Value>* parent = curr->getParent();
        AVLNode<Key, Value>* child = curr->getLeft();
        
        //if curr is the parent's left child, we know to change the parent's left child to curr's left child we are looking at
        if (parent != nullptr)
        {
            if (parent->getLeft() == curr)
            {
                parent->setLeft(child);
            }

            //otherwise it's the parent's right that is curr, so parent's right needs to be child
            else
            {
                parent->setRight(child);
            } 
        }
        else
        {
         this->root_ = child;
        }

        child->setParent(parent);
        
    }

    //if there is a right  child but not left child
    else if (curr->getRight() != nullptr)
    {
        AVLNode<Key, Value>* parent = curr->getParent();
        AVLNode<Key, Value>* child = curr->getRight();
        
        if (parent != nullptr)
        {
            //if curr is the parent's left child, we know to change the parent's left child to curr's left child we are looking at
            if (parent->getLeft() == curr)
            {
                parent->setLeft(child);
            }

            //otherwise it's the parent's right that is curr, so parent's right needs to be child
            else
            {
                parent->setRight(child);
            }
        }
        else
        {
           this->root_ = child;
        }
        
        child->setParent(parent);
        
    }

		else //is the case where has no children, but still could have parent as has been swapped so need to clear out parent's left or right
		{
			AVLNode<Key, Value>* parent = curr->getParent();
			if (parent != nullptr)
			{
				if (parent->getLeft() == curr)
            {
                parent->setLeft(nullptr);
            }

            //otherwise it's the parent's right that is curr, so parent's right needs to be null since deleting
            else
            {
                parent->setRight(nullptr);
            }
			}
		}

    AVLNode<Key, Value>* p = static_cast<AVLNode<Key, Value>*>(curr->getParent());

    //setup different thing
    int8_t diff = 0;
    if (p != nullptr)
    {
        if (p->getLeft() == curr)
        {
            diff = 1;            
        }
        else
        {
            diff = -1;
        }
    }

    //now can null out the curr node that removed
    if (curr != this->root_)
    {
        delete curr;
    }
    else //is root, so need to null root so doesn't point to deleted dead pointer
    {
        delete curr;
        this->root_ = nullptr;
    }

    //patch tree
    removeFix(p, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, int8_t diff)
{
    //null check
    if (n == nullptr)
    {
        return;
    }

    //compute next recursive call's arguments
    AVLNode<Key, Value>* p = n->getParent(); 
    int8_t ndiff = 0;
    if (p != nullptr)
    {
        //set ndiff based on whether n is left child or right child
        if (p->getLeft() == n)
        {
            ndiff = 1;
        }
        else
        {
            ndiff = -1;
        }
    }
    //handle -1 difference to balance case
    if (diff == -1)
    {
        //handle case where balance is now -2, which means unbalanced and have to work on it
        if (n->getBalance() + diff == -2)
        {
            //c is taller child (left since is negative and so left child is taller child)
            AVLNode<Key, Value>* c = n->getLeft();
            
            //if c is also -1 then is zig zig as means c has a left child thta's taller, case so rotate
            if (c->getBalance() == -1)
            {
                rotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
                //recurse up
                removeFix(p, ndiff);
            }
            //handle case where is 0, also a zig zig as means has left child and is easier to do zig zig
            else if (c->getBalance() == 0)
            {
                rotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
                //no recusing as got to something that is perfectly balanced above so are chilling and done bc cannot be unbalanced tree
            }

            //handle case where is +1, which means a right child of a left child, and therefore zig-zag case
            else if (c->getBalance() == 1)
            {
                AVLNode<Key, Value>* g = c->getRight();
                rotateLeft(c);
                rotateRight(n);
                //handle case where g had balance of 1 before
                if (g->getBalance() == 1)
                {
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                }
                //handle case where g had balance of 0 before
                else if (g->getBalance() == 0)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                //handle case where g had balance of -1 before
                else if (g->getBalance() == -1)
                {
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                //recurse back up
                removeFix(p,ndiff);
            }
        }
        //handle case where balance now is -1, just update and done as not unbalanced
        else if (n->getBalance() + diff == -1)
        {
            n->setBalance(-1);
        }
        //handle case where balance is now 0, need to recurse larger tail
        else if (n->getBalance() + diff == 0)
        {
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
    //handle -1 case for diff
    else if (diff == 1)
    {
        //handle case where balance is now 2, which means unbalanced and have to work on it
        if (n->getBalance() + diff == 2)
        {
            //c is taller child (right since is negative and so left child is taller child)
            AVLNode<Key, Value>* c = n->getRight();
            
            //if c is also -1 then is zig zig as means c has a left child thta's taller, case so rotate
            if (c->getBalance() == 1)
            {
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                //recurse up
                removeFix(p, ndiff);
            }
            //handle case where is 0, also a zig zig as means has left child and is easier to do zig zig
            else if (c->getBalance() == 0)
            {
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
                //no recusing as got to something that is perfectly balanced above so are chilling and done bc cannot be unbalanced tree
            }

            //handle case where is +1, which means a right child of a left child, and therefore zig-zag case
            else if (c->getBalance() == -1)
            {
                AVLNode<Key, Value>* g = c->getLeft();
                rotateRight(c);
                rotateLeft(n);
                //handle case where g had balance of 1 before
                if (g->getBalance() == -1)
                {
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                }
                //handle case where g had balance of 0 before
                else if (g->getBalance() == 0)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                //handle case where g had balance of -1 before
                else if (g->getBalance() == 1)
                {
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                //recurse back up
                removeFix(p,ndiff);
            }
        }
        //handle case where balance now is -1, just update and done as not unbalanced
        else if (n->getBalance() + diff == 1)
        {
            n->setBalance(1);
        }
        //handle case where balance is now 0, need to recurse larger tail
        else if (n->getBalance() + diff == 0)
        {
            n->setBalance(0);
            removeFix(p, ndiff);
        }        
    }
    
}

template<class Key, class Value>
/**cases to handle for rotate:
 * when n->getLeft() has left and right node, need to move it's right to become y's top's left
 * update root if rotating one that is root and/or parent is nullptr
 * 
*/
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* n)
{
    if (n == nullptr)
    {
        return;
    }

    AVLNode<Key,Value>* nChild = n->getLeft();//if is nullptr, means n has no children to rotate up
    if (nChild == nullptr) //means nothing to move up
    {
        return;
    }

    AVLNode<Key,Value>* nChildRight = nChild->getRight(); //will be nullptr if no right child of left child, just means will assign nullptr as left child later
    AVLNode<Key,Value>* nParent = n->getParent();//if is nullptr, n is root and so child will end up being root anad need to switch

    //moves over below node's right child to be n's left child, will be nullptr if nChildRight does not exist
    //also make it's parent it's former child
    n->setLeft(nChildRight);
    n->setParent(nChild);

    if (nChildRight != nullptr)
    {
        nChildRight->setParent(n);
    }

    //sort out nChild
    //for child that is rotated up where n was, set it's  parent to n's parent
    //set it's right to n
    nChild->setParent(nParent);
    nChild->setRight(n);

    //sort out nParent
    //then connect the parent to the child correctly but checking to see what side it is
    if (nParent == nullptr) //means is root as nothing above
    {
        this->root_ = nChild;

    }
    else if (nParent->getRight() == n)
    {
        nParent->setRight(nChild);
    }
    else if (nParent->getLeft() == n)
    {
        nParent->setLeft(nChild);
    }
}

template<class Key, class Value>
/**cases to handle for rotate:
 * when n->getLeft() has left and right node, need to move it's right to become y's top's left
 * update root if rotating one that is root and/or parent is nullptr
 * 
*/
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n)
{
    if (n == nullptr)
    {
        return;
    }

    AVLNode<Key,Value>* nChild = n->getRight();//if is nullptr, means n has no children to rotate up
    if (nChild == nullptr) //means nothing to move up
    {
        return;
    }

    AVLNode<Key,Value>* nChildLeft = nChild->getLeft(); //will be nullptr if no right child of left child, just means will assign nullptr as left child later
    AVLNode<Key,Value>* nParent = n->getParent();//if is nullptr, n is root and so child will end up being root anad need to switch

    //moves over below node's right child to be n's left child, will be nullptr if nChildRight does not exist
    //also make it's parent it's former child
    n->setRight(nChildLeft);
    n->setParent(nChild);

    if (nChildLeft != nullptr)
    {
        nChildLeft->setParent(n);
    }

    //sort out nChild
    //for child that is rotated up where n was, set it's  parent to n's parent
    //set it's right to n
    nChild->setParent(nParent);
    nChild->setLeft(n);

    //sort out nParent
    //then connect the parent to the child correctly but checking to see what side it is
    if (nParent == nullptr) //means is root as nothing above
    {
        this->root_ = nChild;

    }
    else if (nParent->getRight() == n)
    {
        nParent->setRight(nChild);
    }
    else if (nParent->getLeft() == n)
    {
        nParent->setLeft(nChild);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}



#endif
