#include <iostream>
#include <vector>
using namespace std;

bool isNum(char c) { return c & 0x10; }

bool rec(vector<char>& bt, int i,
         size_t size) {  // 계산된 식이면 true, 아니면 false
    if (isNum(bt[i])) {
        return i * 2 > size;
    }
    bool left = rec(bt, i * 2, size);
    bool right = rec(bt, i * 2 + 1, size);
    return left && right && (!isNum(bt[i]));
}

bool solve(vector<char>& bt, size_t size) { return rec(bt, 1, size); }

int main(void) {
    freopen("input.txt", "r", stdin);
    int T = 10;
    for (int test_case = 1; test_case <= T; test_case++) {
        int N;
        cin >> N;
        getchar();
        vector<char> bt(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            int dummy;
            cin >> dummy;
            getchar();
            string input;
            getline(cin, input);
            bt[i] = input[0];
        }
        cout << "#" << test_case << " " << solve(bt, N) << "\n";
    }
    return 0;
}
