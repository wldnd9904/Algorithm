#include <iostream>
#include <string>
#define MAX 1001
using namespace std;
int solve(string& A, string& B) {
    int dp[MAX][MAX];

    for (int i = 0; i <= A.size(); i++) {
        for (int j = 0; j <= B.size(); j++) {
            dp[i][j] = 0;
        }
    }
    for (int i = 1; i <= A.size(); i++) {
        for (int j = 1; j <= B.size(); j++) {
            if (A[i - 1] == B[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
        }
    }
    return dp[A.size()][B.size()];
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        string A, B;
        cin >> A >> B;
        cout << "#" << test_case << " " << solve(A, B) << "\n";
    }
    return 0;
}
