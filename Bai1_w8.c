#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cấu trúc lưu ngày tháng năm sinh
struct Ngay {
    int ngay;
    int thang;
    int nam;
};

// Cấu trúc lưu thông tin sinh viên
struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    struct Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

// Cấu trúc một nút trong danh sách liên kết đơn
struct Node {
    struct SinhVien data;
    struct Node* link;
};

// Cấu trúc danh sách liên kết đơn
struct List {
    struct Node* first;
    struct Node* last;
};

// Hàm khởi tạo danh sách
void khoiTaoDanhSach(struct List* list) {
    list->first = NULL;
    list->last = NULL;
}

// Hàm tạo một nút sinh viên mới
struct Node* taoNode(struct SinhVien sv) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = sv;
    node->link = NULL;
    return node;
}

// Hàm nhập thông tin sinh viên
struct SinhVien nhapSinhVien() {
    struct SinhVien sv;
    printf("Nhap ma SV: ");
    scanf("%s", sv.maSV);
    printf("Nhap ho ten: ");
    scanf(" %[^\n]", sv.hoTen);
    printf("Nhap gioi tinh (0: Nu, 1: Nam): ");
    scanf("%d", &sv.gioiTinh);
    printf("Nhap ngay sinh (dd mm yyyy): ");
    scanf("%d %d %d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);
    printf("Nhap dia chi: ");
    scanf(" %[^\n]", sv.diaChi);
    printf("Nhap lop: ");
    scanf("%s", sv.lop);
    printf("Nhap khoa: ");
    scanf("%s", sv.khoa);
    return sv;
}

// Hàm thêm sinh viên vào danh sách theo thứ tự mã sinh viên
void themSinhVien(struct List* list, struct SinhVien sv) {
    struct Node* node = taoNode(sv);

    if (list->first == NULL || strcmp(sv.maSV, list->first->data.maSV) < 0) {
        // Chèn vào đầu danh sách
        node->link = list->first;
        list->first = node;
        if (list->last == NULL) list->last = node;
    } else {
        // Tìm vị trí chèn vào giữa hoặc cuối danh sách
        struct Node* current = list->first;
        while (current->link != NULL && strcmp(current->link->data.maSV, sv.maSV) < 0) {
            current = current->link;
        }
        node->link = current->link;
        current->link = node;
        if (node->link == NULL) list->last = node;
    }
}

// Hàm in danh sách sinh viên
void inDanhSach(struct List list) {
    struct Node* current = list.first;
    while (current != NULL) {
        struct SinhVien sv = current->data;
        printf("\nMa SV: %s\n \nHo Ten: %s\n \nGioi Tinh: %d\n \nNgay Sinh: %02d/%02d/%04d\n \nDia Chi: %s\n \nLop: %s\n \nKhoa: %s\n",
               sv.maSV, sv.hoTen, sv.gioiTinh, sv.ngaySinh.ngay, sv.ngaySinh.thang, sv.ngaySinh.nam,
               sv.diaChi, sv.lop, sv.khoa);
        current = current->link;
    }
}

// Hàm tìm và in sinh viên có cùng ngày sinh
void timCungNgaySinh(struct List list) {
    struct Node* current = list.first;
    int found = 0;

    while (current != NULL) {
        struct Node* temp = current->link;
        while (temp != NULL) {
            if (current->data.ngaySinh.ngay == temp->data.ngaySinh.ngay &&
                current->data.ngaySinh.thang == temp->data.ngaySinh.thang &&
                current->data.ngaySinh.nam == temp->data.ngaySinh.nam) {
                if (!found) {
                    printf("Cac sinh vien co cung ngay sinh:\n");
                    found = 1;
                }
                printf("\nMa SV: %s\n \nHo Ten: %s\n \nNgay Sinh: %02d/%02d/%04d\n\n",
                       current->data.maSV, current->data.hoTen,
                       current->data.ngaySinh.ngay, current->data.ngaySinh.thang, current->data.ngaySinh.nam);
                printf("\nMa SV: %s\n \nHo Ten: %s\n \nNgay Sinh: %02d/%02d/%04d\n\n",
                       temp->data.maSV, temp->data.hoTen,
                       temp->data.ngaySinh.ngay, temp->data.ngaySinh.thang, temp->data.ngaySinh.nam);
            }
            temp = temp->link;
        }
        current = current->link;
    }

    if (!found) {
        printf("Khong tim thay sinh vien cung ngay sinh\n");
    }
}

// Hàm xóa sinh viên có cùng ngày sinh
void loaiBoCungNgaySinh(struct List* list) {
    struct Node* current = list->first;
    struct Node* prev = NULL;

    while (current != NULL) {
        struct Node* temp = current->link;
        int hasDuplicate = 0;

        while (temp != NULL) {
            if (current->data.ngaySinh.ngay == temp->data.ngaySinh.ngay &&
                current->data.ngaySinh.thang == temp->data.ngaySinh.thang &&
                current->data.ngaySinh.nam == temp->data.ngaySinh.nam) {
                hasDuplicate = 1;
                break;
            }
            temp = temp->link;
        }

        if (hasDuplicate) {
            struct Node* toDelete = current;
            if (prev == NULL) {
                list->first = current->link;
            } else {
                prev->link = current->link;
            }
            current = current->link;
            free(toDelete);
        } else {
            prev = current;
            current = current->link;
        }
    }
}

int main() {
    struct List list;
    khoiTaoDanhSach(&list);

    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        struct SinhVien sv = nhapSinhVien();
        themSinhVien(&list, sv);
    }

    printf("\nDanh sach sinh vien sau khi sap xep theo ma SV:\n");
    inDanhSach(list);

    printf("\nSinh vien co cung ngay sinh:\n");
    timCungNgaySinh(list);

    printf("\nDanh sach sau khi loai bo sinh vien co cung ngay sinh:\n");
    loaiBoCungNgaySinh(&list);
    inDanhSach(list);

    return 0;
}
