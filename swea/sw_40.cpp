#include <iostream>
#include <vector>
using namespace std;
int s[100001];
int e[100001];
int l[100001];
int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    int T;
    std::cin >> T;  // 테스트 수
    for (int test_case = 1; test_case <= T; test_case++) {
        int N, left = 0, right;
        int L, ans = 0, time = 0;
        long long sum = 0;
        cin >> L >> N;
        for (int i = 0; i < N; i++) {
            cin >> s[i] >> e[i];
            l[i] = e[i] - s[i];
        }
        int tmpl = 0, tmpr = N, tmpmid;
        while (tmpl < tmpr) {
            tmpmid = tmpl + (tmpr - tmpl) / 2;
            e[tmpmid] <= s[0] + L ? tmpl = tmpmid + 1 : tmpr = tmpmid;
        }
        right = tmpl - 1;
        for (int i = 0; i <= right; i++) time += l[i];
        while (right <= N - 1) {
            // 1. left부터 L에 핏한 공간 찾기
            while (right < N - 1 && e[right + 1] <= s[left] + L)
                time += l[++right];
            // 2. 여유공간 구하기
            const int leftover = s[left] + L - e[right];
            // 3. 왼쪽 이나 오른족 중 갭 작은거 선택해서 스팬
            int leftspan = 0;
            if (left > 0 && leftover - s[left] + e[left - 1] > 0) {
                leftspan = min(leftover - s[left] + e[left - 1], l[left - 1]);
            }
            int rightspan = 0;
            if (right < N - 1 && leftover - s[right + 1] + e[right] > 0) {
                rightspan =
                    min(leftover - s[right + 1] + e[right], l[right + 1]);
            }

            ans = max(ans, time + max(leftspan, rightspan));
            if (left < right)
                time -= l[left++];
            else {
                right = ++left;
                time = l[left];
                ans = max(ans, time);
            }
            if (ans >= L) break;
        }

        cout << "#" << test_case << " " << min(ans, L) << "\n";
    }
    return 0;
}
