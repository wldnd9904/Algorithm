#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum { ADD_HEAD = 1, ADD_TAIL, ADD_NUM, REMOVE, PRINT, END = 99 };

struct Node {
    int data;
    Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;
Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].next = nullptr;
    return &node[nodeCnt++];
}

extern void init() {
    nodeCnt = 0;
    head = nullptr;
}
extern void addNode2Head(int data) {
    Node* next = head;
    head = getNode(data);
    head->next = next;
}
extern void addNode2Tail(int data) {
    if (head == nullptr) {
        addNode2Head(data);
        return;
    }
    Node* cur = head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = getNode(data);
}
extern void addNode2Num(int data, int num) {
    if (num == 1) {
        addNode2Head(data);
        return;
    }
    Node *cur = head, *next;
    num--;
    while (--num) {
        cur = cur->next;
    }
    next = cur->next;
    cur->next = getNode(data);
    cur->next->next = next;
}
extern void removeNode(int data) {
    if (head->data == data) {  // 첫번재면 헤드 옮기기
        head = head->next;
        return;
    }
    Node* cur = head;
    while (cur->next != nullptr && cur->next->data != data) {
        cur = cur->next;
    }
    if (cur->next == nullptr) return;
    cur->next = cur->next->next;
}
extern int getList(int output[MAX_NODE]) {
    int i = 0;
    Node* cur = head;
    while (cur != nullptr) {
        output[i++] = cur->data;
        cur = cur->next;
    }
    return i;
}

static void run() {
    while (1) {
        int cmd, data, num, cnt, i;
        int output[MAX_NODE] = {0};

        scanf("%d", &cmd);
        switch (cmd) {
            case ADD_HEAD:
                scanf("%d", &data);
                addNode2Head(data);
                break;
            case ADD_TAIL:
                scanf("%d", &data);
                addNode2Tail(data);
                break;
            case ADD_NUM:
                scanf("%d %d", &data, &num);
                addNode2Num(data, num);
                break;
            case REMOVE:
                scanf("%d", &data);
                removeNode(data);
                break;
            case PRINT:
                cnt = getList(output);
                i = 0;
                while (cnt--) printf("%d ", output[i++]);
                printf("\n");
                break;
            case END:
                return;
        }
    }
}

int main(void) {
    // setbuf(stdout, NULL);
    // freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        printf("#%d\n", t);
        init();
        run();
        printf("\n");
    }

    return 0;
}