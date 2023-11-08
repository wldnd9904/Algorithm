#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
int dp[3002][102][102][2];
int N, M;
vector<int> v1, v2;
int rec_dp(int n, int m, int mskipped, int skipped) {
    int &ret = dp[n][m][mskipped][skipped];
    if (ret != -1) return ret;
    int ret1 = 0, ret2 = 0, ret3 = 0, ret4 = 0;
    if (!skipped) {  // 직전에 가져갔다면
        if (n < N) ret1 = rec_dp(n + 1, m, mskipped, 1);  // a를 버리는 경우
        if (m + mskipped < M)
            ret2 = rec_dp(n, m, mskipped + 1, 1);  // b를 버리는 경우
    } else {  // 직전에 안 가져갔다면
        if (n < N) {
            ret1 = rec_dp(n + 1, m, mskipped, 0) + v1[n];  // a를 가져가는 경우
            ret2 = rec_dp(n + 1, m, mskipped, 1);  // a를 버리는 경우
        }
        if (m + mskipped < M) {
            ret3 = rec_dp(n, m + 1, mskipped, 0) + v2[m];  // b를 가져가는 경우
            ret4 = rec_dp(n, m, mskipped + 1, 1);  // b를 버리는 경우
        }
    }
    return ret = max(max(max(ret1, ret2), ret3), ret4);
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        cin >> N;
        v1 = vector<int>(N);
        for (int i = 0; i < N; i++) {
            cin >> v1[i];
        }
        cin >> M;
        v2 = vector<int>(M);
        for (int i = 0; i < M; i++) {
            cin >> v2[i];
        }
        sort(v2.begin(), v2.end(), greater<int>());
        memset(dp, -1, sizeof(dp));
        cout << "#" << test_case << " " << rec_dp(0, 0, 0, 1) << "\n";
    }
    return 0;
}
