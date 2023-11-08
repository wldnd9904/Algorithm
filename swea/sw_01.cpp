#include <chrono>
#include <iostream>
#include <queue>
using namespace std;

int solve(int N) {
    int a = 0, i = 1;
    while (a != 1023) {
        int sheep = N * i;
        while (sheep != 0) {
            a |= 1 << (sheep % 10);
            sheep /= 10;
        }
        i++;
    }
    return N * (i - 1);
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;  // 테스트 수
    vector<int> Ns;
    for (int i = 0; i < T; i++) {
        int N;
        cin >> N;
        Ns.push_back(N);
    }
    for (int i = 0; i < T; i++) {
        cout << "#" << i + 1 << " " << solve(Ns[i]) << "\n";
    }
    return 0;
}
