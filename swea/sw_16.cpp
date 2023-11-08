#include <iostream>
#include <vector>
using namespace std;
const int dx[9] = {0, 0, 0, 1, 1, 1, -1, -1, -1};
const int dy[9] = {0, -1, 1, 0, -1, 1, 0, -1, 1};
vector<vector<int>> map;
vector<vector<int>> map2;
vector<vector<bool>> map3;
int N;

int isInside(int x, int y) { return (x >= 0 && y >= 0 && x < N && y < N); }
void fill(int x, int y) {
    map[x][y]++;
    for (int dir = 0; dir < 9; dir++) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (isInside(nx, ny)) {
            if (map[nx][ny] == 0) fill(nx, ny);
            if (map2[nx][ny] != 0) map[nx][ny]++;
        }
    }
}
int solve(void) {
    int ret = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 0) {
                ret++;
                fill(i, j);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!map3[i][j] && map2[i][j] > 0 && map2[i][j] == map[i][j]) ret++;
        }
    }
    return ret;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        cin >> N;
        map = vector<vector<int>>(N, vector<int>(N, 0));
        map3 = vector<vector<bool>>(N, vector<bool>(N, false));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                char input;
                cin >> input;
                if (input == '*') {
                    map3[i][j] = true;
                    for (int dir = 0; dir < 9; dir++) {
                        int x = i + dx[dir], y = j + dy[dir];
                        if (isInside(x, y)) map[x][y]++;
                    }
                }
            }
        }
        map2 = vector<vector<int>>(map);
        cout << "#" << test_case << " " << solve() << "\n";
    }
    return 0;
}
