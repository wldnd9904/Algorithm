#include <iostream>
#include <queue>
#include <string>
using namespace std;
struct cmp {
    bool operator()(string a, string b) {
        if (a.size() == b.size())
            return a > b;
        else
            return a.size() > b.size();
    }
};

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        cout << "#" << test_case << "\n";
        int N;
        cin >> N;
        priority_queue<string, vector<string>, cmp> pq;
        for (int i = 0; i < N; i++) {
            string s;
            cin >> s;
            pq.push(s);
        }
        string before;
        while (!pq.empty()) {
            string s = pq.top();
            pq.pop();
            if (before == s) continue;
            cout << s << "\n";
            before = s;
        }
    }
    return 0;
}
