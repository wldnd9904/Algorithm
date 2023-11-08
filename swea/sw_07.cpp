#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum {
    ADD_HEAD = 1,
    ADD_TAIL,
    ADD_NUM,
    FIND,
    REMOVE,
    PRINT,
    PRINT_REVERSE,
    END = 99
};
struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;
Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].prev = nullptr;
    node[nodeCnt].next = nullptr;
    return &node[nodeCnt++];
}
extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern int findNode(int data);
extern void removeNode(int data);
extern int getList(int output[MAX_NODE]);
extern int getReversedList(int output[MAX_NODE]);

static void run() {
    while (1) {
        int cmd, data, num, cnt, i = 0;
        int output[MAX_NODE] = {0};

        scanf("%d", &cmd);
        switch (cmd) {
            case ADD_HEAD:  // 1
                scanf("%d", &data);
                addNode2Head(data);
                break;
            case ADD_TAIL:  // 2
                scanf("%d", &data);
                addNode2Tail(data);
                break;
            case ADD_NUM:  // 3
                scanf("%d %d", &data, &num);
                addNode2Num(data, num);
                break;
            case FIND:  // 4
                scanf("%d", &data);
                num = findNode(data);
                printf("%d\n", num);
                break;
            case REMOVE:  // 5
                scanf("%d", &data);
                removeNode(data);
                break;
            case PRINT:  // 6
                cnt = getList(output);
                while (cnt--) printf("%d ", output[i++]);
                printf("\n");
                break;
            case PRINT_REVERSE:  // 7
                cnt = getReversedList(output);
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
    freopen("input.txt", "r", stdin);

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
///-------------USERCODE-------------///

void init() {
    nodeCnt = 0;
    head = nullptr;
}

void addNode2Head(int data) {
    if (head == nullptr) {
        head = getNode(data);
        head->prev = head;
        head->next = head;
    } else {
        Node* tmp = getNode(data);
        tmp->prev = head->prev;
        tmp->next = head;
        tmp->next->prev = tmp;
        tmp->prev->next = tmp;
        head = tmp;
    }
}

void addNode2Tail(int data) {
    if (head == nullptr) {
        head = getNode(data);
        head->prev = head;
        head->next = head;
    } else {
        Node* tmp = getNode(data);
        tmp->next = head;
        tmp->prev = head->prev;
        tmp->next->prev = tmp;
        tmp->prev->next = tmp;
    }
}

void addNode2Num(int data, int num) {
    if (num == 1) {
        addNode2Head(data);
        return;
    }
    Node* cur = head;
    num--;
    while (--num) {
        cur = cur->next;
    }
    Node* tmp = getNode(data);
    tmp->next = cur->next;
    tmp->prev = cur;
    tmp->next->prev = tmp;
    tmp->prev->next = tmp;
}

int findNode(int data) {
    Node* cur = head;
    int i = 1;
    while (cur->data != data) {
        cur = cur->next;
        i++;
    }
    return i;
}

void removeNode(int data) {
    Node* cur = head;
    while (cur->data != data && cur->next != head) {
        cur = cur->next;
    }
    // 끝까지 봤는데 숫자 다르면 아무것도 안함
    if (cur->data != data) return;
    // 하나만 남으면 헤드에 널포인터
    if (cur == head && cur->next == head && cur->prev == head) {
        head = nullptr;
        return;
    }
    // 그건 아닌데 지우려는게 헤드면 다음놈이 헤드
    if (cur == head) head = cur->next;
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
}

int getList(int output[MAX_NODE]) {
    output[0] = head->data;
    Node* cur = head->next;
    int i = 1;
    while (cur != head) {
        output[i++] = cur->data;
        cur = cur->next;
    }
    return i;
}

int getReversedList(int output[MAX_NODE]) {
    Node* cur = head->prev;
    int i = 0;
    while (cur != head) {
        output[i++] = cur->data;
        cur = cur->prev;
    }
    output[i++] = cur->data;
    return i;
}