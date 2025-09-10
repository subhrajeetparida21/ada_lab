#include <stdio.h>
#include <stdlib.h>

#define MIN_DEGREE 3   // Minimum degree (t)

// B-tree node
typedef struct BTreeNode {
    int keys[2 * MIN_DEGREE - 1];
    struct BTreeNode* children[2 * MIN_DEGREE];
    int n;
    int leaf;
} BTreeNode;

BTreeNode* createNode(int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2 * MIN_DEGREE; i++)
        node->children[i] = NULL;
    return node;
}

// Traverse in sorted order
void traverse(BTreeNode* root) {
    if (!root) return;
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->children[i]);
}

// Display B-tree structure with indentation
void displayBTree(BTreeNode* root, int level) {
    if (!root) return;

    printf("Level %d [", level);
    for (int i = 0; i < root->n; i++) {
        printf("%d", root->keys[i]);
        if (i < root->n - 1) printf(" ");
    }
    printf("]\n");

    for (int i = 0; i <= root->n; i++) {
        if (root->children[i] != NULL)
            displayBTree(root->children[i], level + 1);
    }
}

// Search a key
BTreeNode* search(BTreeNode* root, int k) {
    if (!root) return NULL;
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;
    if (i < root->n && root->keys[i] == k)
        return root;
    if (root->leaf)
        return NULL;
    return search(root->children[i], k);
}

// Split child
void splitChild(BTreeNode* x, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->leaf);
    z->n = MIN_DEGREE - 1;

    for (int j = 0; j < MIN_DEGREE - 1; j++)
        z->keys[j] = y->keys[j + MIN_DEGREE];

    if (!y->leaf) {
        for (int j = 0; j < MIN_DEGREE; j++)
            z->children[j] = y->children[j + MIN_DEGREE];
    }

    y->n = MIN_DEGREE - 1;

    for (int j = x->n; j >= i + 1; j--)
        x->children[j + 1] = x->children[j];
    x->children[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[MIN_DEGREE - 1];
    x->n++;
}

// Insert non-full
void insertNonFull(BTreeNode* x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    } else {
        while (i >= 0 && x->keys[i] > k)
            i--;
        i++;
        if (x->children[i]->n == 2 * MIN_DEGREE - 1) {
            splitChild(x, i, x->children[i]);
            if (k > x->keys[i])
                i++;
        }
        insertNonFull(x->children[i], k);
    }
}

// Insert key
BTreeNode* insert(BTreeNode* root, int k) {
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = k;
        root->n = 1;
        return root;
    }
    if (root->n == 2 * MIN_DEGREE - 1) {
        BTreeNode* s = createNode(0);
        s->children[0] = root;
        splitChild(s, 0, root);
        int i = 0;
        if (s->keys[0] < k)
            i++;
        insertNonFull(s->children[i], k);
        return s;
    } else {
        insertNonFull(root, k);
        return root;
    }
}

int main() {
    BTreeNode* root = NULL;
    int choice, key;

    while (1) {
        printf("\n---- B-Tree Operations ----\n");
        printf("1. Insert\n");
        printf("2. Traverse (sorted)\n");
        printf("3. Search\n");
        printf("4. Display Tree (levels)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
            break;
        case 2:
            printf("B-Tree Traversal: ");
            traverse(root);
            printf("\n");
            break;
        case 3:
            printf("Enter key to search: ");
            scanf("%d", &key);
            if (search(root, key))
                printf("Key %d found!\n", key);
            else
                printf("Key %d not found!\n", key);
            break;
        case 4:
            printf("B-Tree Structure:\n");
            displayBTree(root, 0);
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
}
