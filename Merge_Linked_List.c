#include <stdio.h>
#include <stdlib.h>

// Define the structure for a singly linked list node
typedef struct SinglyLinkedListNode {
    int data;
    struct SinglyLinkedListNode* next;
} SinglyLinkedListNode;

// Function to create a new node
SinglyLinkedListNode* createNode(int data) {
    SinglyLinkedListNode* newNode = (SinglyLinkedListNode*)malloc(sizeof(SinglyLinkedListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to merge two sorted linked lists
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* headA, SinglyLinkedListNode* headB) {
    // Dummy node to simplify merging process
    SinglyLinkedListNode dummy;
    SinglyLinkedListNode* tail = &dummy;
    dummy.next = NULL;

    // Traverse both lists and merge
    while (headA && headB) {
        if (headA->data <= headB->data) {
            tail->next = headA;
            headA = headA->next;
        } else {
            tail->next = headB;
            headB = headB->next;
        }
        tail = tail->next;
    }

    // Attach the remaining nodes
    tail->next = headA ? headA : headB;

    return dummy.next;
}

// Function to create a linked list from an array
SinglyLinkedListNode* createLinkedList(int arr[], int n) {
    if (n == 0) return NULL;
    SinglyLinkedListNode* head = createNode(arr[0]);
    SinglyLinkedListNode* current = head;
    for (int i = 1; i < n; i++) {
        current->next = createNode(arr[i]);
        current = current->next;
    }
    return head;
}

// Function to print a linked list
void printLinkedList(SinglyLinkedListNode* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    int t, n, m;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        int arr1[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr1[i]);
        }

        scanf("%d", &m);
        int arr2[m];
        for (int i = 0; i < m; i++) {
            scanf("%d", &arr2[i]);
        }

        SinglyLinkedListNode* headA = createLinkedList(arr1, n);
        SinglyLinkedListNode* headB = createLinkedList(arr2, m);

        SinglyLinkedListNode* mergedHead = mergeLists(headA, headB);
        printLinkedList(mergedHead);
    }

    return 0;
}