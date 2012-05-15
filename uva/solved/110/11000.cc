#include <iostream>

using namespace std;

typedef unsigned int uint;

void solve(int n) {
    long long int male, female;
    male = 0; female = 0;
    while(n-- > 0) {
        long long int newmale = male + female + 1;
        long long int newfemale = male;
        male = newmale;
        female = newfemale;
    }
    cout << male << " " << (male+female+1) << endl;
}

int main() {
    int n;
    while(cin >> n && n >= 0)
        solve(n);
    return 0;
}
