#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cấu trúc lưu trữ thông tin thanh gỗ
typedef struct WoodBlock {
    char type[50];
    float length;
    int age;
} WoodBlock;

// Node trong stack
typedef struct Node {
    WoodBlock wood;
    struct Node* next;
} Node;

// Stack lưu danh sách Node
typedef struct Stack {
    Node* top; // Thiếu dấu ; đã sửa
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
void Add(Stack* stack, WoodBlock wood) {
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
WoodBlock pop(Stack* stack) {
    if (EmptyChecking(stack)) {
        printf("Stack empty!!\n");
        exit(1); // Thoát nếu stack rỗng
    }
    Node* temp = stack->top;
    WoodBlock wood = temp->wood;
    stack->top = temp->next;
    free(temp);
    return wood;
}

// Lấy phần tử trên đỉnh stack
WoodBlock peak(Stack* stack) {
    if (EmptyChecking(stack)) {
        printf("Stack empty!!!!\n");
        exit(1); // Thoát nếu stack rỗng
    }
    return stack->top->wood;
}

// Đếm số lượng gỗ có cùng tuổi
int CountingWoodBlock(Stack* stack, int age) {
    int count = 0;
    Node* current = stack->top;
    while (current != NULL) {
        if (current->wood.age == age) {
            count++;
        }
        current = current->next;
    }
    return count;
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
        printf("3. Count the number of wood blocks with the same age\n");
        printf("4. Exit\n");
        printf("Your selection: ");
        scanf("%d", &choice);
        getchar(); // Xóa ký tự '\n' còn lại trong bộ đệm sau khi nhập số
        
        switch (choice) {
            case 1: {
                WoodBlock wood;
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
                int age;
                printf("Enter the age to count: ");
                scanf("%d", &age);
                int count = CountingWoodBlock(&stack, age);
                printf("The number of wood blocks with age %d is: %d\n", age, count);
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
