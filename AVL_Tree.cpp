#include "AVL_Tree.h"
#include <vector>
#include <iostream>
using namespace std;

avlTree::avlTree() {
    root = nullptr;
}

avlTree::avlTree(int rootVal) {
    struct node* n = new node{rootVal, nullptr, nullptr, 0, nullptr};
    root = n;
}

int avlTree::height(struct node* node) {
    if (node == nullptr) {
        return -1;
    }
    return node->height;
}

void avlTree::updateHeight(struct node* node) {
    node->height = max( this->height(node->leftNode), this->height(node->rightNode)) + 1;
}

void avlTree::add(int val) {
    struct node* n = new node{val, nullptr, nullptr, 0, nullptr};

    // If adding a root
    if (root == nullptr) {
        root = n;
        return;
    }

    // Adding new node into tree
    struct node* parentNode = root;
    while (true) {
        // Check if value is already in tree
        if (val == parentNode->data) {
            return;
        }
        else if (val >= parentNode->data) {
            if (parentNode->rightNode == nullptr) {
                parentNode->rightNode = n;
                n->parent = parentNode;
                break;
            }
            parentNode = parentNode->rightNode;
        }
        else {
            if (parentNode->leftNode == nullptr) {
                parentNode->leftNode = n;
                n->parent = parentNode;
                break;
            }
            parentNode = parentNode->leftNode;
        }
    }

    // Rebalancing the tree
    parentNode = n->parent;
    while (parentNode != nullptr) {
        rebalance(parentNode);
        parentNode = parentNode->parent;
    }
}

void avlTree::remove(int val) {
    if (root == nullptr) {
        return;
    }
    struct node* p = nullptr;

    // Creating removeNode and finding the node we are deleting
    struct node* beforeRemoveNode = nullptr;
    struct node* removeNode = root;
    while (removeNode != nullptr) {
        if (removeNode->data > val) {
            beforeRemoveNode = removeNode;
            removeNode = removeNode->leftNode;
        }
        else if (removeNode->data < val) {
            beforeRemoveNode = removeNode;
            removeNode = removeNode->rightNode;
        }
        else {
            break;
        }
    }
    if (removeNode == nullptr) {
        return;
    }

    // No children deletion
    if ((removeNode->leftNode == nullptr) && (removeNode->rightNode == nullptr)) {
        if (removeNode == root) {
            root = nullptr;
            delete removeNode;
        }

        else if (removeNode == beforeRemoveNode->rightNode) {
            beforeRemoveNode->rightNode = nullptr;
            delete removeNode;
        }

        else {
            beforeRemoveNode->leftNode = nullptr;
            delete removeNode;
        }
        p = beforeRemoveNode;
    }

    // Deleting node with left child
    else if ((removeNode->leftNode != nullptr) && (removeNode->rightNode == nullptr)) {
        if (removeNode == root) {
            root = removeNode->leftNode;
            root->parent = nullptr;
            delete removeNode;
        }

        else if (removeNode == beforeRemoveNode->rightNode) {
            beforeRemoveNode->rightNode = removeNode->leftNode;
            removeNode->leftNode->parent = beforeRemoveNode;
            delete removeNode;
        }

        else {
            beforeRemoveNode->leftNode = removeNode->leftNode;
            removeNode->leftNode->parent = beforeRemoveNode;
            delete removeNode;
        }
        p = beforeRemoveNode;
    }

    // Deleting node with right child
    else if ((removeNode->leftNode == nullptr) && (removeNode->rightNode != nullptr)) {
        if (removeNode == root) {
            root = removeNode->rightNode;
            root->parent = nullptr;
            delete removeNode;
        }
        else if (removeNode->data > beforeRemoveNode->data) {
            beforeRemoveNode->rightNode = removeNode->rightNode;
            removeNode->rightNode->parent = beforeRemoveNode;
            delete removeNode;
        }
        else {
            beforeRemoveNode->leftNode = removeNode->rightNode;
            removeNode->rightNode->parent = beforeRemoveNode;
            delete removeNode;
        }
        p = beforeRemoveNode;
    }

    // Deleting node with 2 children
    else if ((removeNode->leftNode != nullptr) && (removeNode->rightNode != nullptr)) {
        // Finding replacement node
        struct node* beforeReplacementNode = removeNode;
        struct node* replacementNode = removeNode->rightNode;
        while (replacementNode->leftNode != nullptr) {
            beforeReplacementNode = replacementNode;
            replacementNode = replacementNode->leftNode;
        }

        // If removing root
        if (removeNode == root) {
            root = replacementNode;
            if (removeNode != beforeReplacementNode) {
                if (replacementNode->rightNode != nullptr) {
                    beforeReplacementNode->leftNode = replacementNode->rightNode;
                    replacementNode->rightNode->parent = beforeReplacementNode;
                } else {
                    beforeReplacementNode->leftNode = nullptr;
                }
            }
            if (removeNode->rightNode != replacementNode) {
                replacementNode->rightNode = removeNode->rightNode;
            }
            if (removeNode->leftNode != replacementNode) {
                replacementNode->leftNode = removeNode->leftNode;
            }
            replacementNode->parent = nullptr;
            p = beforeReplacementNode;
            if (beforeReplacementNode == removeNode) {
                p = replacementNode;
            }
            removeNode->rightNode->parent = replacementNode;
            removeNode->leftNode->parent = replacementNode;
            delete removeNode;
            if (this->root != nullptr) {
                this->root->parent = nullptr;
            }
            while (p != nullptr) {
                rebalance(p);
                p = p->parent;
            }
            rebalance(root);
            return;
        }

        // Make sure removeNode is not parent of replacement node
        if (beforeReplacementNode == removeNode) {
            beforeReplacementNode = beforeRemoveNode;
        }

        // If removeNode is a right child
        if (beforeRemoveNode->rightNode == removeNode) {
            beforeRemoveNode->rightNode = replacementNode;
            replacementNode->parent = beforeRemoveNode;
            replacementNode->leftNode = removeNode->leftNode;
            removeNode->leftNode->parent = replacementNode;

            if (beforeReplacementNode != beforeRemoveNode) {
                beforeReplacementNode->leftNode = replacementNode->rightNode;
                if (replacementNode->rightNode != nullptr) {
                    replacementNode->rightNode->parent = beforeReplacementNode;
                }
            }

            if (removeNode->rightNode != replacementNode) {
                replacementNode->rightNode = removeNode->rightNode;
                removeNode->rightNode->parent = replacementNode;
            }
            delete removeNode;
        }

        // If removeNode is a left child
        else if (beforeRemoveNode->leftNode == removeNode) {
            beforeRemoveNode->leftNode = replacementNode;
            replacementNode->parent = beforeRemoveNode;
            replacementNode->leftNode = removeNode->leftNode;
            removeNode->leftNode->parent = replacementNode;

            if (beforeReplacementNode != beforeRemoveNode) {
                beforeReplacementNode->leftNode = replacementNode->rightNode;
                if (replacementNode->rightNode != nullptr) {
                    replacementNode->rightNode->parent = beforeReplacementNode;
                }
            }

            if (removeNode->rightNode != replacementNode) {
                replacementNode->rightNode = removeNode->rightNode;
                removeNode->rightNode->parent = replacementNode;
            }
            delete removeNode;
        }
        p = beforeReplacementNode;
        if (beforeReplacementNode == beforeRemoveNode) {
            p = replacementNode;
        }
    }
    if (this->root != nullptr) {
        this->root->parent = nullptr;
    }
    while (p != nullptr) {
        rebalance(p);
        //cout << p->data << ", ";
        p = p->parent;
    }
}

