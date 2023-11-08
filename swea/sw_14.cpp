#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void bfs_init(int N, int map[10][10]);
extern int bfs(int x1, int y1, int x2, int y2);

static int test_bfs() {
    int N;
    int map[10][10];
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &map[i][j]);
        }
    }
    bfs_init(N, map);
    int M;
    int score = 100;
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        int result = bfs(x1, y1, x2, y2);
        int dist;
        scanf("%d", &dist);
        if (result != dist) score = 0;
    }
    return score;
}

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);
    printf("#total score : %d\n", test_bfs());

    return 0;
}

int mapsize = 0;
int move[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
struct QNode {
    int map[10][10];
    int x, y, cnt;
    QNode* next;
};

void cpmap(int src[10][10], int dst[10][10]) {
    for (int i = 0; i < mapsize; i++) {
        for (int j = 0; j < mapsize; j++) {
            dst[i][j] = src[i][j];
        }
    }
}
QNode* cpNode(QNode* a) {
    QNode* node = new QNode;
    node->cnt = a->cnt;
    cpmap(a->map, node->map);
    node->x = a->x;
    node->y = a->y;
    node->next = nullptr;
    return node;
}
QNode *head = nullptr, *tail = nullptr;
QNode* sstart = nullptr;
QNode* pop() {
    if (head == nullptr) return nullptr;
    QNode* ret = head;
    if (head == tail) tail = nullptr;
    head = head->next;
    return ret;
}
void push(QNode* node) {
    if (head == nullptr) {
        head = node;
        tail = node;
        return;
    }
    tail->next = node;
    tail = node;
}

void bfs_init(int map_size, int map[10][10]) {
    mapsize = map_size;
    sstart = new QNode;
    cpmap(map, sstart->map);
    sstart->next = nullptr;
}

int bfs(int x1, int y1, int x2, int y2) {
    head = nullptr;
    tail = nullptr;
    push(cpNode(sstart));
    x1--;
    y1--;
    x2--;
    y2--;
    head->x = x1;
    head->y = y1;
    head->cnt = 0;
    while (head != nullptr) {
        QNode* node = pop();
        node->map[node->y][node->x] = 2;
        for (int i = 0; i < 4; i++) {
            QNode* tmp = cpNode(node);
            tmp->cnt++;
            tmp->x += move[i][0];
            tmp->y += move[i][1];
            if (tmp->x < 0 || tmp->x == mapsize || tmp->y < 0 ||
                tmp->y == mapsize || tmp->map[tmp->y][tmp->x] != 0) {
                continue;
            }
            if (tmp->x == x2 && tmp->y == y2) return tmp->cnt;
            push(tmp);
        }
    }
    return -1;
}
