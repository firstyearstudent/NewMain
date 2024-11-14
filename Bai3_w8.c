#include <stdio.h>
#include <stdlib.h>

// Cấu trúc của người chơi trong vòng tròn
struct Node {
    int position;
    struct Node* next;
};

// Hàm tạo danh sách vòng tròn với N người chơi
struct Node* taoVongTron(int N) {
    struct Node* head = NULL;
    struct Node* temp = NULL;
    struct Node* tail = NULL;

    for (int i = 1; i <= N; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->position = i;
        newNode->next = head;

        if (head == NULL) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }
    tail->next = head; // Liên kết cuối về đầu tạo vòng tròn
    return head;
}

// Hàm giải quyết bài toán Josephus
int josephus(struct Node* head, int M) {
    struct Node* current = head;
    struct Node* prev = NULL;

    if (M == 0) {  // Trường hợp đặc biệt khi M = 0
        while (current->next != current) {
            printf("Loai bo nguoi choi thu: %d\n", current->position);
            prev = current;
            current = current->next;
            prev->next = current;
            free(prev);
        }
        int winner = current->position;
        free(current);
        return winner;
    }

    if (M == 1) { // Trường hợp đặc biệt khi M = 1
        while (current->next != current) {
            printf("Loai bo nguoi choi thu: %d\n", current->next->position);
            struct Node* temp = current->next;
            current->next = temp->next;
            free(temp);
            current = current->next;
        }
        int winner = current->position;
        free(current);
        return winner;
    }

    // Trường hợp M > 1
    while (current->next != current) {
        for (int i = 1; i < M; i++) {
            prev = current;
            current = current->next;
        }
        printf("Loai bo nguoi choi thu: %d\n", current->position);
        prev->next = current->next;
        free(current);
        current = prev->next;
    }
    int winner = current->position;
    free(current);
    return winner;
}

int main() {
    int N, M;
    printf("Nhap so luong nguoi choi N: ");
    scanf("%d", &N);
    printf("Nhap gia tri M (so nguoi bi loai bo moi luot): ");
    scanf("%d", &M);

    struct Node* head = taoVongTron(N);
    int winner = josephus(head, M);
    printf("Nguoi chien thang cuoi cung la nguoi thu: %d\n", winner);

    return 0;
}
