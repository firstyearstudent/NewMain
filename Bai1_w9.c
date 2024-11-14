#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 256
#define USB_SIZE 32 * 1024 * 1024 * 1024  // Kích thước USB 32GB

typedef struct FileNode {
    char filename[MAX_FILENAME_LENGTH];
    long size;
    long creationTime;
    struct FileNode* next;
} FileNode;

// Hàm sao chép chuỗi
void myStrCpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0' && i < MAX_FILENAME_LENGTH - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Hàm thêm file vào danh sách liên kết theo thứ tự thời gian
void addFile(FileNode** head, const char* filename, long size, long creationTime) {
    FileNode* newFile = (FileNode*)malloc(sizeof(FileNode));
    myStrCpy(newFile->filename, filename);
    newFile->size = size;
    newFile->creationTime = creationTime;
    newFile->next = NULL;

    if (*head == NULL || (*head)->creationTime > creationTime) {
        newFile->next = *head;
        *head = newFile;
    } else {
        FileNode* current = *head;
        while (current->next != NULL && current->next->creationTime < creationTime) {
            current = current->next;
        }
        newFile->next = current->next;
        current->next = newFile;
    }
}

// Hàm tính tổng kích thước các file
long calculateTotalSize(FileNode* head) {
    long totalSize = 0;
    while (head != NULL) {
        totalSize += head->size;
        head = head->next;
    }
    return totalSize;
}

// Hàm loại bỏ các file có kích thước nhỏ nhất để phù hợp với kích thước USB
void removeSmallestFiles(FileNode** head, long maxSize) {
    while (calculateTotalSize(*head) > maxSize) {
        FileNode* smallest = *head;
        FileNode* current = *head;
        FileNode* prev = NULL;
        FileNode* prevSmallest = NULL;

        while (current != NULL) {
            if (current->size < smallest->size) {
                smallest = current;
                prevSmallest = prev;
            }
            prev = current;
            current = current->next;
        }

        if (prevSmallest == NULL) {
            *head = smallest->next;
        } else {
            prevSmallest->next = smallest->next;
        }
        free(smallest);
    }
}

// Hàm in danh sách các file
void printFiles(FileNode* head) {
    while (head != NULL) {
        printf("File: %s, Size: %ld bytes, Creation Time: %ld\n", head->filename, head->size, head->creationTime);
        head = head->next;
    }
}

// Hàm nhập thông tin file từ người dùng
void inputFile(FileNode** head) {
    char filename[MAX_FILENAME_LENGTH];
    long size, creationTime;

    printf("Nhap ten file: ");
    scanf("%s", filename);
    
    printf("Nhap kich thuoc file (byte): ");
    scanf("%ld", &size);
    
    printf("Nhap thoi gian tao file: ");
    scanf("%ld", &creationTime);

    addFile(head, filename, size, creationTime);
}

// Hàm chính
int main() {
    FileNode* head = NULL;
    int choice;

    do {
        printf("\nChon thao tac:\n");
        printf("1. Them file vao danh sach\n");
        printf("2. Xem danh sach file\n");
        printf("3. Loai bo cac file nho nhat đe phu hop voi USB 32GB\n");
        printf("4. Exit\n");
        printf("Lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputFile(&head);
                break;
            case 2:
                printf("\nDanh sach file hien tai:\n");
                printFiles(head);
                break;
            case 3:
                removeSmallestFiles(&head, USB_SIZE);
                printf("\nDanh sach file sau khi loai bo cac file nho nhat:\n");
                printFiles(head);
                break;
            case 4:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    } while (choice != 4);

    // Giải phóng bộ nhớ
    while (head != NULL) {
        FileNode* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}