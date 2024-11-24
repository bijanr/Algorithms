#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct Node {
    int data;
    int color; // RED or BLACK
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// Function prototypes
Node* createNode(int data);
Node* rotateLeft(Node* root, Node* node);
Node* rotateRight(Node* root, Node* node);
void insertFixup(Node** root, Node* node);
void insert(Node** root, int data);
Node* minimum(Node* node);
Node* successor(Node* node);
void deleteFixup(Node** root, Node* node, Node* parent);
void delete(Node** root, int data);
void inorderTraversal(Node* root);
void printTree(Node* root, int level, int side);
void freeTree(Node* root);

int main() {
    Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\nRed-Black Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Inorder Traversal\n");
        printf("4. Print Tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &data);
                insert(&root, data);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &data);
                delete(&root, data);
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printTree(root, 0, 0);
                printf("\n");
                break;
            case 5:
                freeTree(root);
                exit(0);
        }
    }
}

// Create a new Red-Black Tree node
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED; // New nodes are red
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

// Left rotation
Node* rotateLeft(Node* root, Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != NULL) {
        rightChild->left->parent = node;
    }
    
    rightChild->parent = node->parent;

    if (node->parent == NULL) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;

    return root;
}

// Right rotation
Node* rotateRight(Node* root, Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != NULL) {
        leftChild->right->parent = node;
    }
    
    leftChild->parent = node->parent;

    if (node->parent == NULL) {
        root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;

    return root;
}

// Fix the Red-Black Tree after insertion
void insertFixup(Node** root, Node* node) {
    Node* parent = NULL;
    Node* grandparent = NULL;

    while (node != *root && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    node = parent;
                    *root = rotateLeft(*root, node);
                }

                parent->color = BLACK;
                grandparent->color = RED;
                *root = rotateRight(*root, grandparent);
            }
        } else {
            Node* uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    *root = rotateRight(*root, node);
                }

                parent->color = BLACK;
                grandparent->color = RED;
                *root = rotateLeft(*root, grandparent);
            }
        }
    }

    (*root)->color = BLACK;
}

// Insert a new node into the Red-Black Tree
void insert(Node** root, int data) {
    Node* newNode = createNode(data);
    Node* parent = NULL;
    Node* current = *root;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;

    if (parent == NULL) {
        *root = newNode;
    } else if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    insertFixup(root, newNode);
}

// Find the minimum node in a subtree
Node* minimum(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Find the successor of a node
Node* successor(Node* node) {
    if (node->right != NULL) {
        return minimum(node->right);
    }

    Node* parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

// Fix the Red-Black Tree after deletion
void deleteFixup(Node** root, Node* node, Node* parent) {
    while (node != *root && (node == NULL || node->color == BLACK) ) {
        if (node == parent->left) {
            Node* sibling = parent->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                *root = rotateLeft(*root, parent);
                sibling = parent->right;
            }

            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                (sibling->right == NULL || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                if (sibling->right == NULL || sibling->right->color == BLACK) {
                    if (sibling->left != NULL) {
                        sibling->left->color = BLACK;
                    }
                    sibling->color = RED;
                    *root = rotateRight(*root, sibling);
                    sibling = parent->right;
                }

                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->right != NULL) {
                    sibling->right->color = BLACK;
                }
                *root = rotateLeft(*root, parent);
                node = *root;
            }
        } else {
            Node* sibling = parent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                *root = rotateRight(*root, parent);
                sibling = parent->left;
            }

            if ((sibling->right == NULL || sibling->right->color == BLACK) &&
                (sibling->left == NULL || sibling->left->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                if (sibling->left == NULL || sibling->left->color == BLACK) {
                    if (sibling->right != NULL) {
                        sibling->right->color = BLACK;
                    }
                    sibling->color = RED;
                    *root = rotateLeft(*root, sibling);
                    sibling = parent->left;
                }

                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->left != NULL) {
                    sibling->left->color = BLACK;
                }
                *root = rotateRight(*root, parent);
                node = *root;
            }
        }
    }

    if (node != NULL) {
        node->color = BLACK;
    }
}

// Delete a node from the Red-Black Tree
void delete(Node** root, int data) {
    Node* node = *root;
    Node* child = NULL;
    Node* parent = NULL;
    Node* nodeToDelete = NULL;

    while (node != NULL) {
        if (node->data == data) {
            nodeToDelete = node;
            break;
        } else if (data < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (nodeToDelete == NULL) {
        printf("Node with data %d not found.\n", data);
        return;
    }

    if (nodeToDelete->left == NULL || nodeToDelete->right == NULL) {
        node = nodeToDelete;
    } else {
        node = successor(nodeToDelete);
    }

    if (node->left != NULL) {
        child = node->left;
    } else {
        child = node->right;
    }

    if (child != NULL) {
        child->parent = node->parent;
    }

    if (node->parent == NULL) {
        *root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    if (node != nodeToDelete) {
        nodeToDelete->data = node->data;
    }

    if (node->color == BLACK) {
        deleteFixup(root, child, node->parent);
    }

    free(node);
}

// Inorder Traversal of the Red-Black Tree
void inorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// Print the Red-Black Tree (For visualization)
void printTree(Node* root, int level, int side) {
    if (root == NULL) {
        return;
    }

    printTree(root->right, level + 1, 1);

    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%c%d\n", (side == 1) ? 'R' : 'L', root->data);

    printTree(root->left, level + 1, 0);
}

// Free the memory used by the Red-Black Tree
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