struct avlTree::node* avlTree::leftRotation(struct node* z) {
    // tracking nodes
    struct node* y = z->rightNode;
    struct node* t2 = y->leftNode;
    struct node* zParent = z->parent;

    // repositioning t2
    if (t2 != nullptr) {
        t2->parent = z;
    }
    z->rightNode = t2;

    // y adopting z
    y->leftNode = z;
    y->parent = z->parent;
    z->parent = y;

    if (zParent != nullptr) {
        if (y->data >= zParent->data) {
            zParent->rightNode = y;
        } else {
            zParent->leftNode = y;
        }
    }
    if (z == root) {
        root = y;
    }
    updateHeight(y);
    updateHeight(z);
    return y;
}

struct avlTree::node* avlTree::rightRotation(struct node* z) {
    // tracking nodes
    struct node* y = z->leftNode;
    struct node* t3 = y->rightNode;
    struct node* zParent = z->parent;

    // repositioning t3
    if (t3 != nullptr) {
        t3->parent = z;
    }
    z->leftNode = t3;

    // y adopting z
    y->rightNode = z;
    y->parent = zParent;
    z->parent = y;

    if (zParent != nullptr) {
        if (y->data >= zParent->data) {
            zParent->rightNode = y;
        } else {
            zParent->leftNode = y;
        }
    }
    if (z == root) {
        root = y;
    }
    updateHeight(y);
    updateHeight(z);
    return y;
}

void avlTree::rebalance(struct node* n) {
    //cout << "rebalance";
    if (balanceFactor(n) < -1) {
        if (balanceFactor(n->rightNode) > 0) {
            rightRotation(n->rightNode);
        }
        leftRotation(n);
    }
    else if (balanceFactor(n) > 1) {
        if (balanceFactor(n->leftNode) < 0) {
            leftRotation(n->leftNode);
        }
        rightRotation(n);
    }
    else {
        updateHeight(n);
    }
}

int avlTree::balanceFactor(struct node* n) {
    if (n == nullptr) {
        return 0;
    }
    int bfactor = this->height(n->leftNode) - this->height(n->rightNode);
    return (this->height(n->leftNode) - this->height(n->rightNode));
}

vector<int> avlTree::preorder_traversal(struct node* root) {
    vector<int> nums;
    if (root != nullptr) {
        nums.push_back(root->data);
        vector<int> leftNodeVect = preorder_traversal(root->leftNode);
        for (int i=0; i<leftNodeVect.size(); i++) {
            nums.push_back(leftNodeVect[i]);
        }
        vector<int> rightNodeVect = preorder_traversal(root->rightNode);
        for (int i=0; i<rightNodeVect.size(); i++) {
            nums.push_back(rightNodeVect[i]);
        }
    }
    return nums;
}
