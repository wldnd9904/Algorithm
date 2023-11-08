#include <iostream>
#include <vector>
using namespace std;
int n, q;
long long segtree[200001];
void update(int i, int x) {
    segtree[i += n] = (i & 1) ? -x : x;
    while (i >>= 1) {
        segtree[i] = segtree[i << 1] + segtree[i << 1 | 1];
    }
}
void query(int l, int r) {  // [l,r)
    const int originl = l;
    long long result = 0;
    for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
        if (l & 1) result += segtree[l++];
        if (r & 1) result += segtree[--r];
    }
    cout << ((originl & 1) ? -result : result) << " ";
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
            cin >> segtree[i + n];
            if (i & 1) segtree[i + n] *= -1;
        }
        for (int i = n - 1; i != 0; --i) {
            segtree[i] = segtree[i << 1] + segtree[i << 1 | 1];
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
