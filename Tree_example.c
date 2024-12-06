#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;             // Gia tri cua nut (toan tu hoac toan hang)
    struct Node *left;     // Con trai
    struct Node *right;    // Con phai
} Node;

// Tao mot nut moi
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Dung cay bieu thuc tu bieu thuc tien to
Node* buildExpressionTree(const char* expr, int* index) {
    if (expr[*index] == '\0') return NULL;  // Ket thuc bieu thuc

    // Lay ky tu hien tai
    char current = expr[*index];
    (*index)++;

    // Tao nut moi
    Node* node = createNode(current);

    // Neu la toan tu, xu ly con trai va con phai
    if (current == '+' || current == '-' || current == '*' || current == '/' || current == '^') {
        node->left = buildExpressionTree(expr, index);
        node->right = buildExpressionTree(expr, index);
    }

    // Tra ve nut da tao
    return node;
}

// Duyet cay theo thu tu tien to
void preorder(Node* root) {
    if (root == NULL) return;
    printf("%c", root->data);  // In gia tri nut
    preorder(root->left);      // Duyet cay con trai
    preorder(root->right);     // Duyet cay con phai
}

// Duyet cay theo thu tu trung to
void inorder(Node* root) {
    if (root == NULL) return;

    // Neu nut hien tai la toan tu, bao boi dau ngoac
    if (root->left != NULL || root->right != NULL) printf("(");

    inorder(root->left);       // Duyet cay con trai
    printf("%c", root->data);  // In gia tri nut
    inorder(root->right);      // Duyet cay con phai

    if (root->left != NULL || root->right != NULL) printf(")");
}

// Duyet cay theo thu tu hau to
void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);     // Duyet cay con trai
    postorder(root->right);    // Duyet cay con phai
    printf("%c", root->data);  // In gia tri nut
}

// Giai phong bo nho cay
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char prefixExpr[100];
    printf("Nhap bieu thuc tien to: ");
    scanf("%s", prefixExpr);

    // Dung cay bieu thuc
    int index = 0;
    Node* root = buildExpressionTree(prefixExpr, &index);

    // In bieu thuc theo cac thu tu duyet
    printf("Duyet theo thu tu tien to: ");
    preorder(root);
    printf("\n");

    printf("Duyet theo thu tu trung to: ");
    inorder(root);
    printf("\n");

    printf("Duyet theo thu tu hau to: ");
    postorder(root);
    printf("\n");

    // Giai phong bo nho
    freeTree(root);

    return 0;
}
