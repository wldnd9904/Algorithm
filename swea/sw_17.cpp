#include <iostream>
#include <queue>
#define MAX 100002
using namespace std;

int ancestors[MAX][21];
int depth[MAX];
vector<vector<int>> tree;

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a, b);
    for (int i = 20; i >= 0; i--) {
        if (depth[a] <= depth[ancestors[b][i]]) {
            b = ancestors[b][i];
        }
    }
    int ret = a;
    if (a != b) {
        for (int i = 20; i >= 0; i--) {
            if (ancestors[a][i] != ancestors[b][i]) {
                a = ancestors[a][i];
                b = ancestors[b][i];
            }
            ret = ancestors[a][i];
        }
    }
    return ret;
}

long long solve(void) {
    long long ret = 0;
    queue<int> q;
    int lastone = 1;
    q.push(1);
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        for (int child = 0; child < tree[i].size(); child++) {
            q.push(tree[i][child]);
        }
        int l = lca(lastone, i);
        ret += depth[lastone] - depth[l];
        ret += depth[i] - depth[l];
        lastone = i;
    }
    return ret;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int N;
        cin >> N;
        tree.clear();
        tree.resize(N + 2);
        memset(ancestors, 0, sizeof(int) * MAX * 21);
        memset(depth, 0, sizeof(int) * MAX);
        depth[1] = 0;
        ancestors[1][0] = 1;
        for (int i = 2; i <= N; i++) {
            int p;
            cin >> p;
            tree[p].push_back(i);
            depth[i] = depth[p] + 1;
            ancestors[i][0] = p;
        }
        for (int i = 2; i <= N; i++) {
            for (int j = 1; j <= 20; j++) {
                int tmp = ancestors[i][j - 1];
                ancestors[i][j] = ancestors[tmp][j - 1];
            }
        }
        cout << "#" << test_case << " " << solve() << "\n";
    }
    return 0;
}
