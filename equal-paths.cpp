#include "equal-paths.h"
#include <algorithm>
using namespace std;


bool PathFinder(Node* root, int& maxLength, int currLength)
{
    //base case, if get past leaf node, then is true by default as both leaves do not exist and is thus trivially equalpaths for this node onward
    if (root == nullptr)
    {
        //if length of paths to compare to has not been set yet, then set to what ended up with here
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

		//handles case where tree path becomes one sided towards right
		else if (root->left == nullptr && root->right != nullptr)
		{
			return PathFinder(root->right, maxLength, currLength + 1);
		}

		//handles case where tree path becomes one sided towards left
		else if (root->right == nullptr && root->left != nullptr)
		{
			return PathFinder(root->left, maxLength, currLength + 1);
		}

    //if not any of those, then you are good to check both sides
    return PathFinder(root->left, maxLength, currLength + 1) && PathFinder(root->right, maxLength, currLength + 1);
}


bool equalPaths(Node * root)
{
    int maxPath = -1;
    int value = 0;
    return PathFinder(root, maxPath, value);
}

