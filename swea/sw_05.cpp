#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
};

Node* new_node(int value) {
    Node* node = new Node;
    node->next = nullptr;
    node->value = value;
    return node;
}

void ins(Node* head, size_t num, int value) {
    Node* cur = head;
    while (num--) {
        cur = cur->next;
    }
    Node* node = new_node(value);
    node->next = cur->next;
    cur->next = node;
}

void del(Node* head, size_t num) {
    Node* cur = head;
    while (num--) {
        cur = cur->next;
    }
    cur->next = cur->next->next;
}

void cha(Node* head, size_t num, int value) {
    Node* cur = head->next;
    while (num--) {
        cur = cur->next;
    }
    cur->value = value;
}

int pri(Node* head, size_t num) {
    Node* cur = head->next;
    if (cur == nullptr) return -1;
    while (num--) {
        if (cur->next == nullptr) return -1;
        cur = cur->next;
    }
    return cur->value;
}
void print(Node* head) {
    for (int i = 0; i < 10; i++) {
        cout << i << "\t";
    }
    cout << "\n";
    Node* cur = head->next;
    for (int i = 0; i < 10; i++) {
        cout << cur->value << "\t";
        cur = cur->next;
        if (cur == nullptr) return;
    }
    cout << "\n";
}
int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int N, M, L;
        cin >> N >> M >> L;
        Node head = {0, nullptr};
        Node* cur = &head;
        for (int i = 0; i < N; i++) {
            int value;
            cin >> value;
            Node* node = new_node(value);
            cur->next = node;
            cur = cur->next;
        }
        // print(&head);
        for (int i = 0; i < M; i++) {
            int x, y;
            char command;
            cin >> command;
            switch (command) {
                case 'I': {
                    cin >> x >> y;
                    ins(&head, x, y);
                    // print(&head);
                    break;
                }
                case 'D': {
                    cin >> x;
                    del(&head, x);
                    // print(&head);
                    break;
                }
                case 'C': {
                    cin >> x >> y;
                    cha(&head, x, y);
                    // print(&head);
                    break;
                }
            }
        }
        cout << "#" << test_case << " " << pri(&head, L) << "\n";
    }
    return 0;
}
