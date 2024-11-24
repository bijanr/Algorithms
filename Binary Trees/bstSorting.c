#include <stdio.h>
#include <stdlib.h>

// Define the structure of a BST node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function prototypes
Node* createNode(int data);
Node* insert(Node* root, int data);
Node* delete(Node* root, int data);
Node* findMin(Node* root);
void inOrder(Node* root);
void reverseInOrder(Node* root);
void menu();

// Main function
int main() {
    Node* root = NULL;
    int choice, value;

    while(1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = delete(root, value);
                break;
            case 3:
                printf("BST in ascending order: ");
                inOrder(root);
                printf("\n");
                break;
            case 4:
                printf("BST in descending order: ");
                reverseInOrder(root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to find the minimum value node in the BST
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the BST
Node* delete(Node* root, int data) {
    if (root == NULL) {
        printf("Value not found in the BST.\n");
        return root;
    }
    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

// Function to perform in-order traversal (ascending order)
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Function to perform reverse in-order traversal (descending order)
void reverseInOrder(Node* root) {
    if (root != NULL) {
        reverseInOrder(root->right);
        printf("%d ", root->data);
        reverseInOrder(root->left);
    }
}

// Function to display the menu
void menu() {
    printf("\nBinary Search Tree Operations:\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Display in Ascending Order\n");
    printf("4. Display in Descending Order\n");
    printf("5. Exit\n");
}
