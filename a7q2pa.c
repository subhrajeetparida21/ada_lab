#include <stdio.h>
#include <stdlib.h>

#define MIN_DEGREE 3   // minimum degree (t) of B-tree

// B-tree node structure
typedef struct BTreeNode {
    int keys[2 * MIN_DEGREE - 1];         // keys
    struct BTreeNode* children[2 * MIN_DEGREE]; // child pointers
    int n;                                // number of keys
    int leaf;                             // is true when node is leaf
} BTreeNode;

BTreeNode* createNode(int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2 * MIN_DEGREE; i++)
        node->children[i] = NULL;
    return node;
}

// Traverse the B-tree
void traverse(BTreeNode* root) {
    if (root == NULL) return;
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->children[i]);
}

// Search a key in the B-tree
BTreeNode* search(BTreeNode* root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;
    if (i < root->n && root->keys[i] == k)
        return root;
    if (root->leaf)
        return NULL;
    return search(root->children[i], k);
}

// Split the child y of node x at index i
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

// Insert a key in a non-full node
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

// Insert a key in B-tree
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

// Deletion helper functions
int getPred(BTreeNode* x) {
    BTreeNode* cur = x;
    while (!cur->leaf)
        cur = cur->children[cur->n];
    return cur->keys[cur->n - 1];
}

int getSucc(BTreeNode* x) {
    BTreeNode* cur = x;
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

void merge(BTreeNode* x, int idx) {
    BTreeNode* child = x->children[idx];
    BTreeNode* sibling = x->children[idx + 1];
    child->keys[MIN_DEGREE - 1] = x->keys[idx];

    for (int i = 0; i < sibling->n; i++)
        child->keys[i + MIN_DEGREE] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++)
            child->children[i + MIN_DEGREE] = sibling->children[i];
    }

    for (int i = idx + 1; i < x->n; i++)
        x->keys[i - 1] = x->keys[i];
    for (int i = idx + 2; i <= x->n; i++)
        x->children[i - 1] = x->children[i];

    child->n += sibling->n + 1;
    x->n--;
    free(sibling);
}

void fill(BTreeNode* x, int idx);

void removeFromLeaf(BTreeNode* x, int idx) {
    for (int i = idx + 1; i < x->n; i++)
        x->keys[i - 1] = x->keys[i];
    x->n--;
}

void removeFromNonLeaf(BTreeNode* x, int idx) {
    int k = x->keys[idx];
    if (x->children[idx]->n >= MIN_DEGREE) {
        int pred = getPred(x->children[idx]);
        x->keys[idx] = pred;
        // recursive delete
        BTreeNode* child = x->children[idx];
        int i;
        for (i = 0; i < child->n && child->keys[i] != pred; i++);
        if (i < child->n)
            removeFromLeaf(child, i);
    } else if (x->children[idx + 1]->n >= MIN_DEGREE) {
        int succ = getSucc(x->children[idx + 1]);
        x->keys[idx] = succ;
        BTreeNode* child = x->children[idx + 1];
        int i;
        for (i = 0; i < child->n && child->keys[i] != succ; i++);
        if (i < child->n)
            removeFromLeaf(child, i);
    } else {
        merge(x, idx);
        BTreeNode* child = x->children[idx];
        int i;
        for (i = 0; i < child->n && child->keys[i] != k; i++);
        if (i < child->n)
            removeFromLeaf(child, i);
    }
}

void removeNode(BTreeNode* root, int k) {
    if (!root) return;
    int idx = 0;
    while (idx < root->n && root->keys[idx] < k)
        idx++;

    if (idx < root->n && root->keys[idx] == k) {
        if (root->leaf)
            removeFromLeaf(root, idx);
        else
            removeFromNonLeaf(root, idx);
    } else {
        if (root->leaf) {
            printf("Key %d not found in tree\n", k);
            return;
        }
        removeNode(root->children[idx], k);
    }
}

// Main driver with menu
int main() {
    BTreeNode* root = NULL;
    int choice, key;

    while (1) {
        printf("\n---- B-Tree Operations ----\n");
        printf("1. Insert\n");
        printf("2. Traverse\n");
        printf("3. Search\n");
        printf("4. Delete\n");
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
            printf("Enter key to delete: ");
            scanf("%d", &key);
            removeNode(root, key);
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
}
