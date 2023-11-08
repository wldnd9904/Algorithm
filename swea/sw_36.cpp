#include <iostream>
using namespace std;
long long rec(int C, int K) {
    if (K == 0) return 1;
    if (K == 1) {
        return 2 % C;
    } else {
        long long result = rec(C, K / 2);
        if (K % 2 == 0)
            return (result * result) % C;
        else
            return ((result * result) % C) * 2 % C;
    }
}
int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int A, B, K, C;
        cin >> A >> B >> K;
        C = A + B;
        int ret = ((long long)A * rec(C, K) % C);
        cout << "#" << test_case << " " << min(ret, C - ret) << "\n";
    }
    return 0;
}
