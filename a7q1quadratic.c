#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define EMPTY -1

int hashTable[SIZE];
int collisions = 0;

int hashFunction(int key) {
    return key % SIZE;
}

void insert(int key) {
    int index = hashFunction(key);
    int startIndex = index;

    printf("Inserting %d -> Hash index: %d\n", key, index);

    if (hashTable[index] == EMPTY) {
        hashTable[index] = key;
        printf("Key %d placed at index %d\n\n", key, index);
        return;
    }

    int i = 1;
    while (i < SIZE) {
        collisions++;
        int newIndex = (startIndex + i * i) % SIZE;
        printf("Collision at index %d for key %d, trying index %d\n", index, key, newIndex);

        if (hashTable[newIndex] == EMPTY) {
            hashTable[newIndex] = key;
            printf("Key %d placed at index %d\n\n", key, newIndex);
            return;
        }
        i++;
    }

    printf("Hash table is full, cannot insert %d\n\n", key);
}

void display() {
    printf("\nFinal Hash Table:\n");
    for (int i = 0; i < SIZE; i++) {
        if (hashTable[i] == EMPTY)
            printf("[%d] : EMPTY\n", i);
        else
            printf("[%d] : %d\n", i, hashTable[i]);
    }
    printf("\nTotal Collisions = %d\n", collisions);
}

int main() {
    for (int i = 0; i < SIZE; i++)
        hashTable[i] = EMPTY;

    int n, key;
    printf("Enter number of keys to insert: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter key %d: ", i + 1);
        scanf("%d", &key);
        insert(key);
    }

    display();
    return 0;
}
