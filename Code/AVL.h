#pragma once
#include "Items.h"


class Node
{
public:
    Treasure key;
    Node* left;
    Node* right;
    int height;
    Node(Treasure k)
    {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};


class AvlTree
{
public:
    Node* root;

    AvlTree()
    {
        root = nullptr;
    }
    int height(Node* N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation  
        x->right = y;
        y->left = T2;

        // Update heights  
        y->height = max(height(y->left),
            height(y->right)) + 1;
        x->height = max(height(x->left),
            height(x->right)) + 1;

        // Return new root  
        return x;
    }

    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation  
        y->left = x;
        x->right = T2;

        // Update heights  
        x->height = max(height(x->left),
            height(x->right)) + 1;
        y->height = max(height(y->left),
            height(y->right)) + 1;

        // Return new root  
        return y;
    }

    int getBalance(Node* N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* insert(Node* node, Treasure key)
    {
        /* 1. Perform the normal BST insertion */
        if (node == NULL)
        {
           // cout << "YYEYEEEE";
            return new Node(key);
        }

        if (key.value < node->key.value)
            node->left = insert(node->left, key);
        else // (key > node->key)
            node->right = insert(node->right, key);
   //     else // Equal keys are not allowed in BST  
      //      return node;

        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left),
            height(node->right));

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then  
        // there are 4 cases  

        // Left Left Case  
        if (balance > 1 && key.value < node->left->key.value)
            return rightRotate(node);

        // Right Right Case  
        if (balance < -1 && key.value > node->right->key.value)
            return leftRotate(node);

        // Left Right Case  
        if (balance > 1 && key.value > node->left->key.value)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case  
        if (balance < -1 && key.value < node->right->key.value)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    Node* minValueNode(Node* node)
    {
        Node* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != NULL)
            current = current->left;

        return current;
    }

    Node* deleteNode(Node* root, Treasure key)
    {

        // STEP 1: PERFORM STANDARD BST DELETE 
        if (root == NULL)
            return root;

        // If the key to be deleted is smaller 
        // than the root's key, then it lies
        // in left subtree 
        if (key.value < root->key.value)
            root->left = deleteNode(root->left, key);

        // If the key to be deleted is greater 
        // than the root's key, then it lies 
        // in right subtree 
        else if (key.value > root->key.value)
            root->right = deleteNode(root->right, key);

        // if key is same as root's key, then 
        // This is the node to be deleted 
        else
        {
            // node with only one child or no child 
            if ((root->left == NULL) ||
                (root->right == NULL))
            {
                Node* temp = root->left ?
                    root->left :
                    root->right;

                // No child case 
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else // One child case 
                    *root = *temp; // Copy the contents of 
                // the non-empty child 
                free(temp);
            }
            else
            {
                // node with two children: Get the inorder 
                // successor (smallest in the right subtree) 
                Node* temp = minValueNode(root->right);

                // Copy the inorder successor's 
                // data to this node 
                root->key = temp->key;

                // Delete the inorder successor 
                root->right = deleteNode(root->right,
                    temp->key);
            }
        }

        // If the tree had only one node
        // then return 
        if (root == NULL)
            return root;

        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
        root->height = 1 + max(height(root->left),
            height(root->right));

        // STEP 3: GET THE BALANCE FACTOR OF 
        // THIS NODE (to check whether this 
        // node became unbalanced) 
        int balance = getBalance(root);

        // If this node becomes unbalanced, 
        // then there are 4 cases 

        // Left Left Case 
        if (balance > 1 &&
            getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case 
        if (balance > 1 &&
            getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case 
        if (balance < -1 &&
            getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case 
        if (balance < -1 &&
            getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void Insert(Treasure key)
    {
        root = insert(root, key);
        cout << "added to inventory" << endl;
    }

    void inOrder(Node* root, string &s)
    {
     //   cout << s;
        if (root != NULL)
        {
           // cout << root->key.name << " ";
            inOrder(root->left, s);
            cout << root->key.name << " ";
            s += root->key.name + " " + "\n";
            inOrder(root->right, s);
         //   cout << "!@#$@";
        }
      //  cout << "????";
    }

};