#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#include <iostream>
using namespace std;
#define MAX_ARR_SIZE (100000)

void init(int, int[]);
void add(int, int[]);
void erase(int, int);
int find(int);

#define CMD_INIT (100)
#define CMD_ADD (200)
#define CMD_ERASE (300)
#define CMD_FIND (400)

static int arr[MAX_ARR_SIZE];
static int N, M;
static int from, to;

static bool run() {
    int query_num;
    scanf("%d", &query_num);

    int ret, ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++) {
        int query;
        scanf("%d", &query);

        if (query == CMD_INIT) {
            scanf("%d", &N);
            for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
            init(N, arr);
            ok = true;
        } else if (query == CMD_ADD) {
            scanf("%d", &M);
            for (int i = 0; i < M; i++) scanf("%d", &arr[i]);
            add(M, arr);
        } else if (query == CMD_ERASE) {
            scanf("%d%d", &from, &to);
            erase(from, to);

        } else if (query == CMD_FIND) {
            int K;
            scanf("%d", &K);
            ret = find(K);
            scanf("%d", &ans);
            if (ans != ret) ok = false;
        }
    }
    return ok;
}

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}
#include <vector>
using namespace std;
struct Node {
    int min, max, cnt;
    vector<int> v;
};
int nodeCnt;
bool latest;
Node* nodes[3001];

void add(int cnt, int values[]) {
    latest = false;
    Node* node = new Node;
    node->max = 0;
    node->min = 100000001;
    node->cnt = cnt;
    node->v = vector<int>(cnt);
    for (size_t i = 0; i < cnt; ++i) {
        node->v[i] = values[i];
        node->min = min(node->min, values[i]);
        node->max = max(node->max, values[i]);
    }
    nodes[nodeCnt++] = node;
};

void init(int N, int values[]) {
    for (int i = 0; i <= 3000; i++) {
        if (nodes[i] != nullptr) delete nodes[i];
        nodes[i] = nullptr;
    }
    nodeCnt = 0;
    int i = 0;
    for (; i < N / 100; i++) {
        add(100, values + i * 100);
    }
    if (N % 100 > 0) add(N % 100, values + i * 100);
};
void erase(int mFrom, int mTo) {
    latest = false;
    int from = 0;
    while (from < nodeCnt) {
        if (nodes[from]->cnt < mFrom) {
            mFrom -= nodes[from]->cnt;
            mTo -= nodes[from]->cnt;
            from++;
        } else
            break;
    }
    int to = from;
    while (to < nodeCnt) {
        if (nodes[to]->cnt < mTo) {
            mTo -= nodes[to]->cnt;
            to++;
        } else
            break;
    }
    if (from == nodeCnt) from--;
    if (to == nodeCnt) to--;
    // 같은 노드에서 지움
    if (from == to) {
        nodes[from]->v.erase(nodes[from]->v.begin() + mFrom - 1,
                             nodes[from]->v.begin() + mTo);
        nodes[from]->cnt = nodes[from]->v.size();
        nodes[from]->max = 0;
        nodes[from]->min = 100000001;
        for (auto it = nodes[from]->v.begin(); it != nodes[from]->v.end();
             it++) {
            nodes[from]->max = max(nodes[from]->max, *it);
            nodes[from]->min = min(nodes[from]->min, *it);
        }
    } else {  // 두 개 이상
        nodes[from]->v.erase(nodes[from]->v.begin() + mFrom - 1,
                             nodes[from]->v.end());
        nodes[from]->cnt = nodes[from]->v.size();
        nodes[from]->max = 0;
        nodes[from]->min = 100000001;
        for (auto it = nodes[from]->v.begin(); it != nodes[from]->v.end();
             it++) {
            nodes[from]->max = max(nodes[from]->max, *it);
            nodes[from]->min = min(nodes[from]->min, *it);
        }
        for (int i = from + 1; i < to; i++) {
            nodes[i]->cnt = 0;
        }
        nodes[to]->v.erase(nodes[to]->v.begin(), nodes[to]->v.begin() + mTo);
        nodes[to]->cnt = nodes[to]->v.size();
        nodes[to]->max = 0;
        nodes[to]->min = 100000001;
        for (auto it = nodes[to]->v.begin(); it != nodes[to]->v.end(); it++) {
            nodes[to]->max = max(nodes[to]->max, *it);
            nodes[to]->min = min(nodes[to]->min, *it);
        }
    }
};
int find(int K) {
    int rmin = 100000001, rmax = 0;
    K--;
    int from = nodeCnt - 1;
    while (from > 0) {
        if (nodes[from]->cnt <= K) {
            K -= nodes[from--]->cnt;
        } else
            break;
    }
    for (int i = nodes[from]->cnt - K - 1; i < nodes[from]->cnt; i++) {
        rmin = min(rmin, nodes[from]->v[i]);
        rmax = max(rmax, nodes[from]->v[i]);
    }
    from++;
    while (from < nodeCnt) {
        if (nodes[from]->cnt == 0) {
            from++;
            continue;
        }
        rmin = min(rmin, nodes[from]->min);
        rmax = max(rmax, nodes[from]->max);
        from++;
    }
    return rmax - rmin;
};