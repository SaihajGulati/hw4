#include "equal-paths.h"
#include <algorithm>
using namespace std;


bool PathFinder(Node* root, int& maxLength, int currLength)
{
    //base case, if get past leaf node, then is true by default as both leaves do not exist and is thus  trivially equalpaths for this node onward
    if (root == nullptr)
    {
        //if max length has not been set yet, then set to what ended up with heree
        if (maxLength == -1)
        {
            maxLength = currLength;
        }

        //if the length of path found was not equal to the  max legnth, then not equal paths so return false
        else if (maxLength != currLength) 
        {
            return false;
        }

        //otherwise if it is equal, so we're good on this path matching the others
        return true;
    }

    //if not base case, then try left and right path
    return PathFinder(root->left, maxLength, currLength + 1) && PathFinder(root->right, maxLength, currLength + 1);
}


bool equalPaths(Node * root)
{
    int maxPath = -1;
    int value = 0;
    return PathFinder(root, maxPath, value);
}

