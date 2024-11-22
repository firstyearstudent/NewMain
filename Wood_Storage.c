#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CAPACITY 100

typedef struct Wood
{
    char type[MAX_CAPACITY];
    float length;
    int age;
} Wood;

// Node trong stack
typedef struct Node {
    Wood wood;
    struct Node* next;
} Node;

// Stack lưu danh sách Node
typedef struct Stack {
    Node* top; 
} Stack;

// Khởi tạo stack
void StackBegin(Stack* stack) {
    stack->top = NULL;
}

// Kiểm tra stack rỗng
int EmptyChecking(Stack* stack) {
    return stack->top == NULL;
}

// Thêm phần tử vào stack
void Add(Stack* stack, Wood wood) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("ERROR!!!!\n");
        return;
    }
    newNode->wood = wood;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Loại bỏ phần tử khỏi stack
Wood pop(Stack* stack) {
    if (EmptyChecking(stack)) {
        printf("Stack empty!!\n");
        exit(1); // Thoát nếu stack rỗng
    }
    Node* temp = stack->top;
    Wood wood = temp->wood;
    stack->top = temp->next;
    free(temp);
    return wood;
}

// Thêm phần tử vào đáy stack
void AddToPosition(Stack* stack, Wood wood, int position) {
    if(position < 0){
        printf("Invalid position!!\n");
        return;
    }

    if (position == 0 || EmptyChecking(stack)) {
        Add(stack, wood); // Nếu stack rỗng, chèn phần tử vào
        return;
    }
    // Lấy phần tử trên đỉnh stack
    Wood topWood = pop(stack);
    // Gọi đệ quy để thêm phần tử vào đáy
    AddToPosition(stack, wood, position);
    // Đưa phần tử trên đỉnh stack trở lại
    Add(stack, topWood);
}

// Hiển thị danh sách gỗ trong kho
void displayStack(Stack* stack) {
    if (EmptyChecking(stack)) {
        printf("Storage is empty!!\n");
        return;
    }
    printf("List of wood blocks: \n");
    Node* current = stack->top;
    while (current != NULL) {
        printf("- Type: %s\n  Length: %.2f m\n  Age: %d years\n",
               current->wood.type, current->wood.length, current->wood.age);
        current = current->next;
    }
}

// Chương trình chính
int main() {
    Stack stack;
    StackBegin(&stack);

    int choice;
    do {
        printf("\nWood storage management\n");
        printf("1. Add new wood block\n");
        printf("2. Display list of wood block\n");
        printf("3. Add a new wood block to the bottom\n");
        printf("4. Exit\n");
        printf("Your selection: ");
        scanf("%d", &choice);
        getchar(); // Xóa ký tự '\n' còn lại trong bộ đệm sau khi nhập số
        
        switch (choice) {
            case 1: {
                Wood wood;
                printf("Enter wood type: ");
                fgets(wood.type, 50, stdin);
                wood.type[strcspn(wood.type, "\n")] = '\0'; // Loại bỏ '\n'
                printf("Enter length (m): ");
                scanf("%f", &wood.length);
                printf("Enter age: ");
                scanf("%d", &wood.age);
                getchar(); // Xóa bộ đệm sau khi nhập số

                Add(&stack, wood);
                printf("New wood block was added to the storage!\n");
                break;
            }
            case 2:
                displayStack(&stack);
                break;
            case 3: {
                Wood wood;
                int position;

                printf("Enter wood type: ");
                fgets(wood.type, 50, stdin);
                wood.type[strcspn(wood.type, "\n")] = '\0'; // Loại bỏ '\n'
                printf("Enter length (m): ");
                scanf("%f", &wood.length);
                printf("Enter age: ");
                scanf("%d", &wood.age);
                getchar(); // Xóa bộ đệm sau khi nhập số

                printf("Select position: \n");
                scanf("%d", &position);
                getchar();

                AddToPosition(&stack, wood, position);
                printf("New wood block was added to the bottom of the storage!\n");
                break;
            }
            case 4:
                printf("Exiting program!\n");
                break;
            default:
                printf("Invalid selection!!\n");
                break;
        }
    } while (choice != 4);

    return 0;
}