#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern int init(int N, int sCity[], int eCity[], int mCost[]);
extern void add(int sCity, int eCity, int mCost);
extern int cost(int mHub);

/////////////////////////////////////////////////////////////////////////

#define MAX_N 1400
#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_COST 3

static bool run() {
    int q;
    scanf("%d", &q);

    int n;
    int sCityArr[MAX_N], eCityArr[MAX_N], mCostArr[MAX_N];
    int sCity, eCity, mCost, mHub;
    int cmd, ans, ret = 0;
    bool okay = false;

    for (int i = 0; i < q; ++i) {
        scanf("%d", &cmd);
        switch (cmd) {
            case CMD_INIT:
                okay = true;
                scanf("%d", &n);
                for (int j = 0; j < n; ++j) {
                    scanf("%d %d %d", &sCityArr[j], &eCityArr[j], &mCostArr[j]);
                }
                scanf("%d", &ans);
                ret = init(n, sCityArr, eCityArr, mCostArr);
                if (ans != ret) okay = false;
                break;
            case CMD_ADD:
                scanf("%d %d %d", &sCity, &eCity, &mCost);
                add(sCity, eCity, mCost);
                break;
            case CMD_COST:
                scanf("%d %d", &mHub, &ans);
                ret = cost(mHub);
                printf("%d, %d\n", ans, ret);
                if (ans != ret) okay = false;
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

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;
struct Road {
    int sCity, eCity, mCost;
};
unordered_map<int, int> cityID;
vector<Road> roads[600];
vector<Road> roads2[600];
int cityCnt;
int init(int N, int sCity[], int eCity[], int mCost[]) {
    cityID.clear();
    cityCnt = 0;
    for (int i = 0; i < 600; i++) {
        roads[i].clear();
        roads2[i].clear();
    }
    for (int i = 0; i < N; i++) {
        int s, e;
        if (cityID.count(sCity[i]))
            s = cityID[sCity[i]];
        else
            s = cityID[sCity[i]] = cityCnt++;
        if (cityID.count(eCity[i]))
            e = cityID[eCity[i]];
        else
            e = cityID[eCity[i]] = cityCnt++;
        roads[s].push_back(Road{s, e, mCost[i]});
        roads2[e].push_back(Road{s, e, mCost[i]});
    }

    return cityCnt;
}

void add(int sCity, int eCity, int mCost) {
    int s = cityID[sCity], e = cityID[eCity];
    roads[s].push_back(Road{s, e, mCost});
    roads2[e].push_back(Road{s, e, mCost});
}

int dijkstra(int s) {
    priority_queue<pair<int, int>> q;
    vector<int> dijk(cityCnt, 9999999);
    dijk[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        int cost = -q.top().first;
        int now = q.top().second;
        q.pop();
        if (dijk[now] < cost) continue;
        for (auto i : roads[now]) {
            int tmpCost = cost + i.mCost;
            if (dijk[i.eCity] > tmpCost) {
                dijk[i.eCity] = tmpCost;
                q.push({-tmpCost, i.eCity});
            }
        }
    }
    int ans = 0;
    for (int cost : dijk) ans += cost;
    return ans;  // error
}

int dijkstra2(int s) {
    priority_queue<pair<int, int>> q;
    vector<int> dijk(cityCnt, 9999999);
    dijk[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        int cost = -q.top().first;
        int now = q.top().second;
        q.pop();
        if (dijk[now] < cost) continue;
        for (auto i : roads2[now]) {
            int tmpCost = cost + i.mCost;
            if (dijk[i.sCity] > tmpCost) {
                dijk[i.sCity] = tmpCost;
                q.push({-tmpCost, i.sCity});
            }
        }
    }
    int ans = 0;
    for (int cost : dijk) ans += cost;
    return ans;  // error
}
int cost(int mHub) {
    int ret = 0, hub = cityID[mHub];
    ret = dijkstra(hub) + dijkstra2(hub);
    return ret;
}