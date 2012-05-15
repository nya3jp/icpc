#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_PRIME 1000000

bool isprime[MAX_PRIME+1];

int main() {

    isprime[0] = isprime[1] = false;
    fill(isprime+2, isprime+MAX_PRIME+1, true);
    for(int i = 2; i <= MAX_PRIME; i++) {
        if (isprime[i]) {
            if ((long long int)i*i <= MAX_PRIME)
                for(int j = i*i; j <= MAX_PRIME; j += i)
                    isprime[j] = false;
            //cout << i << endl;
        }
    }

    int a, d, n;
    while(cin >> a >> d >> n && !(a == 0 && d == 0 && n == 0)) {

        int result = -1;
        for(int k = 0; n > 0; k++) {
            int b = a + d*k;
            if (isprime[b]) {
                result = b;
                n--;
            }
        }

        cout << result << endl;

    }

    return 0;
}

