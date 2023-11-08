#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define MAX_CITY 50001
#define MAX_EDGE 200001
int N, M;
int parent[MAX_CITY];

struct edge {
    int A, B, cost;
};

struct cmp {
    bool operator()(edge a, edge b) { return a.cost > b.cost; }
};

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        cin >> N >> M;
        priority_queue<edge, vector<edge>, cmp> v;
        for (int i = 0; i <= N; i++) {
            parent[i] = i;
        }
        for (int i = 0; i < M; i++) {
            edge tmp;
            cin >> tmp.A >> tmp.B >> tmp.cost;
            v.push(tmp);
        }
        int edges = 0;
        long long ret = 0;
        while (!v.empty()) {
            edge it = v.top();
            v.pop();
            int isA = it.A, isB = it.B;
            int paA = isA, paB = isB;
            while (parent[paA] != paA) paA = parent[paA];
            while (parent[paB] != paB) paB = parent[paB];
            if (paA != paB) {
                parent[paB] = paA;
                parent[isB] = paA;
                ret += it.cost;
                edges++;
            }
            if (edges == N - 1) break;
        }
        cout << "#" << test_case << " " << ret << "\n";
    }
    return 0;
}
