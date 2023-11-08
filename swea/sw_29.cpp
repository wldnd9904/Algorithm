#include <iostream>
#include <string>
using namespace std;

size_t djb2(string str) {
    size_t hash = 5381;
    for (auto it = str.begin(); it != str.end(); it++) {
        hash = (hash << 5) + hash + *it;
    }
    return hash % 100000;
}
struct Node {
    string data;
    Node* next;
};

Node* nodes[100000];

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int N, M;
        cin >> N >> M;
        for (int i = 0; i < 100000; i++) {
            nodes[i] = nullptr;
        }
        for (int i = 0; i < N; i++) {
            string s;
            cin >> s;
            size_t hash = djb2(s);
            Node* node = new Node;
            node->data = s;
            node->next = nullptr;
            if (nodes[hash] == nullptr)
                nodes[hash] = node;
            else {
                Node* cur = nodes[hash];
                while (cur->next != nullptr) cur = cur->next;
                cur->next = node;
            }
        }
        int ans = 0;
        for (int i = 0; i < M; i++) {
            string s;
            cin >> s;
            size_t hash = djb2(s);
            if (nodes[hash] == nullptr)
                continue;
            else {
                Node* cur = nodes[hash];
                while (cur != nullptr) {
                    if (cur->data == s) {
                        ans++;
                        break;
                    }
                    cur = cur->next;
                }
            }
        }
        cout << "#" << test_case << " " << ans << "\n";
    }
    return 0;
}
