#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 256
#define MAX_SIZE 32 * 1024

typedef struct File
{
    char NameFile[MAX_LENGTH];
    long size;
    long Date;
    struct File* link;
} File;

typedef struct FolderNode
{
    File* file;
    struct FolderNode* next;
} FolderNode;

// Hàm sao chép chuỗi 
void myStrCpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0' && i < MAX_LENGTH - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Hàm thêm file vào danh sách liên kết của folder theo thứ tự dung lượng
void addFile(FolderNode** head, const char* name, long size, long date) {
    File* newFile = (File*)malloc(sizeof(File));
    myStrCpy(newFile->NameFile, name);
    newFile->size = size;
    newFile->Date = date;
    newFile->link = NULL;

    FolderNode* newFolder = (FolderNode*)malloc(sizeof(FolderNode));
    newFolder->file = newFile;
    newFolder->next = NULL;

    // Chèn vào danh sách theo thứ tự dung lượng
    if (*head == NULL || (*head)->file->size > size) {
        newFolder->next = *head;
        *head = newFolder;
    } else {
        FolderNode* current = *head;
        while (current->next != NULL && current->next->file->size < size) {
            current = current->next;
        }
        newFolder->next = current->next;
        current->next = newFolder;
    }
}

// Hàm tính tổng kích thước các file trong folder
long calculateTotalSize(FolderNode* head) {
    long totalSize = 0;
    while (head != NULL) {
        totalSize += head->file->size;
        head = head->next;
    }
    return totalSize;
}

// Hàm loại bỏ file có kích thước nhỏ nhất và thời gian lâu nhất để phù hợp với kích thước USB
void removeOldestSmallestFile(FolderNode** head, long maxSize) {
    while (calculateTotalSize(*head) > maxSize) {
        FolderNode* smallest = *head;
        FolderNode* current = *head;
        FolderNode* prev = NULL;
        FolderNode* prevSmallest = NULL;

        // Tìm file có kích thước nhỏ nhất và ngày tạo lâu nhất
        while (current != NULL) {
            if (current->file->size < smallest->file->size || 
                (current->file->size == smallest->file->size && current->file->Date < smallest->file->Date)) {
                smallest = current;
                prevSmallest = prev;
            }
            prev = current;
            current = current->next;
        }

        // Xóa file được chọn (smallest)
        if (prevSmallest == NULL) {
            *head = smallest->next;
        } else {
            prevSmallest->next = smallest->next;
        }
        free(smallest->file);
        free(smallest);
    }
}


// Hàm in danh sách các file trong folder
void printFiles(FolderNode* head) {
    while (head != NULL) {
        printf("File: %s, Size: %ld MB, Date: %ld\n", head->file->NameFile, head->file->size, head->file->Date);
        head = head->next;
    }
}

// Hàm nhập thông tin file từ người dùng
void inputFile(FolderNode** head) {
    char name[MAX_LENGTH];
    long size, date;

    printf("Nhap ten file: ");
    scanf("%s", name);
    
    printf("Nhap kich thuoc file(MB): ");
    scanf("%ld", &size);
    
    printf("Nhap ngay tao file: ");
    scanf("%ld", &date);

    addFile(head, name, size, date);
}

// Hàm chính
int main() {
    FolderNode* head = NULL;
    int choice;

    do {
        printf("\nChon thao tac:\n");
        printf("1. Them file vao danh sach\n");
        printf("2. Xem danh sach file\n");
        printf("3. Loai bo cac file neu vuot qua 32GB\n");
        printf("4. Exit\n");
        printf("Lua chon cua ban: ");
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
                removeOldestSmallestFile(&head, MAX_SIZE);
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
        FolderNode* temp = head;
        head = head->next;
        free(temp->file);
        free(temp);
    }

    return 0;
}
