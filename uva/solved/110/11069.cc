#include <iostream>

using namespace std;

#define N 76

int dp[N+1][2] = {
    {},
    {0, 1},
    {1, 1},
    {1, 1},
};

int main() {
    for(int n = 4; n <= N; n++) {
        // o*
        dp[n][0] = dp[n-1][1] + dp[n-2][1];
        // *o
        dp[n][1] = dp[n-1][0];
    }
    int given;
    while(cin >> given)
        cout << (dp[given][0]+dp[given][1]) << endl;
    return 0;
}
