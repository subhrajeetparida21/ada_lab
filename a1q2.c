#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* addNode(struct Node* head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) return newNode;

    struct Node* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

struct Node* merge(struct Node* a, struct Node* b) {
    struct Node* result = NULL;
    if (!a) return b;
    if (!b) return a;

    if (a->data <= b->data) {
        result = a;
        result->next = merge(a->next, b);
    } else {
        result = b;
        result->next = merge(a, b->next);
    }
    return result;
}

void split(struct Node* source, struct Node** front, struct Node** back) {
    struct Node* slow = source;
    struct Node* fast = source->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

struct Node* mergeSort(struct Node* head) {
    if (!head || !head->next) return head;

    struct Node* a;
    struct Node* b;
    split(head, &a, &b);

    a = mergeSort(a);
    b = mergeSort(b);

    return merge(a, b);
}

void printList(struct Node* head) {
    while (head) {
        printf("%d", head->data);
        if (head->next) printf(" -> ");
        head = head->next;
    }
    printf(" -> NULL\n");
}

int main() {
    struct Node* head = NULL;
    int n, value;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements :\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        head = addNode(head, value);
    }

    printf("Unsorted: ");
    printList(head);

    head = mergeSort(head);

    printf("Sorted: ");
    printList(head);

    return 0;
}
