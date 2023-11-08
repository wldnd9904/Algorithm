#include <iostream>
using namespace std;

int V[100], C[100];  // 부피, 가치
int N, K;

int solve(void) {
    int dp[101][1001];
    for (int i = 0; i <= N; i++) {
        for (int v = 0; v <= K; v++) {
            dp[i][v] = 0;
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int v = 0; v <= K; v++) {
            dp[i][v] = dp[i - 1][v];
            if (v - V[i - 1] >= 0) {
                dp[i][v] = max(dp[i][v], dp[i - 1][v - V[i - 1]] + C[i - 1]);
            }
        }
    }

    int maxC = 0;
    for (int v = 0; v <= K; v++) {
        maxC = max(maxC, dp[N][v]);
    }
    return maxC;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        cin >> N >> K;
        for (int i = 0; i < N; i++) {
            cin >> V[i] >> C[i];
        }
        cout << "#" << test_case << " " << solve() << "\n";
    }
    return 0;
}