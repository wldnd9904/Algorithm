#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> hasher;
const int DIV = (1 << 30) - 1;
int H, W, N, M;
long long int makeHasher(int h, int w) {
    if (h == H || w == W) return 0;
    int &ret = hasher[h][w];
    if (ret != -1)
        return ret;
    else
        return ret = max((makeHasher(h + 1, w) * 5) & DIV,
                         (makeHasher(h, w + 1) * 3) & DIV);
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int hash = 0;
        cin >> H >> W >> N >> M;
        vector<vector<bool>> big(N, vector<bool>(M, false));
        hasher = vector<vector<int>>(H, vector<int>(W, -1));
        vector<vector<int>> hHash(N, vector<int>(M - W + 1, 0));
        vector<vector<int>> vHash(N - H + 1, vector<int>(M - W + 1, 0));
        hasher[H - 1][W - 1] = 1;
        makeHasher(0, 0);
        for (int i = 0; i < H; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < W; j++) {
                if (s[j] == 'o') {
                    hash += hasher[i][j];
                }
            }
        }
        // cout << hash << endl;
        for (int y = 0; y < N; y++) {
            string s;
            cin >> s;
            for (int x = 0; x < M; x++) {
                if (s[x] == 'o') {
                    big[y][x] = true;
                }
            }
        }
        for (int i = 0; i < N; i++) {
            long long tmp = 0;
            for (int j = 0; j < W; j++) {
                tmp = (tmp * 3) & DIV;
                if (big[i][j]) tmp = (tmp + 1) & DIV;
            }
            hHash[i][0] = tmp;
            for (int j = W; j < M; j++) {
                if (big[i][j - W]) tmp -= hasher[H - 1][0];
                tmp = (tmp * 3) & DIV;
                if (big[i][j]) tmp = (tmp + 1) & DIV;
                hHash[i][j - W + 1] = tmp;
            }
        }
        for (int j = 0; j < N; j++) {
            long long tmp = 0;
            for (int i = 0; i < H; i++) {
                tmp = (tmp * 5) & DIV;
                tmp = (tmp + hHash[i][j]) & DIV;
            }
            vHash[0][j] = tmp;
            for (int i = H; i < N; i++) {
                long long tmp2 =
                    (tmp - ((long long)hasher[0][W - 1] * hHash[i - H][j])) &
                    DIV;
                if (tmp2 < 0) tmp2 += tmp = (tmp * 5) & DIV;
                tmp = (tmp + hHash[i][j]) & DIV;
                vHash[i - H + 1][j] = tmp;
            }
        }
        int ans = 0;
        for (int i = 0; i < N - H + 1; i++) {
            for (int j = 0; j < M - W + 1; j++) {
                // cout << vHash[i][j] << " ";
                if (hash == vHash[i][j]) ans++;
            }
            // cout << endl;
        }
        cout << "#" << test_case << " " << ans << "\n";
    }
    return 0;
}
