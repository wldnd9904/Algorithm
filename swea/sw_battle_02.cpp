#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
struct Result {
    int mPrice;
    int mPerformance;
};

extern void init(int mCharge);
extern Result order(int mBudget);
extern int stock(int mType, int mPerformance, int mPrice, int mPosition);

/////////////////////////////////////////////////////////////////////////

#define INIT 0
#define STOCK 1
#define ORDER 2

static bool run() {
    int cmd, ans, ans2, ret;
    int in, in2, in3, in4;
    int Q = 0;
    bool okay = false;
    Result Ret;

    scanf("%d", &Q);

    for (int q = 0; q < Q; ++q) {
        scanf("%d", &cmd);

        switch (cmd) {
            case INIT:
                scanf("%d", &in);
                init(in);
                okay = true;
                break;

            case STOCK:
                scanf("%d %d %d %d", &in, &in2, &in3, &in4);
                ret = stock(in, in2, in3, in4);
                scanf("%d", &ans);
                if (ret != ans) okay = false;
                break;

            case ORDER:
                scanf("%d", &in);
                Ret = order(in);
                scanf("%d %d", &ans, &ans2);
                if (Ret.mPrice != ans || Ret.mPerformance != ans2)
                    printf("budget: %d, %d, %d, %d, %d\n", in, Ret.mPerformance,
                           ans2, Ret.mPrice, ans);
                if (Ret.mPrice != ans || Ret.mPerformance != ans2) okay = false;
                break;

            default:
                okay = false;
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
#include <algorithm>
#include <vector>
using namespace std;
int segTree[2][3][8000];
int treeSize[2][3];
int charge;
vector<pair<int, int>> v[2][3];  // 성능, 가격

size_t findIndex(const vector<pair<int, int>> &v,
                 const int performance) {  // performance 이상인 첫 인덱스
    size_t l = 0, r = v.size(), mid;
    while (l != r) {
        mid = l + (r - l) / 2;
        v[mid].first < performance ? l = mid + 1 : r = mid;
    }
    return l;
}

void makeTree(const vector<pair<int, int>> &v, const int position,
              const int type) {
    if (v.empty()) {
        segTree[position][type][0] = 9999999;
        return;
    }
    const int n = v.size();
    for (size_t i = 0; i < n; ++i) {
        segTree[position][type][i + n] = v[i].second;
    }
    for (size_t i = n - 1; i != 0; --i) {
        segTree[position][type][i] = min(segTree[position][type][i << 1],
                                         segTree[position][type][i << 1 | 1]);
    }
}

int minPrice(const int performance, const vector<pair<int, int>> &v,
             const int position, const int type) {
    int result = 9999999;
    if (v.empty()) return result;
    size_t firstIndex = findIndex(v, performance);
    if (firstIndex == v.size()) return result;
    size_t l = firstIndex + v.size(), r = 2 * v.size();
    for (; l != r; l >>= 1, r >>= 1) {
        if (l & 1) result = min(result, segTree[position][type][l++]);
        if (r & 1) result = min(result, segTree[position][type][--r]);
    }
    return result;
}

void init(int mCharge) {
    charge = mCharge;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            treeSize[i][j] = 0;
            v[i][j].clear();
            for (int k = 0; k < 8000; k++) {
                segTree[i][j][k] = 0;
            }
        }
    }
}

int stock(int mType, int mPrice, int mPerformance, int mPosition) {
    v[mPosition][mType].push_back({mPerformance, mPrice});
    return v[mPosition][mType].size();
}

Result order(int mBudget) {
    int p[2][3];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            if (treeSize[i][j] != v[i][j].size()) {
                sort(v[i][j].begin(), v[i][j].end());
                makeTree(v[i][j], i, j);
                treeSize[i][j] = v[i][j].size();
            }
        }
    }
    int l = 0, r = 1000000, mid, performance = 0, price = 9999999;
    while (l != r) {
        mid = l + (r - l) / 2;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                p[i][j] = minPrice(mid, v[i][j], i, j);
            }
        }
        const int candi1 = p[0][0] + p[0][1] + p[0][2];
        const int candi2 = p[1][0] + p[1][1] + p[1][2];
        int candi3 = min(p[0][0], p[1][0]) + min(p[0][1], p[1][1]) +
                     min(p[0][2], p[1][2]) + charge;
        int tmpPrice = min(min(candi1, candi2), candi3);
        if (tmpPrice > mBudget) {
            r = mid;
        } else {
            if (performance < mid) {
                performance = mid;
                price = tmpPrice;
            } else if (performance == mid) {
                price = min(price, tmpPrice);
            }
            l = mid + 1;
        }
    }
    Result res = {performance == 0 ? 0 : price, performance};
    return res;
}