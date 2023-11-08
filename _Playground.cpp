#include <iostream>
#include <vector>
using namespace std;
const int MIN = numeric_limits<int>::min();
const int MAX = numeric_limits<int>::max();
int main(void)
{
    cout << MAX;
}

int inefficientMaxSum(const vector<int> &A)
{
    int N = A.size(), ret = MIN;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int sum = 0;
        }
    }
}