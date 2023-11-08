#include <iostream>
#include <vector>
using namespace std;

void rec(vector<char>& bt, int i, size_t size) {
    if (i > size) return;
    rec(bt, i * 2, size);
    cout << bt[i];
    rec(bt, i * 2 + 1, size);
}

void solve(vector<char>& bt, size_t size) { rec(bt, 1, size); }

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
        cout << "#" << test_case << " ";
        solve(bt, N);
        cout << "\n";
    }
    return 0;
}
