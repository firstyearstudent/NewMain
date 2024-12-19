#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa cấu trúc của một node trong cây
typedef struct Node {
    char title[100];
    int pages;
    struct Node *firstChild;
    struct Node *nextSibling;
} Node;

// Tạo một node mới
Node *createNode(const char *title, int pages) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strncpy(newNode->title, title, sizeof(newNode->title) - 1);
    newNode->title[sizeof(newNode->title) - 1] = '\0';
    newNode->pages = pages;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Thêm một node con vào node cha
void addChild(Node *parent, Node *child) {
    if (!parent->firstChild) {
        parent->firstChild = child;
    } else {
        Node *temp = parent->firstChild;
        while (temp->nextSibling) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

// Đếm số chương
int countChapters(Node *root) {
    int count = 0;
    Node *temp = root->firstChild;
    while (temp) {
        count++;
        temp = temp->nextSibling;
    }
    return count;
}

// Tìm chương dài nhất
Node *findLongestChapter(Node *root) {
    Node *longest = NULL;
    int maxPages = 0;
    Node *temp = root->firstChild;
    while (temp) {
        if (temp->pages > maxPages) {
            maxPages = temp->pages;
            longest = temp;
        }
        temp = temp->nextSibling;
    }
    return longest;
}

// Giải phóng cây
void freeTree(Node *root) {
    if (!root) return;

    freeTree(root->firstChild);
    freeTree(root->nextSibling);
    free(root);
}

// In cây
void printTree(Node *root, int level) {
    for (int i = 0; i < level; i++) printf("  ");
    printf("- %s (%d pages)\n", root->title, root->pages);

    for (Node *child = root->firstChild; child; child = child->nextSibling) {
        printTree(child, level + 1);
    }
}

// Nhập thông tin một nút
Node *inputNode() {
    char title[100];
    int pages;

    printf("Enter title: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    printf("Enter number of pages: ");
    scanf("%d", &pages);
    getchar();

    return createNode(title, pages);
}

// Thêm nút từ người dùng
void addNodeFromInput(Node *root) {
    char parentTitle[100];
    printf("Enter parent title: ");
    fgets(parentTitle, sizeof(parentTitle), stdin);
    parentTitle[strcspn(parentTitle, "\n")] = '\0';

    Node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Node *current = queue[front++];
        if (strcmp(current->title, parentTitle) == 0) {
            Node *newNode = inputNode();
            addChild(current, newNode);
            printf("Node added successfully!\n");
            return;
        }
        for (Node *child = current->firstChild; child; child = child->nextSibling) {
            queue[rear++] = child;
        }
    }

    printf("Parent node not found!\n");
}

int main() {
    printf("Create the root of the book:\n");
    Node *root = inputNode();

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Add a new node\n");
        printf("2. Print the table of contents\n");
        printf("3. Count chapters\n");
        printf("4. Find the longest chapter\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addNodeFromInput(root);
                break;
            case 2:
                printf("\nTable of Contents:\n");
                printTree(root, 0);
                break;
            case 3:
                printf("\nNumber of chapters: %d\n", countChapters(root));
                break;
            case 4: {
                Node *longest = findLongestChapter(root);
                if (longest) {
                    printf("\nLongest chapter: %s (%d pages)\n", longest->title, longest->pages);
                } else {
                    printf("\nNo chapters found.\n");
                }
                break;
            }
            case 0:
                freeTree(root);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
