#include <iostream>
#include <queue>
#include <string>
using namespace std;
int map[100][100];
int tra[100][100];
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
int solve(void) { return 0; }
struct point {
    int x;
    int y;
    int cost;
};
struct cmp {
    bool operator()(point a, point b) { return a.cost > b.cost; }
};
int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int N;
        cin >> N;
        for (int i = 0; i < N; i++) {
            string input;
            cin >> input;
            for (int j = 0; j < N; j++) {
                map[i][j] = input[j] - '0';
                tra[i][j] = INT_MAX;
            }
        }
        priority_queue<point, vector<point>, cmp> q;
        point tmp;
        tmp.cost = map[0][0];
        tmp.x = 0;
        tmp.y = 0;
        q.push(tmp);
        cout << "#" << test_case << " ";
        while (!q.empty()) {
            point pt = q.top();
            tra[pt.x][pt.y] = pt.cost + map[pt.x][pt.y];
            q.pop();
            if (pt.x == N - 1 && pt.y == N - 1) {
                cout << pt.cost + map[N - 1][N - 1] << "\n";
                break;
            }
            point tmp;
            tmp.x = pt.x;
            tmp.y = pt.y;
            tmp.cost = pt.cost + map[tmp.x][tmp.y];
            for (int i = 0; i < 4; i++) {
                tmp.x += dx[i];
                tmp.y += dy[i];
                if (tmp.x >= 0 && tmp.x < N && tmp.y >= 0 && tmp.y < N &&
                    map[tmp.x][tmp.y] + tmp.cost < tra[tmp.x][tmp.y]) {
                    q.push(tmp);
                }
                tmp.x -= dx[i];
                tmp.y -= dy[i];
            }
        }
    }
    return 0;
}
