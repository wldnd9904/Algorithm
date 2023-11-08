#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAXL (11 + 1)

#define CMD_INIT (100)
#define CMD_ADD (200)
#define CMD_DISTANCE (300)
#define CMD_COUNT (400)

extern void init(char mAncestor[], int mLastday);
extern int add(char mName[], char mParent[], int mFirstday, int mLastday);
extern int distance(char mName1[], char mName2[]);
extern int count(int mDay);

static bool run() {
    int Q;
    int ret = -1, ans;
    bool okay = false;

    scanf("%d", &Q);

    for (int q = 0; q < Q; ++q) {
        int cmd;
        char mName1[MAXL], mName2[MAXL];
        int mDay1, mDay2;
        scanf("%d", &cmd);

        switch (cmd) {
            case CMD_INIT:
                scanf("%s %d", mName1, &mDay1);
                init(mName1, mDay1);
                okay = true;
                break;
            case CMD_ADD:
                scanf("%s %s %d %d", mName1, mName2, &mDay1, &mDay2);
                ret = add(mName1, mName2, mDay1, mDay2);
                scanf("%d", &ans);
                if (ret != ans) okay = false;
                break;
            case CMD_DISTANCE:
                scanf("%s %s", mName1, mName2);
                ret = distance(mName1, mName2);
                scanf("%d", &ans);
                // printf("distance: %d, %d\n", ret, ans);
                if (ret != ans) okay = false;
                break;
            case CMD_COUNT:
                scanf("%d", &mDay1);
                ret = count(mDay1);
                scanf("%d", &ans);
                // printf("count: %d, %d\n", ret, ans);
                if (ret != ans) okay = false;
                break;
            default:
                okay = false;
                break;
        }
    }

    return okay;
}

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int TC, MARK;

    scanf("%d %d", &TC, &MARK);

    for (int tc = 1; tc <= TC; ++tc) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}
#include <string>
#include <unordered_map>
#define MAX 1048576
using namespace std;
unordered_map<string, int> creatureID;
int depth[12001];
int ancestors[12001][12];
int creatureCnt;
int segtree[2 * MAX];

void treeAdd(int idx, int l, int r, int from, int to) {
    if (r < from || to < l) return;
    if (from <= l && r <= to) {
        segtree[idx] += 1;
        return;
    }
    int mid = l + (r - l) / 2;
    treeAdd(idx * 2, l, mid, from, to);
    treeAdd(idx * 2 + 1, mid + 1, r, from, to);
}

void init(char mAncestor[], int mDeathday) {
    creatureID.clear();
    creatureCnt = 0;
    int id = creatureCnt++;
    depth[id] = 0;
    for (int i = 0; i < 2 * MAX; i++) {
        segtree[i] = 0;
    }
    treeAdd(1, 0, MAX - 1, 0, mDeathday);
    return;
}

int add(char mName[], char mParent[], int mBirthday, int mDeathday) {
    int pid = creatureID[mParent];
    creatureID[mName] = creatureCnt;
    ancestors[creatureCnt][0] = pid;
    int id = creatureCnt++;
    depth[id] = depth[pid] + 1;
    for (int j = 1; j <= 10; j++) {
        int t = ancestors[id][j - 1];
        ancestors[id][j] = ancestors[t][j - 1];
    }
    treeAdd(1, 0, MAX - 1, mBirthday, mDeathday);
    return depth[id];
}

int distance(char mName1[], char mName2[]) {
    int oa = creatureID[mName1], ob = creatureID[mName2];
    int a = oa, b = ob;
    if (depth[a] > depth[b]) swap(a, b);
    for (int i = 10; i >= 0; i--) {
        if (depth[a] <= depth[ancestors[b][i]]) {
            b = ancestors[b][i];
        }
    }
    int ret = a;
    if (a != b) {
        for (int i = 10; i >= 0; i--) {
            if (ancestors[a][i] != ancestors[b][i]) {
                a = ancestors[a][i];
                b = ancestors[b][i];
            }
            ret = ancestors[a][i];
        }
    }
    return depth[oa] + depth[ob] - 2 * depth[ret];
}

int count(int mDay) {
    int idx = mDay + MAX;
    int ret = 0;
    while (idx != 0) {
        ret += segtree[idx];
        idx /= 2;
    }
    return ret;
}