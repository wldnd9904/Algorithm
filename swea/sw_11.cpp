#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int left;
    int right;
};

struct inf {
    int lca;
    bool foundOne;
    int size;
};

inf rec(vector<Node>& node, int cur, int A, int B) {
    if (cur == 0) return {0, false, 0};
    inf l = rec(node, node[cur].left, A, B);
    if (l.lca) return l;
    inf r = rec(node, node[cur].right, A, B);
    if (r.lca) return r;
    inf ret = {(l.foundOne && r.foundOne) ? cur : 0,
               cur == A || cur == B || l.foundOne || r.foundOne,
               l.size + r.size + 1};
    return ret;
}

void solve(vector<Node>& node, int A, int B) {
    inf ret = rec(node, 1, A, B);
    cout << ret.lca << " " << ret.size << "\n";
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int test_case = 1; test_case <= T; test_case++) {
        int N, E, A, B;
        cin >> N >> E >> A >> B;
        vector<Node> node(N + 1, {0, 0});
        for (int i = 0; i < E; i++) {
            int mom, son;
            cin >> mom >> son;
            if (node[mom].left)
                node[mom].right = son;
            else
                node[mom].left = son;
        }
        cout << "#" << test_case << " ";
        solve(node, A, B);
    }
    return 0;
}
