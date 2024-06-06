
// Implementation of a Binary Tree

#include<iostream>
#include <queue>

struct BinaryTreeNode{
    char key;
    int value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    
    BinaryTreeNode(char key, int value){
        this->key=key;
        this->value = value;
        left = NULL;
        right = NULL;
    }
    
    //prints out the keys in the tree inOrder
    void inOrderTraversal(BinaryTreeNode* node){
        if (node == NULL){
            return;
        }
        
        inOrderTraversal(node->left);
        std::cout << node->key << " ";
        inOrderTraversal(node->right);
    }
    
    //prints out the keys in the tree in preOrder
    void preOrderTraversal(BinaryTreeNode* node){
        if (node == NULL){
            return;
        }

        std::cout << node->key << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
    
    //prints out the keys in the tree in postOrder
    void postOrderTraversal(BinaryTreeNode* node){
        if (node == NULL){
            return;
        }

        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        std::cout << node->key << " ";

    }
    
    //Searches and returns the node with the target key using DFS assuming it is unique in the tree.
    BinaryTreeNode* DFS(BinaryTreeNode* node, char target){
        if(node == NULL){
            return NULL;
        }
        
        //search the left subtree
        BinaryTreeNode* left_res = DFS(node->left, target);
        if(left_res != NULL){
            return left_res;
        }
        
        //search the right subtree
        BinaryTreeNode* right_res = DFS(node->right, target);
        if(right_res != NULL){
            return right_res;
        }
        
        //check the current node for the specified key 
        if(node->key == target){
            return node;
        }
        
        return NULL;
    }
    
     //Searches and returns the node with the target key using BFS assuming it is unique in the tree.
    BinaryTreeNode* BFS(BinaryTreeNode* node, char target){
        if(node == NULL){
            return NULL;
        }
        
        std::queue<BinaryTreeNode*> open_queue;
        open_queue.push(node);
        
       while(!open_queue.empty()){
            BinaryTreeNode* currentNode = open_queue.front();
            std::cout << currentNode->key << " ";
            
            //is this the target we are looking for?
            if(currentNode->key ==target){
                return currentNode;
            }
            if(currentNode->left !=NULL) {
                open_queue.push(currentNode->left);
            }
            if(currentNode->right !=NULL) {
                open_queue.push(currentNode->right);
            }
            
            open_queue.pop();
       } 
       
       //if we exit the while look we have not found the target 
       return NULL;
    }
};

int main() {
    // Create a binary tree
    BinaryTreeNode* root = new BinaryTreeNode('A', 1);
    root->left = new BinaryTreeNode('B', 2);
    root->right = new BinaryTreeNode('C', 3);
    root->left->left = new BinaryTreeNode('D', 4);
    root->left->right = new BinaryTreeNode('E', 5);
    root->right->left = new BinaryTreeNode('F', 6);
    root->right->right = new BinaryTreeNode('G', 7);

    // Test in-order traversal
    std::cout << "In-order traversal: ";
    root->inOrderTraversal(root);
    std::cout << std::endl;

    std::cout << "Pre-order traversal: ";
    root->preOrderTraversal(root);
    std::cout << std::endl;

    std::cout << "Post-order traversal: ";
    root->postOrderTraversal(root);
    std::cout << std::endl;

    // Test DFS
    char targetDFS = 'E';
    BinaryTreeNode* resultDFS = root->DFS(root, targetDFS);
    if (resultDFS != nullptr) {
        std::cout << "DFS: Found node with key '" << targetDFS << "' and value '" << resultDFS->value << "'" << std::endl;
    } else {
        std::cout << "DFS: Node with key '" << targetDFS << "' not found." << std::endl;
    }

    // Test BFS
    char targetBFS = 'F';
    BinaryTreeNode* resultBFS = root->BFS(root, targetBFS);
    if (resultBFS != nullptr) {
        std::cout << "BFS: Found node with key '" << targetBFS << "' and value '" << resultBFS->value << "'" << std::endl;
    } else {
        std::cout << "BFS: Node with key '" << targetBFS << "' not found." << std::endl;
    }

    return 0;
}

/*    Question 1
In class we implemented a Binary Tree. In our implementation we wrote a method to perform an inOrder traversal of the tree. Your task is to complete the implementation for a preorder traversal and a postorder traversal of the tree. You can use the implementation of a Binary Tree from class. The method headers should be:

    //prints out the keys in the tree in preOrder

    void preOrderTraversal(BinaryTreeNode* node){}

    //prints out the keys in the tree in postOrder

    void postOrderTraversal(BinaryTreeNode* node){}
*/

/*   Question 2
In class we also implemented depth first search, and breadth first search. 
Our breadth first search implementation used a single queue. 
For this question your task is to implement breadth first search with 2 queues as explained in lecture. 
In your implementation print the path your search takes through the tree, and the level in the tree at which you found the target node. 
Your method should also return the target node.
*/

/*   Question 3
For each of the questions below draw the answer. You can draw it by hand or digitally. 
If you choose to draw it by hand, take a picture of your drawing and upload it.

Draw the binary search tree that is created if the following numbers are inserted in the tree in the given order. 
12 15 3 35 21 42 14
Draw a balanced binary search tree containing the same numbers given in part (a).
*/

/*    Quesiton 4
Given a Binary Search Tree(BST), remove nodes from the BST that have keys outside the a specified range. Take the target range as an input. 
For each node, if the key is outside the range delete the node and adjust your BST such that it remains a valid BST.
When you are done print the resulting tree using a similar approach to BFS such that the tree is printed level by level.
*/