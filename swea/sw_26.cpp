#include <iostream>
#include <queue>
using namespace std;

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int N, K;
        cin >> N;
        vector<int> v(N);
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            pq;
        for (int i = 0; i < N; i++) {
            cin >> v[i];
        }
        cin >> K;

        pq.push({0, K});
        while (pq.top().second != 0) {
            pair<int, int> tmp = pq.top();
            pq.pop();
            pq.push({tmp.first + tmp.second, 0});
            for (int i = 0; i < N; i++) {
                pq.push({tmp.first + tmp.second % v[i], tmp.second / v[i]});
            }
        }
        int ans = pq.top().first;
        cout << "#" << test_case << " " << ans << "\n";
    }
    return 0;
}
