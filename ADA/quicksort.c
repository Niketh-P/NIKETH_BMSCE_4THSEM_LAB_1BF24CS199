#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Create new node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Insert at end
void insert(struct Node** head, int data) {
    struct Node* temp = newNode(data);
    if (*head == NULL) {
        *head = temp;
        return;
    }
    struct Node* last = *head;
    while (last->next != NULL)
        last = last->next;
    last->next = temp;
}

// Get tail
struct Node* getTail(struct Node* cur) {
    while (cur && cur->next)
        cur = cur->next;
    return cur;
}

// Partition
struct Node* partition(struct Node* head, struct Node* end,
                       struct Node** newHead, struct Node** newEnd) {

    struct Node* pivot = end;
    struct Node* prev = NULL;
    struct Node* cur = head;
    struct Node* tail = pivot;

    while (cur != pivot) {
        if (cur->data < pivot->data) {
            if (*newHead == NULL)
                *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;

            struct Node* temp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if (*newHead == NULL)
        *newHead = pivot;

    *newEnd = tail;
    return pivot;
}

// Recursive quicksort
struct Node* quickSortRecur(struct Node* head, struct Node* end) {
    if (!head || head == end)
        return head;

    struct Node* newHead = NULL;
    struct Node* newEnd = NULL;

    struct Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        struct Node* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;

        temp->next = NULL;

        newHead = quickSortRecur(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

// Main quicksort
void quickSort(struct Node** headRef) {
    *headRef = quickSortRecur(*headRef, getTail(*headRef));
}

// Print list
void printList(struct Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Seed random number generator
    srand(time(0));

    // Generate random elements (0–999)
    for (int i = 0; i < n; i++) {
        int randomValue = rand() % 10000;
        insert(&head, randomValue);
    }

    printf("Original List:\n");
    printList(head);

    // Start time
    clock_t start = clock();

    quickSort(&head);

    // End time
    clock_t end = clock();

    printf("Sorted List:\n");
    printList(head);

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
