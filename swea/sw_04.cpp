#include <iostream>

using namespace std;

struct Node {
    Node* prev;
    int value;
    Node* next;
};
Node* new_node(int value) {
    Node* node = new Node;
    node->value = value;
    node->prev = nullptr;
    node->next = nullptr;
    return node;
}
void print(Node head) {
    Node* cur = head.next;
    for (int i = 0; i < 10; i++) {
        cout << cur->value << " ";
        cur = cur->next;
    }
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    for (int i = 1; i <= 10; i++) {
        int N, M;
        cin >> N;  // 원본 암호문 뭉치 속 암호문 개수
        Node head = {nullptr, 0, nullptr};
        Node* cur = &head;
        for (int j = 0; j < N; j++) {  // 원본 암호문 뭉치
            int value;
            cin >> value;
            Node* node = new_node(value);
            node->prev = cur;
            cur->next = node;
            cur = cur->next;
        }
        cur->next = &head;
        head.prev = cur;

        cin >> M;                      // 명령어의 개수
        for (int j = 0; j < M; j++) {  // 명령어
            char command;
            size_t x, y;
            cin >> command;
            switch (command) {
                case 'I': {
                    cin >> x;
                    cur = &head;
                    for (int k = 0; k < x; k++) cur = cur->next;
                    Node* next = cur->next;
                    cin >> y;
                    for (int k = 0; k < y; k++) {
                        int value;
                        cin >> value;
                        Node* node = new_node(value);
                        node->prev = cur;
                        cur->next = node;
                        cur = cur->next;
                    }
                    cur->next = next;
                    next->prev = cur;
                    break;
                }

                case 'D': {
                    cin >> x >> y;
                    cur = &head;
                    for (int k = 0; k < x; k++) cur = cur->next;
                    Node* next = cur->next;
                    for (int k = 0; k < y; k++) next = next->next;
                    cur->next = next;
                    next->prev = cur;
                    break;
                }

                case 'A': {
                    cur = head.prev;
                    cin >> y;
                    for (int k = 0; k < y; k++) {
                        int value;
                        cin >> value;
                        Node* node = new_node(value);
                        node->prev = cur;
                        cur->next = node;
                        cur = cur->next;
                    }
                    cur->next = &head;
                    head.prev = cur;
                    break;
                }
            }
        }
        cout << "#" << i << " ";
        print(head);
        cout << "\n";
    }
    return 0;
}
