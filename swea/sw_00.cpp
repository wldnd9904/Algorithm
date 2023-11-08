#include <iostream>
using namespace std;

int solve(void) { return 0; }

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int N, M;
        cin >> N >> M;
        cout << "#" << test_case << " " << solve() << "\n";
    }
    return 0;
}
