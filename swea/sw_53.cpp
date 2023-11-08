#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_MIN_TRAVEL_TIME 3
#define CMD_MIN_PRICE 4

extern void init(int N);
extern void add(int mStartAirport, int mEndAirport, int mStartTime,
                int mTravelTime, int mPrice);
extern int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime);
extern int minPrice(int mStartAirport, int mEndAirport);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run() {
    int numQuery;
    int N, mStartAirport, mEndAirport, mStartTime, mTravelTime, mPrice;
    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int q = 0; q < numQuery; q++) {
        int cmd;
        scanf("%d", &cmd);

        switch (cmd) {
            case CMD_INIT:
                scanf("%d", &N);
                init(N);
                isCorrect = true;
                break;
            case CMD_ADD:
                scanf("%d %d %d %d %d", &mStartAirport, &mEndAirport,
                      &mStartTime, &mTravelTime, &mPrice);
                add(mStartAirport, mEndAirport, mStartTime, mTravelTime,
                    mPrice);
                break;
            case CMD_MIN_TRAVEL_TIME:
                scanf("%d %d %d", &mStartAirport, &mEndAirport, &mStartTime);
                userAns = minTravelTime(mStartAirport, mEndAirport, mStartTime);
                scanf("%d", &ans);
                // printf("min time: %d, %d\n", userAns, ans);
                if (userAns != ans) {
                    isCorrect = false;
                }
                break;
            case CMD_MIN_PRICE:
                scanf("%d %d", &mStartAirport, &mEndAirport);
                userAns = minPrice(mStartAirport, mEndAirport);
                scanf("%d", &ans);
                // printf("min price: %d, %d\n", userAns, ans);
                if (userAns != ans) {
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
    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}
#include <queue>
#include <vector>
#define MAX 999999999
using namespace std;
int inputN;
struct Travel {
    int src, dst, srcTime, travelTime, price;
};
struct qItem {
    int time, now, curTime;
};
struct cmp {
    bool operator()(qItem &a, qItem &b) { return a.time > b.time; }
};
vector<Travel> travels[60][60];
int prices[60][60];
void init(int N) {
    inputN = N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            travels[i][j].clear();
            prices[i][j] = MAX;
        }
    }
    for (int j = 0; j < N; j++) {
        prices[j][j] = 0;
    }
}

void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime,
         int mPrice) {
    travels[mStartAirport][mEndAirport].emplace_back(
        (Travel){mStartAirport, mEndAirport, mStartTime, mTravelTime, mPrice});
    prices[mStartAirport][mEndAirport] =
        min(prices[mStartAirport][mEndAirport], mPrice);
}

int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime) {
    int dijk[60];
    for (int i = 0; i < inputN; i++) {
        dijk[i] = MAX;
    }
    priority_queue<qItem, vector<qItem>, cmp> pq;
    pq.push((qItem){0, mStartAirport, mStartTime});
    while (!pq.empty()) {
        int time = pq.top().time;
        int now = pq.top().now;
        int curTime = pq.top().curTime;
        pq.pop();
        if (now == mEndAirport) return time;
        for (int i = 0; i < inputN; i++) {
            if (i == now) continue;
            for (auto it : travels[now][i]) {
                int tmpTime =
                    time + (it.srcTime - curTime + 24) % 24 + it.travelTime;
                int tmpCurTime = (it.srcTime + it.travelTime) % 24;
                if (tmpTime < dijk[i]) {
                    dijk[i] = tmpTime;
                    pq.push({tmpTime, i, tmpCurTime});
                }
            }
        }
    }
    if (dijk[mEndAirport] >= MAX) return -1;
    return dijk[mEndAirport];
}

int minPrice(int mStartAirport, int mEndAirport) {
    int dijk[60];
    for (int i = 0; i < inputN; i++) {
        dijk[i] = MAX;
    }
    priority_queue<pair<int, int>> pq;
    pq.push({0, mStartAirport});
    while (!pq.empty()) {
        int price = -pq.top().first;
        int now = pq.top().second;
        pq.pop();
        if (dijk[now] < price) continue;
        if (now == mEndAirport) return price;
        for (int i = 0; i < inputN; i++) {
            if (prices[now][i] == 0) continue;
            int tmpprice = price + prices[now][i];
            if (tmpprice < dijk[i]) {
                dijk[i] = tmpprice;
                pq.push({-tmpprice, i});
            }
        }
    }
    if (dijk[mEndAirport] >= MAX) return -1;
    return dijk[mEndAirport];
}