#include <iostream>

using namespace std;

template <class T>
class BST
{
private:
    // The TreeNode struct is used to build the tree.
    struct TreeNode
    {
        T value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(T value1,
            TreeNode* left1 = nullptr,
            TreeNode* right1 = nullptr)
        {
            value = value1;
            left = left1;
            right = right1;
        }
    };

    TreeNode* root;

    // Various helper member functions.
    void insert(TreeNode*&, T);
    void destroySubtree(TreeNode*);
    void remove(TreeNode*&, T);
    void makeDeletion(TreeNode*&);
    int findLevel(TreeNode*&, int);
    void displayInOrder(ostream& out,TreeNode*) const;
    void displayPreOrder(ostream& out,TreeNode*) const;
    void displayPostOrder(ostream& out,TreeNode*) const;

public:
    // wrapper members
    void findItem(T) const;
    BST()		// Constructor
    {
        root = nullptr;
    }
    ~BST()		// Destructor
    {
        destroySubtree(root);
    }
    void insert(T num)
    {
        insert(root, num);
    }
    bool search(T) const;
    void remove(int num)
    {
        remove(root, num);
    }
    void showInOrder(ostream& out) const
    {
        out << "\nInOrder traversal:\n";
        displayInOrder(out,root);
    }
    void showPreOrder(ostream& out) const
    {
        out << "\nPreOrder traversal:\n";
        displayPreOrder(out,root);
    }
    void showPostOrder(ostream& out) const
    {
        out << "\nPostOrder traversal:\n";
        displayPostOrder(out,root);
    }
    void isBalanced() //check if the tree is balanced
    {
        int levelL = 0,
            levelR = 0;
        if (root)
        {
            levelL = findLevel(root->left, 0);
            levelR = findLevel(root->right, 0);
        }
        cout << "\n\nThe left level is " << levelL <<
            "\nThe right level is " << levelR << endl;

    }
};

template <class T>
void BST<T>::insert(TreeNode*& tree, T num)
{
    // If the tree is empty, make a new node and make it 
    // the root of the tree.
    if (!tree)
    {
        tree = new TreeNode(num);
        return;
    }

    // If num is already in tree: return.
    // duplicate values are not allowed
    else if (tree->value == num)
        return;

    // The tree is not empty: insert the new node into the
    // left or right subtree.
    else if (num < tree->value)
        insert(tree->left, num);
    else
        insert(tree->right, num);
}

template <class T>
void BST<T>::destroySubtree(TreeNode* tree)
{
    if (!tree) return;
    destroySubtree(tree->left);
    destroySubtree(tree->right);
    // Delete the node at the root.
    delete tree;
}


template <class T>
bool BST<T>::search(T num) const
{
    TreeNode* tree = root;

    while (tree)
    {
        if (tree->value == num) //number found
            return true;
        else if (num < tree->value) //value is greater than the number
            tree = tree->left;
        else //value is less than the number
            tree = tree->right;
    }
    return false;
}

template <class T>
void BST<T>::findItem(T num) const
{
    TreeNode* tree = root;

    while (tree)
    {
        if (tree->value == num)
        {
            cout << "The searched value was found.\n\t" << tree->value;
            return;
        }
        else if (num < tree->value)
            tree = tree->left;
        else
            tree = tree->right;
    }
    cout << "The searched value was not found in the tree.\n";
}

template <class T>
void BST<T>::remove(TreeNode*& tree, T num)
{
    if (tree == nullptr) return;
    if (num < tree->value)
        remove(tree->left, num);
    else if (num > tree->value)
        remove(tree->right, num);
    else
        // We have found the node to delete.
        makeDeletion(tree);
}

template <class T>
void BST<T>::makeDeletion(TreeNode*& tree)
{
    // Used to hold node that will be deleted.
    TreeNode* nodeToDelete = tree;

    // Used to locate the  point where the 
    // left subtree is attached.
    TreeNode* attachPoint;

    if (tree->right == nullptr)
    {
        // Replace tree with its left subtree. 
        tree = tree->left;
    }
    else if (tree->left == nullptr)
    {
        // Replace tree with its right subtree.
        tree = tree->right;
    }
    else
        //The node has two children
    {
        // Move to right subtree.
        attachPoint = tree->right;

        // Locate the smallest node in the right subtree
        // by moving as far to the left as possible.
        while (attachPoint->left != nullptr)
            attachPoint = attachPoint->left;

        // Attach the left subtree of the original tree
        // as the left subtree of the smallest node 
        // in the right subtree.
        attachPoint->left = tree->left;

        // Replace the original tree with its right subtree.
        tree = tree->right;
    }

    // Delete root of original tree
    delete nodeToDelete;
}


template <class T>
int BST<T>::findLevel(TreeNode*& tree, int level)
{
    if (tree)
    {
        int left, right;
        right = findLevel(tree->right, level) + 1; //find right level
        left = findLevel(tree->left, level) + 1; //find left level
        if (left > right)  level += left; //take the bigger one
        else level += right;
    }
    return level;
}

template <class T>
void BST<T>::displayInOrder(ostream& out,TreeNode* tree) const
{
    if (tree)
    {
        //InOrder
        //Left side->Root->Right side
        displayInOrder(out,tree->left);
        out << tree->value << "\t";
        displayInOrder(out,tree->right);
    }
}

template <class T>
void BST<T>::displayPreOrder(ostream& out,TreeNode* tree) const
{
    if (tree)
    {
        //PreOrder
        //Root->Left side->Right side
        out << tree->value << "\t";
        displayPreOrder(out,tree->left);
        displayPreOrder(out,tree->right);
    }
}

template <class T>
void BST<T>::displayPostOrder(ostream& out,TreeNode* tree) const
{
    if (tree)
    {
        //PostOrder
        //Left side->Right side->Root
        displayPostOrder(out,tree->left);
        displayPostOrder(out,tree->right);
        out << tree->value << "\t";
    }
}
