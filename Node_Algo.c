#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

Node* createNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode -> data = data;
    newNode -> next = NULL;
    return newNode;
}

void createList(Node** head) {
    int data, choice;
    Node* temp = NULL;

    while (1) {
        printf("Insert data (insert -1 to stop): ");
        scanf("%d", &data);

        if (data == -1) break;

        Node* newNode = createNode(data);

        if (*head == NULL) {
            *head = newNode;
            temp = *head;
        } else {
            temp->next = newNode;
            temp = temp->next;
        }
    }

    printf("The list has been created.\n");
}

void deleteHead(Node** head){
    if(*head == NULL){
        printf("Empty list!!!\n");
        return;
    }
    Node* temp = *head;
    *head = (*head) -> next;
    free(temp);
    printf("Head deleted!!\n");
}

void deleteTail(Node** head){
    if(*head == NULL){
        printf("Empty list!!!!\n");
        return;
    }

    if((*head) -> next == NULL){
        free(*head);
        *head = NULL;
        printf("Tail deleted!!\n");
        return;
    }

    Node* temp = *head;
    while (temp -> next -> next != NULL)
    {
        temp = temp -> next;
    }

    free(temp -> next);
    temp -> next = NULL;
    printf("Tail deleted!!\n");
}

Node* findNode(Node* head, int value) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == value) {
            return current; // Tìm thấy node
        }
        current = current->next;
    }
    return NULL; // Không tìm thấy
}

void deleteNextNode(Node* prevNode){
    if(prevNode == NULL || prevNode -> next == NULL){
        printf("Unable to delete the next node!!\n");
        return;
    }

    Node* temp = prevNode -> next;
    prevNode -> next = temp -> next;
    free(temp);
    printf("Next node deleted!!\n");
}

void displayList(Node* head){
    if(head == NULL){
        printf("Empty list!!\n");
        return;
    }

    Node* temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp -> data);
        temp = temp ->next;
    }
    printf("NULL\n");
}

int main(){
    Node* head = NULL;
    printf("Create the initial list:\n");
    createList(&head);

    printf("Initial list:\n");
    displayList(head);

    // Xoá node đầu
    deleteHead(&head);
    printf("After delete the head:\n");
    displayList(head);

    // Xoá node cuối
    deleteTail(&head);
    printf("After delete the tail:\n");
    displayList(head);

    // Chức năng chọn node để xoá node phía sau
    int value;
    printf("Select the front node: ");
    scanf("%d", &value);

    Node* selectedNode = findNode(head, value);
    if (selectedNode != NULL) {
        deleteNextNode(selectedNode);
        printf("After delete the next node %d:\n", value);
        displayList(head);
    } else {
        printf("Unable to found %d in the list.\n", value);
    }
    return 0;
}
