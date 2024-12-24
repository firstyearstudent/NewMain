#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc node của cây AVL
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// Hàm trả về chiều cao của một node
int height(Node *N) {
    return (N == NULL) ? 0 : N->height;
}

// Hàm trả về giá trị lớn hơn
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Tạo một node mới
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Hàm xoay phải
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Hàm xoay trái
Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Lấy hệ số cân bằng
int getBalance(Node *N) {
    return (N == NULL) ? 0 : height(N->left) - height(N->right);
}

// Thêm một node mới vào cây AVL
Node* insert(Node* node, int key) {
    // Bước 1: Thêm node bình thường
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Các khóa trùng nhau không được phép
        return node;

    // Bước 2: Cập nhật chiều cao của node hiện tại
    node->height = 1 + max(height(node->left), height(node->right));

    // Bước 3: Lấy hệ số cân bằng
    int balance = getBalance(node);

    // Nếu mất cân bằng, có 4 trường hợp

    // Trường hợp trái-trái
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Trường hợp phải-phải
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Trường hợp trái-phải
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Trường hợp phải-trái
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Hàm in cây theo phép duyệt LNR (In-order)
void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Chương trình kiểm thử
int main() {
    Node *root = NULL;

    // Mảng kiểm tra đầu vào
    int keys[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i]);
        printf("Cay AVL sau khi them %d: ", keys[i]);
        inOrder(root);
        printf("\n");
    }

    return 0;
}
