#include <stdio.h>
#include <stdlib.h>

#define MAX 8 // Số đỉnh tối đa (ở đây là 8: a, b, c, d, e, g, h)

// Ma trận kề từ bài toán
int graph[MAX][MAX] = {
    {0, 1, 0, 1, 0, 1, 0, 1},
    {0, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 1, 0, 1},
    {0, 1, 1, 0, 1, 0, 1, 0},
    {1, 1, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0}
};

char vertices[MAX] = {'a', 'b', 'c', 'd', 'e', 'g', 'h'};

// Hàm đánh dấu và kiểm tra đỉnh đã được duyệt
int visited[MAX];

// Hàm duyệt BFS
void BFS(int start) {
    int queue[MAX];
    int front = 0, rear = 0;

    for (int i = 0; i < MAX; i++)
        visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    printf("BFS: ");

    while (front < rear) {
        int current = queue[front++];
        printf("%c ", vertices[current]);

        for (int i = 0; i < MAX; i++) {
            if (graph[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

// Hàm duyệt DFS
void DFSUtil(int vertex) {
    visited[vertex] = 1;
    printf("%c ", vertices[vertex]);

    for (int i = 0; i < MAX; i++) {
        if (graph[vertex][i] && !visited[i]) {
            DFSUtil(i);
        }
    }
}

void DFS(int start) {
    for (int i = 0; i < MAX; i++)
        visited[i] = 0;

    printf("DFS: ");
    DFSUtil(start);
    printf("\n");
}

int main() {
    int startVertex;
    printf("Nhap dinh bat dau (0-7): ");
    scanf("%d", &startVertex);

    if (startVertex < 0 || startVertex >= MAX) {
        printf("Dinh khong hop le!\n");
        return 1;
    }

    BFS(startVertex);
    DFS(startVertex);

    return 0;
}
