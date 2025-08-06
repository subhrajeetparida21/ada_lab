#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* left;
    struct node* right;
} s1;

s1* create_node(int value) {
    s1* newnode = (s1*)malloc(sizeof(s1));
    newnode->value = value;
    newnode->left = newnode->right = NULL;
    return newnode;
}

s1* insert(s1* root, int value) {
    if (root == NULL)
        return create_node(value);
    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
    return root;
}

void search(s1* root, int value) {
    if (root == NULL) {
        printf("Value not found!\n");
        return;
    }
    if (value == root->value)
        printf("Value %d found!\n", value);
    else if (value < root->value)
        search(root->left, value);
    else
        search(root->right, value);
}

int minimum(s1* root) {
    while (root->left != NULL)
        root = root->left;
    return root->value;
}

int maximum(s1* root) {
    while (root->right != NULL)
        root = root->right;
    return root->value;
}

int max_value(int a, int b) {
    return (a > b) ? a : b;
}

int height(s1* root) {
    if (root == NULL) return 0;
    return 1 + max_value(height(root->left), height(root->right));
}

int depth(s1* root, int value) {
    if (root == NULL) return -1;
    if (value == root->value) return 1;
    if (value < root->value) {
        int left_depth = depth(root->left, value);
        return (left_depth == -1) ? -1 : 1 + left_depth;
    } else {
        int right_depth = depth(root->right, value);
        return (right_depth == -1) ? -1 : 1 + right_depth;
    }
}

s1* minValueNode(s1* node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

s1* deleteNode(s1* root, int value) {
    if (root == NULL) return root;
    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else {
        if (root->left == NULL) {
            s1* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            s1* temp = root->left;
            free(root);
            return temp;
        }
        s1* temp = minValueNode(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

void inorder(s1* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d->", root->value);
        inorder(root->right);
    }
}

int main() {
    s1* root = NULL;
    int choice, value;
    while (1) {
        printf("\n1. Insert\n2. Search\n3. Minimum\n4. Maximum\n5. Height\n6. Depth\n7. Delete\n8. Display BST\n9. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                search(root, value);
                break;
            case 3:
                if (root) printf("Minimum: %d\n", minimum(root));
                else printf("Tree is empty\n");
                break;
            case 4:
                if (root) printf("Maximum: %d\n", maximum(root));
                else printf("Tree is empty\n");
                break;
            case 5:
                printf("Height: %d\n", height(root));
                break;
            case 6:
                printf("Enter value for depth: ");
                scanf("%d", &value);
                printf("Depth: %d\n", depth(root, value));
                break;
            case 7:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 8:
                inorder(root);
                printf("\n");
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
}
