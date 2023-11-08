#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> map;
vector<pair<int, int>> cores;
int N, satisfied, satisfiedCnt, line, lineCnt;
int cnt = 0;
const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool isBorder(int x, int y) {
    return (x == 0 || y == 0 || x == N - 1 || y == N - 1);
}
bool isInside(int x, int y) {
    return (x >= 0 && y >= 0 && x <= N - 1 && y <= N - 1);
}

int check(int x, int y, int direction) {
    int dis = 0;
    x += dir[direction][0];
    y += dir[direction][1];
    dis++;
    while (isInside(x, y)) {
        if (map[x][y] != 0) return 0;
        if (isBorder(x, y)) return dis;
        x += dir[direction][0];
        y += dir[direction][1];
        dis++;
    }
    return 0;  // 맵 나가는것도 펄스(가장자리는 이미체크됨)
}

void drawLine(int x, int y, int direction, int tobeFilled) {
    x += dir[direction][0];
    y += dir[direction][1];
    while (isInside(x, y)) {
        map[x][y] = tobeFilled;
        x += dir[direction][0];
        y += dir[direction][1];
    }
}

void dfs(int core) {
    if (core == cores.size()) {
        cnt++;
        if (satisfiedCnt > satisfied) {
            satisfied = satisfiedCnt;
            line = lineCnt;
        } else if (satisfiedCnt == satisfied && line > lineCnt) {
            line = lineCnt;
        }
        return;
    }
    // dfs
    for (int i = 0; i < 4; i++) {
        int dis = check(cores[core].first, cores[core].second, i);
        if (dis > 0) {
            drawLine(cores[core].first, cores[core].second, i, 2);
            satisfiedCnt++;
            lineCnt += dis;
            dfs(core + 1);
            drawLine(cores[core].first, cores[core].second, i, 0);
            satisfiedCnt--;
            lineCnt -= dis;
        }
    }
    dfs(core + 1);
}

int solve() {
    dfs(0);
    return line;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        cin >> N;  // 멕시노스 크기
        map = vector<vector<int>>(N, vector<int>(N, 0));
        cores.clear();
        satisfied = 0;
        satisfiedCnt = 0;
        line = 999999;
        lineCnt = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int input;
                cin >> input;
                if (input) {
                    map[i][j] = input;
                    if (!isBorder(i, j)) {
                        cores.push_back({i, j});
                    }
                }
            }
        }
        cout << "#" << test_case << " " << solve() << "\n";
    }
    return 0;
}