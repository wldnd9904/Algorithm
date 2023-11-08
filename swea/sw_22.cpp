#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_INPUT 10000
#define MAX_NUM 30000

extern void init();
extern void addUser(int uID, int income);
extern int getTop10(int result[10]);

static int input[MAX_INPUT];

static unsigned int seed = 13410;

static unsigned int pseudoRand() {
    seed = seed * 214013 + 2531011;
    return (unsigned int)(seed >> 11) % MAX_NUM;
}

static void makeInput(int inputLen) {
    for (int i = 0; i < inputLen; i++) {
        input[i] = pseudoRand();
    }
}

static int run() {
    int N, userNum, uID = 0;
    int score = 100, result[10], cnt;
    int sum, check;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &userNum);
        makeInput(userNum);
        for (int j = 0; j < userNum; j++) {
            addUser(uID++, input[j]);
        }
        cnt = getTop10(result);

        sum = 0;
        for (int j = 0; j < cnt; j++) sum += result[j];
        scanf("%d", &check);
        if (check != sum) score = 0;
    }
    return score;
}

int main(void) {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        init();
        printf("#%d %d\n", tc, run());
    }
    return 0;
}

#define HEAP_MAX 300000
struct pair {
    int income;
    int uID;
};
int count = 0, count2;
pair heap[HEAP_MAX];
pair heap2[HEAP_MAX];
bool less(pair a, pair b) {
    if (a.income < b.income)
        return true;
    else if (a.income == b.income && a.uID > b.uID)
        return true;
    else
        return false;
}
void init() {
    int count = 0;
    for (int i = 0; i < HEAP_MAX; i++) {
        heap[i] = {0, 0};
        heap[i] = {0, 0};
    }
}

void addUser(int uID, int height) {
    pair tmp = {height, uID};
    int cur = ++count;
    while (cur > 1 && less(heap[cur / 2], tmp)) {
        heap[cur] = heap[cur / 2];
        cur /= 2;
    }
    heap[cur] = tmp;
}
void swap(pair &a, pair &b) {
    pair tmp = a;
    a = b;
    b = tmp;
}
int popUser() {
    int ret = heap2[1].uID;
    heap2[1] = heap2[count2--];
    int cur = 1;
    while (cur * 2 + 1 <= count2) {
        if (cur * 2 == count2) {
            if (less(heap2[cur], heap2[cur * 2])) {
                swap(heap2[cur], heap2[cur * 2]);
                cur = cur * 2;
                continue;
            } else {
                return ret;
            }
        }
        if (less(heap2[cur * 2], heap2[cur * 2 + 1])) {
            if (less(heap2[cur], heap2[cur * 2 + 1])) {
                swap(heap2[cur], heap2[cur * 2 + 1]);
                cur = cur * 2 + 1;
                continue;
            } else {
                return ret;
            }
        } else {
            if (less(heap2[cur], heap2[cur * 2])) {
                swap(heap2[cur], heap2[cur * 2]);
                cur = cur * 2;
                continue;
            } else {
                return ret;
            }
        }
    }
    return ret;
}

int getTop10(int result[10]) {
    for (int i = 0; i <= count; i++) {
        heap2[i] = heap[i];
    }
    count2 = count;
    printf("%d\n", count);
    int ret = 0;
    for (int i = 0; i < 10; i++) {
        if (count2 > 0) {
            result[i] = popUser();
            ret++;
        }
    }
    return ret;
}