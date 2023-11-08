#include <iostream>
#include <queue>
#define MAX 100001
using namespace std;

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int N;
        cin >> N;
        priority_queue<int> q;
        cout << "#" << test_case << " ";
        for (int i = 0; i < N; i++) {
            int cmd;
            cin >> cmd;
            if (cmd == 1) {
                int x;
                cin >> x;
                q.push(x);
            } else {
                if (q.empty())
                    cout << -1 << " ";
                else {
                    cout << q.top() << " ";
                    q.pop();
                }
            }
        }
        cout << "\n";
    }
    return 0;
}
