#include <iostream>
#include <vector>
using namespace std;
int n, q;
int mintree[200001];
int maxtree[200001];
void update(int i, int x) {
    i += n;
    mintree[i] = maxtree[i] = x;
    while (i >>= 1) {
        mintree[i] = min(mintree[i << 1], mintree[i << 1 | 1]);
        maxtree[i] = max(maxtree[i << 1], maxtree[i << 1 | 1]);
    }
}
void query(int l, int r) {  // [l,r)
    int maxi = 0, mini = 2147483647;
    for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
        if (l & 1) {
            mini = min(mini, mintree[l]);
            maxi = max(maxi, maxtree[l++]);
        }
        if (r & 1) {
            mini = min(mini, mintree[--r]);
            maxi = max(maxi, maxtree[r]);
        }
    }
    cout << maxi - mini << " ";
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        cout << "#" << test_case << " ";
        cin >> n >> q;
        for (int i = 0; i < n; ++i) {
            cin >> mintree[i + n];
            maxtree[i + n] = mintree[i + n];
        }
        for (int i = n - 1; i != 0; --i) {
            mintree[i] = min(mintree[i << 1], mintree[i << 1 | 1]);
            maxtree[i] = max(maxtree[i << 1], maxtree[i << 1 | 1]);
        }
        for (int i = 0; i < q; i++) {
            int qu, a, b;
            cin >> qu >> a >> b;
            if (qu == 0)
                update(a, b);
            else
                query(a, b);
        }
        cout << "\n";
    }
    return 0;
}
