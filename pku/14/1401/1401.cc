#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int c;
    cin >> c;
    while(c-- > 0) {
        int n;
        cin >> n;
        int twos = 0, fives = 0;
        for(long long int t = 2; t <= n; t *= 2)
            twos += n/t;
        for(long long int t = 5; t <= n; t *= 5)
            fives += n/t;
        cout << min(twos, fives) << endl;
    }
    return 0;
}

