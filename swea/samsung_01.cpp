// 7.17(월)
#include <iostream>
#include <vector>
using namespace std;
int main(void) {
    vector<int> array(8, 1);
    cout << array.capacity() << endl;
    array.push_back(2);  // Reallocation happens
    cout << array.capacity() << endl;
}