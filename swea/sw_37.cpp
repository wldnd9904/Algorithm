#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int N, P, ans = 0;
        cin >> N >> P;
        vector<int> v(N);
        for (int i = 0; i < N; i++) cin >> v[i];
        // 기저사례: 처음부터 끝까지 다채우고도 남는경우
        if (v[N - 1] - v[0] + 1 - N <= P) {
            ans = N + P;
        } else {
            // v[0]일부터 채울 때 오른쪽 끝 탐색
            int l = 0, r = N, mid = 0;  // 오른쪽 열린 구간
            while (l < r) {
                mid = l + (r - l) / 2;
                (v[mid] - v[0] - mid <= P) ? l = mid + 1 : r = mid;
            }
            int lb = 0, rb = l - 1;
            ans = (rb - lb + 1) + P;
            while (rb != N) {
                if (v[rb] - v[lb] - (rb - lb) <= P) {
                    ans = max(ans, (rb - lb + 1) + P);
                    rb++;
                } else {
                    lb++;
                }
            }
        }
        cout << "#" << test_case << " " << ans << "\n";
    }
    return 0;
}