#include <chrono>
#include <iostream>
int solve(int);
using namespace std;

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int N;
    std::cin >> N;  // 테스트 수
    std::chrono::system_clock::time_point startTime =
        std::chrono::system_clock::now();
    for (int i = 0; i < N; i++) {
        int a;
        std::cin >> a;
        std::cout << solve(a) << std::endl;
    }
    std::chrono::system_clock::time_point endTime =
        std::chrono::system_clock::now();
    std::chrono::milliseconds millisecond =
        std::chrono::duration_cast<std::chrono::milliseconds>(endTime -
                                                              startTime);
    std::cout << "Time Cost: " << millisecond.count() << " ms\n";
    return 0;
}

int solve(int a) {
    cout << "gd" << endl;
    return a;
}