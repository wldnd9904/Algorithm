#include <iostream>
#include <vector>
using namespace std;
#define MAX 1000
int N;
double E;
int parent[MAX];
pair<int, int> island[MAX];
struct bri {
    int islandA, islandB;
    double cost;
};
double cost(int a, int b) {
    return E * (pow(island[a].first - island[b].first, 2) +
                pow(island[a].second - island[b].second, 2));
}
bool cmp(bri a, bri b) { return a.cost < b.cost; }
int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            island[i] = {x, 0};
            parent[i] = i;
        }
        for (int i = 0; i < N; i++) {
            int y;
            cin >> y;
            island[i].second = y;
        }
        cin >> E;
        vector<bri> v;
        for (int i = 0; i < N - 1; i++) {
            for (int j = i + 1; j < N; j++) {
                v.push_back({i, j, cost(i, j)});
            }
        }
        sort(v.begin(), v.end(), cmp);
        int edges = 0;
        double ret = 0;
        for (auto it = v.begin(); it != v.end(); it++) {
            int isA = (*it).islandA, isB = (*it).islandB;
            int paA = isA, paB = isB;
            while (parent[paA] != paA) paA = parent[paA];
            while (parent[paB] != paB) paB = parent[paB];
            if (paA != paB) {
                parent[paB] = paA;
                ret += (*it).cost;
                edges++;
            }
            if (edges == N - 1) break;
        }
        long long ans = (long long)floor(ret + 0.5);
        cout << "#" << test_case << " " << ans << "\n";
    }
    return 0;
}
