#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_DESTROY 200
#define CMD_ALLY 300
#define CMD_ATTACK 400
#define CMD_RECRUIT 500

/////////////////////////////////////////////////////////////////////////
extern void init(int N, int mSoldier[25][25], char mGeneral[25][25][11]);
extern void destroy();
extern int ally(char mMonarchA[11], char mMonarchB[11]);
extern int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11]);
extern int recruit(char mMonarch[11], int mNum, int mOption);
/////////////////////////////////////////////////////////////////////////

#define MAX_N 25
#define MAX_L 10

static int Sol[MAX_N][MAX_N];
static char General[MAX_N][MAX_N][MAX_L + 1];

static int run() {
    int isOK = 0;

    int N;
    int cmd;
    int result;
    int check;

    int mN;
    char mMonarchA[11];
    char mMonarchB[11];
    char mGeneral[11];
    int mOption;
    int num;

    scanf("%d", &N);

    for (int c = 0; c < N; ++c) {
        scanf("%d", &cmd);
        switch (cmd) {
            case CMD_INIT:
                scanf("%d", &mN);
                for (int j = 0; j < mN; j++)
                    for (int i = 0; i < mN; i++) scanf("%d", &Sol[j][i]);

                for (int j = 0; j < mN; j++)
                    for (int i = 0; i < mN; i++) scanf("%s", General[j][i]);

                init(mN, Sol, General);
                isOK = 1;
                break;

            case CMD_ALLY:
                scanf("%s %s", mMonarchA, mMonarchB);
                result = ally(mMonarchA, mMonarchB);
                scanf("%d", &check);
                // printf("ally: %d, %d\n", result, check);
                if (result != check) isOK = 0;
                break;

            case CMD_ATTACK:
                scanf("%s %s %s", mMonarchA, mMonarchB, mGeneral);
                result = attack(mMonarchA, mMonarchB, mGeneral);
                scanf("%d", &check);
                // printf("attack: %d, %d\n", result, check);
                if (result != check) isOK = 0;
                break;

            case CMD_RECRUIT:
                scanf("%s %d %d", mMonarchA, &num, &mOption);
                result = recruit(mMonarchA, num, mOption);
                scanf("%d", &check);
                // printf("recruit: %d, %d\n", result, check);
                if (result != check) isOK = 0;
                break;

            default:
                isOK = 0;
                break;
        }
    }

    destroy();

    return isOK;
}

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++) {
        if (run())
            printf("#%d %d\n", tc, MARK);
        else
            printf("#%d %d\n", tc, 0);
    }
    return 0;
}
#include <list>
#include <string>
#include <unordered_map>

using namespace std;
int InputN;

int parent[8625];

list<int> UnionList[625];
list<int> EnemyList[625];

int Find(int x) {
    if (x == parent[x])
        return x;
    else
        return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
        parent[y] = x;
        UnionList[x].splice(UnionList[x].end(), UnionList[y]);
        EnemyList[x].splice(EnemyList[x].end(), EnemyList[y]);
    }
}

int IsSameUnion(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y)
        return 1;
    else
        return 0;
}

int IsEnemy(int x, int y) {
    x = Find(x);
    y = Find(y);
    for (auto enemy : EnemyList[x]) {
        if (Find(enemy) == y) return 1;
    }
    return 0;
}

void MakeEnemy(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (IsEnemy(x, y)) return;
    EnemyList[x].push_back(y);
    EnemyList[y].push_back(x);
}

struct SNationInfo {
    int x;
    int y;
    int sol;
};

SNationInfo Nation[8625];
int NationIndex[26][26];

unordered_map<string, int> NationMap;

int NactionCount;

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11]) {
    InputN = N;
    int index = 0;
    NationMap.clear();
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            NationMap[mMonarch[j][i]] = index;

            NationIndex[j][i] = index;

            Nation[index].sol = mSoldier[j][i];
            Nation[index].x = i;
            Nation[index].y = j;
            parent[index] = index;

            UnionList[index].clear();
            EnemyList[index].clear();

            UnionList[index].push_back(index);

            index++;
        }
    }

    NactionCount = N * N;
}

void destroy() {}

int ally(char mMonarchA[11], char mMonarchB[11]) {
    int a = NationMap[mMonarchA];
    int b = NationMap[mMonarchB];

    if (IsSameUnion(a, b)) {
        return -1;
    }
    if (IsEnemy(a, b)) {
        return -2;
    }

    Union(a, b);
    return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11]) {
    int a = NationMap[mMonarchA];
    int b = NationMap[mMonarchB];

    int bossA = Find(a);
    int bossB = Find(b);

    if (bossA == bossB) {
        return -1;
    }

    int sx = Nation[b].x - 1;
    int ex = Nation[b].x + 1;
    int sy = Nation[b].y - 1;
    int ey = Nation[b].y + 1;

    if (sx < 0) sx = 0;
    if (sy < 0) sy = 0;
    if (ex > InputN - 1) ex = InputN - 1;
    if (ey > InputN - 1) ey = InputN - 1;

    int isThereEnemy = 0;
    for (int j = sy; j <= ey; j++) {
        for (int i = sx; i <= ex; i++) {
            if (bossA == Find(NationIndex[j][i])) {
                isThereEnemy = 1;
                j = InputN;
                break;
            }
        }
    }

    if (isThereEnemy == 0) {
        return -2;
    }

    MakeEnemy(bossA, bossB);

    int totalSolA = 0;
    int totalSolB = Nation[b].sol;
    Nation[b].sol = 0;
    int moveNum;

    for (int j = sy; j <= ey; j++) {
        for (int i = sx; i <= ex; i++) {
            if (bossA == Find(NationIndex[j][i])) {
                moveNum = Nation[NationIndex[j][i]].sol / 2;
                Nation[NationIndex[j][i]].sol -= moveNum;
                totalSolA += moveNum;
            } else if (bossB == Find(NationIndex[j][i])) {
                moveNum = Nation[NationIndex[j][i]].sol / 2;
                Nation[NationIndex[j][i]].sol -= moveNum;
                totalSolB += moveNum;
            }
        }
    }

    if (totalSolB >= totalSolA) {
        Nation[b].sol = totalSolB - totalSolA;
        return 0;
    }

    UnionList[bossB].remove(b);

    Nation[b].sol = totalSolA - totalSolB;
    Nation[NactionCount] = Nation[b];

    NationIndex[Nation[NactionCount].y][Nation[NactionCount].x] = NactionCount;

    NationMap[mGeneral] = NactionCount;

    parent[NactionCount] = bossA;
    UnionList[bossA].push_back(NactionCount);

    NactionCount++;
    return 1;
}

int recruit(char mMonarch[11], int mNum, int mOption) {
    int sum = 0;

    if (mOption == 0) {
        int a = NationMap[mMonarch];
        Nation[a].sol += mNum;
        sum = Nation[a].sol;
    } else {
        int boss = Find(NationMap[mMonarch]);
        for (auto nation : UnionList[boss]) {
            Nation[nation].sol += mNum;
            sum += Nation[nation].sol;
        }
    }
    return sum;
}