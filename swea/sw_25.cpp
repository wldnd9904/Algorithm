#include <limits.h>

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
        int N, A;
        int ans = 0;
        cin >> N >> A;
        priority_queue<int> maxQ;
        priority_queue<int, vector<int>, greater<int>> minQ;
        maxQ.push(INT_MIN);
        minQ.push(INT_MAX);
        for (int i = 0; i < N; i++) {
            int a, b;
            cin >> a >> b;
            if (a > b) swap(a, b);  // a, b
            if (A <= a && A <= b) {
                swap(A, a);  // A, a, b
            } else if (A >= a && A >= b) {
                swap(A, b);  // a, b, A
            }
            if (minQ.top() < A) {  // a, minQ, A, b
                int tmp = minQ.top();
                minQ.pop();
                minQ.push(A);
                A = tmp;
            }
            if (maxQ.top() > A) {  // a, A, maxQ, b
                int tmp = maxQ.top();
                maxQ.pop();
                maxQ.push(A);
                A = tmp;
            }
            if (A <= a && A <= b) {
                swap(A, a);  // A, a, b
            } else if (A >= a && A >= b) {
                swap(A, b);  // a, b, A}
            }
            maxQ.push(a);
            minQ.push(b);
            ans = (ans + A) % 20171109;
        }
        cout << "#" << test_case << " " << ans << "\n";
    }
    return 0;
}
