#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int z1z2;
int dst(int x1, int x2) { return abs(x1 - x2); }

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int N, M;  // 소 N마리, 말 M마리
        int c1, c2;
        cin >> N >> M;
        vector<int> so(N), mal(M);
        cin >> c1 >> c2;
        z1z2 = abs(c1 - c2);
        for (int i = 0; i < N; i++) {
            cin >> so[i];
        }
        for (int i = 0; i < M; i++) {
            cin >> mal[i];
        }
        sort(so.begin(), so.end());
        sort(mal.begin(), mal.end());

        int mindst = 2147483647, cnt = 0;
        for (int soX : so) {
            int l = 0, r = M, mid;
            while (l != r) {
                mid = l + (r - l) / 2;
                int dist = dst(soX, mal[mid]);
                if (dist == mindst)
                    cnt++;
                else if (dist < mindst) {
                    mindst = dist;
                    cnt = 1;
                }
                (mal[mid] > soX) ? r = mid : l = mid + 1;
            }
        }

        cout << "#" << test_case << " " << mindst + z1z2 << " " << cnt << "\n";
    }
    return 0;
}
