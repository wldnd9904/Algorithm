#include <iostream>
#include <vector>
using namespace std;
vector<long long> v;
#define __LONG_LONG_MAX__ 9223372036854775807LL
bool makeable(long long r, long long m) {
    if (r == 0) return true;
    for (auto it = v.begin(); it != v.end(); it++) {
        m -= (*it) / r;
        if (m <= 0) return true;
    }
    return false;
}
long long solve(long long M) {
    long long l, r = 1, mid;
    while (makeable(r, M) && r < __LONG_LONG_MAX__) r *= 2;
    l = r / 2;
    while (l < r) {
        mid = l + (r - l) / 2;
        makeable(mid, M) ? l = mid + 1 : r = mid;
    }
    return max((long long)0, l - 1);
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        long long N, M;
        cin >> N >> M;
        v = vector<long long>(N);
        for (int i = 0; i < N; i++) {
            cin >> v[i];
        }
        cout << "#" << test_case << " " << solve(M) << "\n";
    }
    return 0;
}
