#include <stdio.h>
#include <stdlib.h>
//Cấu trúc của hạng tử
struct Node {
    int bac; //Bậc của hạng tử
    int heSo; //Hệ số của hạng tử
    struct Node* next; //Con trỏ trỏ đến hạng tử tiếp theo
};
//Hàm tạo hạng tử
struct Node* taoDaThuc(int heSo, int bac){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // Cấp phát bộ nhớ cho node mới
    newNode -> heSo = heSo; //Gán hệ số cho hạng tử
    newNode -> bac = bac; //Gán bậc cho hạng tử
    newNode -> next = NULL; //Khởi tạo con trỏ next là NULL vì đây là hạng tử mới
    return newNode; //Trả về con trỏ trỏ đến hạng tử mới
}
//Hàm chèn đa thức
void chenDaThuc(struct Node** head, int heSo, int bac){
    struct Node* newNode = taoDaThuc(heSo, bac); 
    
    if (*head == NULL || (*head) -> bac < bac) {
        newNode -> next = *head;
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current -> next != NULL && current -> next -> bac > bac) {
            current = current->next;
        }
        newNode -> next = current -> next;
        current -> next = newNode;
    }
}
//Hàm cho phép nhập đa thức
void nhapDaThuc(struct Node** head){
    int bac;
    int heSo;
    int n;
    printf("Nhap so hang tu trong da thuc: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        printf("Nhap he so va bac cua hang tu %d: ", i+1);
        scanf("%d %d", &heSo, &bac);

        if(heSo == 0){
            continue;
        }
        
        chenDaThuc(head, heSo, bac);
    }
}
// Hàm cộng hai đa thức
struct Node* congDaThuc(struct Node* f, struct Node* g) {
    struct Node* h = NULL;
    struct Node* p1 = f;
    struct Node* p2 = g;

    // Duyệt qua từng hạng tử của f và g để cộng lại
    while (p1 != NULL || p2 != NULL) {
        if (p1 != NULL && (p2 == NULL || p1->bac > p2->bac)) {
            chenDaThuc(&h, p1->heSo, p1->bac);
            p1 = p1->next;
        } else if (p2 != NULL && (p1 == NULL || p2->bac > p1->bac)) {
            chenDaThuc(&h, p2->heSo, p2->bac);
            p2 = p2->next;
        } else {
            int sumHeSo = p1->heSo + p2->heSo;
            if (sumHeSo != 0) {
                chenDaThuc(&h, sumHeSo, p1->bac);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    return h;
}
//Hàm in kết quả
void inDaThuc(struct Node* head){
    struct Node* current = head;
    while(current != NULL){
        if(current -> heSo > 0 && current != head) printf(" + ");
        printf("%dx^%d", current -> heSo, current -> bac);
        current = current -> next;
    }
    printf("\n");
}
//Hàm giải phóng bộ nhớ
void giaiphongDaThuc(struct Node* head){
    struct Node* temp;
    while(head != NULL){
        temp = head;
        head = head -> next;
        free(temp);
    }
}

int main(){
    struct Node* f = NULL; // Đa thức f(x)
    struct Node* g = NULL; // Đa thức g(x)

    printf("Nhap da thuc f(x)\n");
    nhapDaThuc(&f);

    printf("Nhap da thuc g(x)\n");
    nhapDaThuc(&g);

    printf("Da thuc f(x) = ");
    inDaThuc(f);

    printf("Da thuc g(x) = ");
    inDaThuc(g);

    // Tính tổng h(x) = f(x) + g(x)
    struct Node* h = congDaThuc(f, g);
    printf("Tong hai da thuc h(x) = f(x) + g(x) = ");
    inDaThuc(h);

    // Giải phóng bộ nhớ
    giaiphongDaThuc(f);
    giaiphongDaThuc(g);
    giaiphongDaThuc(h);

    return 0;
}