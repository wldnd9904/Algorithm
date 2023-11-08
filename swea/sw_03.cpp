#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int MOD = 1000000007;
int solve(const string& input) {
    const int len = input.length();
    vector<vector<int>> dp(len, vector<int>(16, 0));
    // 첫날엔 A랑 첫날 책임자 필참
    const int fday = ((1 << (input[0] - 'A')) | 1);
    for (int i = 1; i <= 15; i++) {
        if ((fday & i) == fday) dp[0][i] = 1;
    }
    // 1일차부턴 동적계획법
    for (int i = 1; i < len; i++) {
        const int responsible = 1 << (input[i] - 'A');
        for (int tday = 1; tday <= 15; tday++) {
            int sum = 0;
            for (int yday = 1; yday <= 15; yday++) {
                if ((tday & responsible) && (yday & tday)) {
                    sum = (sum + dp[i - 1][yday]) % MOD;
                }
            }
            dp[i][tday] = sum;
        }
    }
    int ret = 0;
    for (int i = 1; i <= 15; i++) ret = (ret + dp[len - 1][i]) % MOD;
    return ret;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int T;
    std::cin >> T;  // 테스트 수
    for (int i = 1; i <= T; i++) {
        string input;
        cin >> input;
        cout << "#" << i << " " << solve(input) << "\n";
    }
    return 0;
}