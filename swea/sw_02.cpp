#include <iostream>
using namespace std;

void solve(int N, int M) {
    if ((((1 << N) - 1) & (M)) == (1 << N) - 1)
        cout << " ON\n";
    else
        cout << " OFF\n";
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int T;
    std::cin >> T;  // 테스트 수
    for (int i = 1; i <= T; i++) {
        int N, M;
        cin >> N >> M;
        cout << "#" << i;
        solve(N, M);
    }
    return 0;
}
