#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <limits>
#include <vector>

using namespace std;

int main() {

    int nCases;
    cin >> nCases >> ws;

    for(int iCase = 0; iCase < nCases; iCase++) {

        string line;
        getline(cin, line);
        istringstream is(line);
        vector<int> u;
        copy(istream_iterator<int>(is), istream_iterator<int>(), back_inserter(u));

        const int n = u.size();
        int v[10];
        copy(u.begin(), u.end(), v);

            int from = max(1, (n+1)/2-1);
            int to = n-from+1;
        int m = numeric_limits<int>::max();
        do {
            for(int i = from; i < to; i++) {
                if ((v[0] != 0 || i == 1) && (v[i] != 0 || i == n-1)) {
                    int a = 0;
                    for(int j = 0; j < i; j++)
                        a = a*10 + v[j];
                    int b = 0;
                    for(int j = i; j < n; j++)
                        b = b*10 + v[j];
                    int d = a - b;
                    if (d < 0) d = -d;
                    m = min(m, d);
                }
            }
        } while(next_permutation(v, v+n));

        cout << m << endl;

    }

    return 0;
}

