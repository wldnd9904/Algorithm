#include <iostream>
#include <vector>
using namespace std;

struct Node {
    bool isNum;
    int data;
    int left;
    int right;
};

bool isNum(char c) { return c & 0x10; }

double rec(vector<Node>& node, int i) {
    if (node[i].isNum) return node[i].data;
    double left, right;
    left = rec(node, node[i].left);
    right = rec(node, node[i].right);
    switch (node[i].data) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
    }
    return 0;
}

int solve(vector<Node>& node_pool) { return rec(node_pool, 1); }

int main(void) {
    // freopen("input.txt", "r", stdin);
    int T = 10;
    for (int test_case = 1; test_case <= T; test_case++) {
        int N;
        cin >> N;
        vector<Node> node_pool(N + 1, {false, 0, 0, 0});
        for (int i = 1; i <= N; i++) {
            int no;
            char tmp;
            cin >> no;
            getchar();
            tmp = getchar();
            if (isNum(tmp)) {
                int data;
                node_pool[no].isNum = true;
                ungetc(tmp, stdin);
                cin >> data;
                node_pool[no].data = data;
            } else {
                int left, right;
                cin >> left >> right;
                node_pool[no].data = tmp;
                node_pool[no].left = left;
                node_pool[no].right = right;
            }
        }
        cout << "#" << test_case << " " << solve(node_pool) << "\n";
    }
    return 0;
}
