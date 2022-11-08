#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void helpClear(Node<Key, Value>* montez);
    int calculateHeightIfBalanced(Node<Key, Value>* root) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr):
current_(ptr)
{
    // TODO
    //did in initalizer list
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator():
current_(nullptr)
{
    // TODO
    //did above in initalizer list

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    this->current_ = successor(current_);
    return *this;   

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree():
root_(nullptr)
{
    // TODO
    //did above
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO

    //if root is null, need to add one to start because there is nothing in this tree
    if (root_ == nullptr)
    {
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
    }

    else
    {
        //make a temp node
        Node<Key, Value>* temp = root_;

        //flag for if insertion  done
        bool inserted = false;
        while (!inserted)
        {
            //if the inserting one is less than temp, we go left of temp
            if (keyValuePair.first < temp->getKey())
            {
                //check if the left of my temp is null, bc then we'll put into my temp's left
                if (temp->getLeft() == nullptr)
                {
                    Node<Key, Value>* baby = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp);
                    temp->setLeft(baby);
                    inserted = true;
                }

                //otherwise move downwards again to check next one
                else
                {
                    temp = temp->getLeft();
                }
            }
            else if (keyValuePair.first > temp->getKey())
            {
                //check if the Right of my temp is null/empty, bc then we'll put into my temp's Right
                if (temp->getRight() == nullptr)
                {
                    Node<Key, Value>* baby = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp);
                    temp->setRight(baby);
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
                temp->setValue(keyValuePair.second);
                inserted = true;
            }
        }
    }

}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO

    //if root is null, cannot remove anything so just return out
    if (root_ == nullptr)
    {
        return;
    }

    //attempt to find the key in the tree
    Node<Key, Value>* curr = this->internalFind(key);

    //check to see if key not found in tree, so then can just return
    if (curr == nullptr)
    {
        return;
    }

    //if has both children
    if (curr->getLeft() != nullptr && curr->getRight() != nullptr)
    {
        //swap the predecessor and curr, because this will  conver to 0 or 1 child case which below will handle
        nodeSwap(predecessor(curr), curr);
    }

    //now that know are not 2 children, check if left child exists and then work with that
    if (curr->getLeft() != nullptr)
    {
        Node<Key, Value>* parent = curr->getParent();
        Node<Key, Value>* child = curr->getLeft();
        
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
          root_ = child;
        }

        child->setParent(parent);
        
    }

    //if there is a right  child but not left child
    else if (curr->getRight() != nullptr)
    {
        Node<Key, Value>* parent = curr->getParent();
        Node<Key, Value>* child = curr->getRight();
        
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
            root_ = child;
        }
        
        child->setParent(parent);
        
    }

		else //is the case where has no children, but still could have parent as has been swapped so need to clear out parent's left or right
		{
			Node<Key, Value>* parent = curr->getParent();
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

    //now can null out the curr node that removed

		if (curr != root_)
		{
			delete curr;
		}

		else //is root, so need to null root so doesn't point to deleted dead pointer
		{
			delete curr;
			root_ = nullptr;
		}
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO

		//check if current exists, otherwise return
		if (current == nullptr)
		{
			return nullptr;
		}
    //if left child exists, predecessor is the rightmost node of the left subtree
    if (current->getLeft() != nullptr)
    {
        //go left

				Node<Key, Value>* curr = current->getLeft();

        //go as much right as you can
        while (curr->getRight() != nullptr)
        {
            curr = curr->getRight();
        }

        return curr;
    }

    //otherwise find the first node above that is a right child of a parent, and that parent is predecessor (because this node is that one's successor)
    else
    {
				//set curr to current
        Node<Key, Value>* curr = current;

				//if the parent is not null, then we can explore 
				while (curr->getParent() != nullptr && curr->getParent()->getRight() != curr)
				{
						curr = curr->getParent();
				}

				//will return correct value or nullptr if curr is root
				return curr->getParent();
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO

		if (current == nullptr)
		{
			return nullptr;
		}
    //if right child exists, successor is the leftmost node of the left subtree
    if (current->getRight() != nullptr)
    {
        //go right
        Node<Key, Value>* curr = current->getRight();

        //go as much left as you can
        while (curr->getLeft() != nullptr)
        {
            curr = curr->getLeft();
        }

        return curr;
    }

    //otherwise find the first node above that is a left child of a parent, and that parent is successor (because this node is that one's successor)
    else
    {
				//set curr to current
        Node<Key, Value>* curr = current;

				//if the parent is not null, then we can explore 
				while (curr->getParent() != nullptr && curr->getParent()->getLeft() != curr)
				{
						curr = curr->getParent();
				}

				//will return correct value or nullptr if curr is root
				return curr->getParent();
    }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    helpClear(root_); 
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::helpClear(Node<Key, Value>* curr)
{
    // TODO
    if (curr == nullptr)
    {
        return;
    }
    helpClear(curr->getLeft());
    helpClear(curr->getRight());
    
		//if isn't root, just delete
		if (curr != root_)
		{
			delete curr;
		}

		else //is root, so need to also set root to null because otherwise will point to dead pointer
		{
			delete curr;
			root_ = nullptr;
		}
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO

    //null check
    if (root_ == nullptr)
    {
        return nullptr;
    }
    Node<Key, Value>* curr = root_;

    //go left until get to end
    while(curr->getLeft() != nullptr)
    {
        curr = curr->getLeft();
    }
    return curr;
}
/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* curr = root_;
		
    //go through and do binary search
    while (curr != nullptr)
    {
        if (curr->getKey() > key)
        {
            curr = curr -> getLeft();
        }
        else if (curr->getKey() < key)
        {
            curr = curr -> getRight();
        }
        else if (curr->getKey() == key)//if get here, means are equal and so found
        {
            return curr;
        }
    }

    //we didn't find it, so return nullptr
    return nullptr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    //return whether differ by at most one
	//use and because has to be in range of 1 and negative 1
  int height  = calculateHeightIfBalanced(root_);
	return (height != -1);
    
}

template<typename Key, typename Value>
/// Calculates the height of the tree if it is balanced. Otherwise returns -1.
int BinarySearchTree<Key, Value>::calculateHeightIfBalanced(Node<Key, Value>* root) const {
	// Base case: an empty tree is always balanced and has a height of 0
	if (root == nullptr) return 0;

	//either way, need to get height of either subtree
	//add one to call to increase heigher since base case returns 0;
	int lefth = calculateHeightIfBalanced(root->getLeft());
	int righth = calculateHeightIfBalanced(root->getRight());

	//handles possible edge case weirdness where get 0 and negative 1
	if  ((lefth == -1  || righth == -1))
	{
		return -1;
	}

    //check if is balanced so can calc height, and then do it
	else if (abs(lefth-righth) <= 1)
	{
		if (lefth > righth)
		{
			return lefth + 1;
		}
		else
		{
			return righth + 1;
		}
	}
	else
	{
		return -1;
	}

}





template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
