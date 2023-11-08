#include <iostream>
#include <string>
using namespace std;

vector<int> getPi(string p) {
    int m = p.size(), j = 0;
    vector<int> pi(m, 0);
    for (int i = 1; i < m; i++) {
        while (j > 0 && p[i] != p[j]) j = pi[j - 1];
        if (p[i] == p[j]) pi[i] = ++j;
    }
    return pi;
}

int kmp(string s, string p) {
    auto pi = getPi(p);
    int ans = 0;
    int n = s.size(), m = p.size(), j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && s[i] != p[j]) j = pi[j - 1];
        if (s[i] == p[j]) {
            if (j == m - 1) {
                ans++;
                j = pi[j];
            } else {
                j++;
            }
        }
    }
    return ans;
}
int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        string B, S;
        cin >> B >> S;
        cout << "#" << test_case << " " << kmp(B, S) << "\n";
    }
    return 0;
}
