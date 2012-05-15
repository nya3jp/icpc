#include <iostream>
#include <cstdio>

using namespace std;

void solve(int n) {
    if (n == 1) {
        printf("((A0|B0)|(A0|B0))");
    }
    else {
        printf("((A%d|B%d)|(", n-1, n-1);
        solve(n-1);
        printf("|((A%d|A%d)|(B%d|B%d))))", n-1, n-1, n-1, n-1);
    }
}

int main() {
    int n;
    cin >> n;
    solve(n);
    printf("\n");
    return 0;
}
