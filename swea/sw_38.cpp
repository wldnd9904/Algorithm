#include <iostream>
using namespace std;

long long solve(long long N) {
    if (N == 1) return 1;
    long long l = 0, r = 2, mid;
    while (r * r / 2 < N) r = r * 2;
    while (l < r) {
        mid = l + (r - l) / 2;
        long long cal = (mid * mid + mid) / 2;
        if (cal == N)
            return mid;
        else
            (cal > N) ? r = mid : l = mid + 1;
    }
    return -1;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        long long N;
        cin >> N;
        cout << "#" << test_case << " " << solve(N) << "\n";
    }
    return 0;
}
