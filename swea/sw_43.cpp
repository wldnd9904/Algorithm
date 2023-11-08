#include <iostream>
#include <string>
#define MAX 26
using namespace std;
struct Trie {
    bool isTerminal = false;
    Trie* child[MAX] = {
        nullptr,
    };
};
int cnt, target;

void dfs(Trie* cur, int pivot, string s) {
    if (cnt == target) return;
    if (cur->isTerminal) {
        if (++cnt == target) cout << s << "\n";
    }
    for (int i = 0; i < pivot; i++) {
        if (cur->child[i] != nullptr)
            dfs(cur->child[i], i, string(s + (char)('a' + i)));
    }
    for (int i = pivot; i < MAX; i++) {
        if (cur->child[i] != nullptr)
            dfs(cur->child[i], i, string(s + (char)('a' + i)));
    }
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        string s;
        cnt = 0;
        Trie* trie = new Trie;
        cin >> target >> s;
        for (int i = 0; i < s.size(); i++) {
            cnt = 0;
            Trie* cur = trie;
            for (int j = i; j < s.size(); j++) {
                if (cur->child[s[j] - 'a'] == nullptr) {
                    Trie* tmp = new Trie;
                    cur->child[s[j] - 'a'] = tmp;
                }
                cur = cur->child[s[j] - 'a'];
                cur->isTerminal = true;
            }
        }
        cout << "#" << test_case << " ";
        dfs(trie, 0, string());
    }
    return 0;
}
