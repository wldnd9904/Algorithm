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
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
bool isNeighbor(int x1, int y1, int x2, int y2) {
    if (x1 - x2 >= -1 && x1 - x2 <= 1 && y1 - y2 >= -1 && y1 - y2 <= 1)
        return true;
    else
        return false;
}
struct Monarch {
    int id, x, y, ally, soldier;
};

Monarch *monarch[10000];

int findBoss(Monarch *mon) {
    if (mon->id == mon->ally)
        return mon->id;
    else
        return mon->ally = monarch[findBoss(monarch[mon->ally])]->ally;
}
unordered_map<string, int> monarchID;
list<int> allies[625];
list<int> enemies[625];
vector<vector<int>> map;
int mapN;
int monarchCnt;

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11]) {
    mapN = N;
    monarchID.clear();
    map.clear();
    monarchCnt = 0;
    for (int i = 0; i < 10000; i++) {
        monarch[i] = nullptr;
    }
    for (int i = 0; i < 625; i++) {
        allies[i].clear();
        enemies[i].clear();
    }
    map = vector<vector<int>>(N, vector<int>(N, 0));
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            Monarch *tmp = new Monarch;
            tmp->id = monarchCnt++;
            tmp->soldier = mSoldier[y][x];
            tmp->ally = tmp->id;
            monarchID[mMonarch[y][x]] = tmp->id;
            tmp->x = x;
            tmp->y = y;
            allies[tmp->id].push_back(tmp->id);
            map[y][x] = tmp->id;
            monarch[tmp->id] = tmp;
        }
    }
}

void destroy() {}

int ally(char mMonarchA[11], char mMonarchB[11]) {
    int A = monarchID[mMonarchA], B = monarchID[mMonarchB];
    int bossA = findBoss(monarch[A]), bossB = findBoss(monarch[B]);
    if (bossA == bossB) return -1;
    for (auto enemy : enemies[bossA]) {
        if (findBoss(monarch[enemy]) == bossB) return -2;
    }
    monarch[bossB]->ally = bossA;
    enemies[bossA].splice(enemies[bossA].end(), enemies[bossB]);
    allies[bossA].splice(allies[bossA].end(), allies[bossB]);
    return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11]) {
    int A = monarchID[mMonarchA], B = monarchID[mMonarchB];
    int bossA = findBoss(monarch[A]), bossB = findBoss(monarch[B]);
    if (bossA == bossB) return -1;
    int soldiers = 0, attackCnt = 0, enemyCnt = monarch[B]->soldier;

    int sx = monarch[B]->x - 1, ex = monarch[B]->x + 1, sy = monarch[B]->y - 1,
        ey = monarch[B]->y + 1;

    if (sx < 0) sx = 0;
    if (sy < 0) sy = 0;
    if (ex > mapN - 1) ex = mapN - 1;
    if (ey > mapN - 1) ey = mapN - 1;
    for (int j = sy; j <= ey; j++) {
        for (int i = sx; i <= ex; i++) {
            if (bossA == findBoss(monarch[map[j][i]])) {
                attackCnt++;
                j = ey;
                break;
            }
        }
    }
    if (attackCnt == 0) return -2;
    for (int j = sy; j <= ey; j++) {
        for (int i = sx; i <= ex; i++) {
            if (bossA == findBoss(monarch[map[j][i]])) {
                soldiers += monarch[map[j][i]]->soldier / 2;
                monarch[map[j][i]]->soldier -= monarch[map[j][i]]->soldier / 2;
            } else if (bossB == findBoss(monarch[map[j][i]])) {
                if (map[j][i] == B) continue;
                enemyCnt += monarch[map[j][i]]->soldier / 2;
                monarch[map[j][i]]->soldier -= monarch[map[j][i]]->soldier / 2;
            }
        }
    }
    bool isEnemy = false;
    for (auto it : enemies[bossA])
        if (findBoss(monarch[it]) == bossB) isEnemy = true;
    if (!isEnemy) {
        enemies[bossA].push_back(bossB);
        enemies[bossB].push_back(bossA);
    }
    soldiers -= enemyCnt;
    if (soldiers <= 0) {
        monarch[B]->soldier = -1 * soldiers;
        return 0;
    }
    allies[bossB].remove(B);
    Monarch *tmp = new Monarch;
    tmp->ally = bossA;
    tmp->id = monarchCnt++;
    monarch[tmp->id] = tmp;
    tmp->x = monarch[B]->x;
    tmp->y = monarch[B]->y;
    map[tmp->y][tmp->x] = tmp->id;
    tmp->soldier = soldiers;
    allies[bossA].push_back(tmp->id);
    monarchID[mGeneral] = tmp->id;
    return 1;
}

int recruit(char mMonarch[11], int mNum, int mOption) {
    int id = monarchID[mMonarch];
    if (mOption == 0) {
        monarch[id]->soldier += mNum;
        return monarch[id]->soldier;
    } else {
        int ans = 0;
        int boss = findBoss(monarch[id]);
        for (auto it = allies[boss].begin(); it != allies[boss].end(); it++) {
            monarch[*it]->soldier += mNum;
            ans += monarch[*it]->soldier;
        }
        return ans;
    }
}
