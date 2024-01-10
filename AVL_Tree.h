#ifndef AVL_TREE_AVL_TREE_H
#define AVL_TREE_AVL_TREE_H

#include <vector>
#include <algorithm>
#include <stack>

class avlTree {
private:
    struct node {
        int data;
        struct node* leftNode;
        struct node* rightNode;
        int height;
        struct node* parent;
    };
    struct node* root;

public:
    avlTree();
    avlTree(int headVal);
    int height(struct node* node);
    void updateHeight(struct node* node);
    void add(int val);
    void remove(int val);
    struct node* leftRotation(struct node* z);
    struct node* rightRotation(struct node* z);
    void rebalance(struct node* n);
    int balanceFactor(struct node* n);
    std::vector<int> preorder_traversal(struct node* root);

    bool is_valid_avl(avlTree tree) {

        std::stack<avlTree::node*> stack;
        stack.push(tree.root);
        if (tree.root != nullptr && tree.root->parent != nullptr){
            return false;
        }

        while (!stack.empty()) {
            avlTree::node* node = stack.top();
            stack.pop();

            if (node) {
                int left_height = node->leftNode ? node->leftNode->height : -1;
                int right_height = node->rightNode ? node->rightNode->height : -1;

                if (node->height != 1 + std::max(left_height, right_height)) {
                    return false;
                }

                if (node->parent) {
                    avlTree::node* check = nullptr;
                    if (node->data < node->parent->data) {
                        check = node->parent->leftNode;
                    }
                    else {
                        check = node->parent->rightNode;
                    }

                    if (check != node) {
                        return false;
                    }
                }
                else {
                    if (node != tree.root) {
                        return false;
                    }
                }

                stack.push(node->rightNode);
                stack.push(node->leftNode);
            }
        }

        return true;
    }
};


#endif //AVL_TREE_AVL_TREE_H
