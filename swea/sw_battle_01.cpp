#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#include <chrono>
#include <iostream>

#define CMD_INIT 1
#define CMD_HIRE 2
#define CMD_FIRE 3
#define CMD_UPDATE_SOLDIER 4
#define CMD_UPDATE_TEAM 5
#define CMD_BEST_SOLDIER 6

extern void init();
extern void hire(int mID, int mTeam, int mScore);
extern void fire(int mID);
extern void updateSoldier(int mID, int mScore);
extern void updateTeam(int mTeam, int mChangeScore);
extern int bestSoldier(int mTeam);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run() {
    int numQuery;

    int mID, mTeam, mScore, mChangeScore;

    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i) {
        // printf("%d: ", i);
        int cmd;
        scanf("%d", &cmd);
        switch (cmd) {
            case CMD_INIT:
                init();
                isCorrect = true;
                break;
            case CMD_HIRE:
                scanf("%d %d %d", &mID, &mTeam, &mScore);
                hire(mID, mTeam, mScore);
                break;
            case CMD_FIRE:
                scanf("%d", &mID);
                fire(mID);
                break;
            case CMD_UPDATE_SOLDIER:
                scanf("%d %d", &mID, &mScore);
                updateSoldier(mID, mScore);
                break;
            case CMD_UPDATE_TEAM:
                scanf("%d %d", &mTeam, &mChangeScore);
                updateTeam(mTeam, mChangeScore);
                break;
            case CMD_BEST_SOLDIER:
                scanf("%d", &mTeam);
                userAns = bestSoldier(mTeam);
                scanf("%d", &ans);
                if (userAns != ans) {
                    printf("\n%d,%d \n", userAns, ans);
                    isCorrect = false;
                }
                break;
            default:
                isCorrect = false;
                break;
        }
    }

    return isCorrect;
}

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    std::chrono::system_clock::time_point startTime =
        std::chrono::system_clock::now();
    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    std::chrono::system_clock::time_point endTime =
        std::chrono::system_clock::now();
    std::chrono::milliseconds millisecond =
        std::chrono::duration_cast<std::chrono::milliseconds>(endTime -
                                                              startTime);
    std::cout << "Time Cost: " << millisecond.count() << " ms\n";

    return 0;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#include <queue>
using namespace std;
struct Soldier {
    int mID, mTeam;
    bool deprecated;
};
struct cmp2 {
    bool operator()(Soldier *a, Soldier *b) { return a->mID < b->mID; }
};
typedef priority_queue<Soldier *, vector<Soldier *>, cmp2> heap;
struct cmp1 {
    bool operator()(heap *a, heap *b) { return a->top()->mID < b->top()->mID; }
};
typedef priority_queue<heap *, vector<heap *>, cmp1> heapheap;
int soldierCnt;
Soldier soldiers[200000];
Soldier *mIDs[100001];
heapheap *qq[6][6];
heap *q[6][6];  // [팀번호][점수]

Soldier *newSoldier(int mID, int mTeam) {
    Soldier *ret = &soldiers[soldierCnt++];
    ret->deprecated = false;
    ret->mID = mID;
    ret->mTeam = mTeam;
    mIDs[mID] = ret;
    return ret;
}

void deprecateSoldier(int mID) { mIDs[mID]->deprecated = true; }

void init() {
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            qq[i][j] = new heapheap;
            q[i][j] = new heap;
        }
    }
    for (int i = 100000; i > 0; i--) {
        mIDs[i] = nullptr;
    }
    soldierCnt = 0;
}

void hire(int mID, int mTeam, int mScore) {
    q[mTeam][mScore]->push(newSoldier(mID, mTeam));
}

void fire(int mID) { deprecateSoldier(mID); }

void updateSoldier(int mID, int mScore) {
    int mTeam = mIDs[mID]->mTeam;
    deprecateSoldier(mID);
    hire(mID, mTeam, mScore);
}

int changeScore(int from, const int mChangeScore) {
    from += mChangeScore;
    if (from >= 5) return 5;
    if (from <= 1) return 1;
    return from;
}

void changeTeamScore(const int mTeam, const int from, const int to) {
    if (from == to) return;
    if (qq[mTeam][to]->empty()) {
        delete qq[mTeam][to];
        qq[mTeam][to] = qq[mTeam][from];
        qq[mTeam][from] = new heapheap;
    } else {
        while (!qq[mTeam][from]->empty()) {
            heap *tmp = qq[mTeam][from]->top();
            qq[mTeam][from]->pop();
            qq[mTeam][to]->push(tmp);
        }
    }
    if (q[mTeam][to]->empty()) {
        delete q[mTeam][to];
        q[mTeam][to] = q[mTeam][from];
        q[mTeam][from] = new heap;
    } else {
        if (q[mTeam][from]->size() > 15) {
            heap *tmp = q[mTeam][from];
            qq[mTeam][to]->push(tmp);
            q[mTeam][from] = new heap;
        }
        while (!q[mTeam][from]->empty()) {
            Soldier *tmp = q[mTeam][from]->top();
            q[mTeam][from]->pop();
            if (!tmp->deprecated) {
                q[mTeam][to]->push(tmp);
            }
        }
    }
}

void updateTeam(const int mTeam, const int mChangeScore) {
    if (mChangeScore > 0) {
        for (int i = 4; i >= 1; i--) {
            int newScore = changeScore(i, mChangeScore);
            changeTeamScore(mTeam, i, newScore);
        }
    } else if (mChangeScore < 0) {
        for (int i = 2; i <= 5; i++) {
            int newScore = changeScore(i, mChangeScore);
            changeTeamScore(mTeam, i, newScore);
        }
    }
}

int findBest(heapheap *h) {
    Soldier *candi;
    if (h->empty()) return 0;
    while (true) {
        candi = h->top()->top();
        if (candi->deprecated) {
            heap *tmp = h->top();
            tmp->pop();
            h->pop();
            if (!tmp->empty()) h->push(tmp);
        } else
            break;
    }
    return candi->mID;
}
int findBest(heap *h) {
    Soldier *candi;
    if (h->empty()) return 0;
    while (true) {
        candi = h->top();
        if (candi->deprecated) {
            h->pop();
            if (h->empty()) return 0;
        } else
            break;
    }
    return candi->mID;
}

int bestSoldier(int mTeam) {
    int ret = 0;
    for (int i = 5; i > 0; i--) {
        if (q[mTeam][i]->empty() && qq[mTeam][i]->empty()) continue;
        if (!q[mTeam][i]->empty()) {
            ret = max(ret, findBest(q[mTeam][i]));
        }
        if (!qq[mTeam][i]->empty()) {
            ret = max(ret, findBest(qq[mTeam][i]));
        }
        if (ret != 0) return ret;
    }
    return 0;
}