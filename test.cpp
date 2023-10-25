#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    vector<int> myVector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    random_device rd;
    mt19937 g(rd());

    shuffle(myVector.begin(), myVector.end(), g);

    for (int num : myVector)
    {
        std::cout << num << " ";
    }
}