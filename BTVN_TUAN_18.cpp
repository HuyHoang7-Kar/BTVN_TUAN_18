#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 12

// Ma trận kề và danh sách kề
int adjMatrix[MAX][MAX] = {0};
// Thêm cạnh vào ma trận kề
void addEdgeMatrix(int u, int v) {
    adjMatrix[u][v] = v;
    adjMatrix[v][u] = v;
}
struct Node {
    int data;
    struct Node* next;
};
struct Node* adjList[MAX];
// Thêm cạnh vào danh sách kề
void addEdgeList(int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = u;
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

// Hàng đợi cho BFS
typedef struct Queue {
    int items[MAX];
    int front;
    int rear;
} Queue;

Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue( Queue* q, int value) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue( Queue* q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    if (q->front >= q->rear) q->front = q->rear = -1;
    else q->front++;
    return item;
}

// Ngăn xếp cho DFS
typedef struct Stack {
    int items[MAX];
    int top;
} Stack;

Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

bool isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

void push( Stack* stack, int value) {
    if (stack->top == MAX - 1) return;
    stack->items[++stack->top] = value;
}

int pop( Stack* stack) {
    if (isStackEmpty(stack)) return -1;
    return stack->items[stack->top--];
}

// In ma trận kề
void printAdjMatrix() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// In danh sách kề
void printAdjList() {
    for (int i = 0; i < MAX; i++) {
        printf("%d: ", i);
        struct Node* temp = adjList[i];
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Duyệt đồ thị theo BFS
void bfs(int start) {
    bool visited[MAX] = {false};
    struct Queue* q = createQueue();

    visited[start] = true;
    enqueue(q, start);

    printf("Duyet BFS: ");
    while (!isEmpty(q)) {
        int current = dequeue(q);
        printf("%d ", current);

        struct Node* temp = adjList[current];
        while (temp) {
            if (!visited[temp->data]) {
                visited[temp->data] = true;
                enqueue(q, temp->data);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Duyệt đồ thị theo DFS
void dfs(int start) {
    bool visited[MAX] = {false};
    struct Stack* stack = createStack();

    push(stack, start);

    printf("Duyet DFS: ");
    while (!isStackEmpty(stack)) {
        int current = pop(stack);

        if (!visited[current]) {
            printf("%d ", current);
            visited[current] = true;
        }

        struct Node* temp = adjList[current];
        while (temp) {
            if (!visited[temp->data]) {
                push(stack, temp->data);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}
// 0: Hà Nội
// 1: Bắc Giang
// 2: Bắc Ninh
// 3: Hải Dương
// 4: Hải Phòng
// 5: Uông Bí
// 6: Sơn Tây
// 7: Hòa Bình
// 8: Phủ Lý
// 9: Thái Nguyên
// 10: Hưng Yên
int main() {
    // Khởi tạo danh sách kề
    for (int i = 0; i < MAX; i++) {
        adjList[i] = NULL;
    }

    // Thêm các cạnh (thay bằng các cạnh thực tế từ đồ thị)
    int edges[][2] = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 6}, {0, 7}, {3, 4},
        {4, 5}, {5, 8}, {8, 9}, {9, 10}, {5, 10}
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);

    for (int i = 0; i < numEdges; i++) {
        addEdgeMatrix(edges[i][0], edges[i][1]);
        addEdgeList(edges[i][0], edges[i][1]);
    }

    // In ma trận kề
    printf("Ma tran ke:\n");
    printAdjMatrix();

    // In danh sách kề
    printf("\nDanh sach ke:\n");
    printAdjList();

    // Thực hiện duyệt BFS và DFS
    int startVertex = 0;
    bfs(startVertex);
    dfs(startVertex);

    return 0;
}
