#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

const int NINF = -100000000;

#define N 100
#define M 1000
#define OFFSET (N*M)

int table[N*M*2+1];

int main() {

    int n;
    cin >> n;

    fill(table, table+(N*M*2+1), NINF);
    table[OFFSET] = 0;
    int lower = OFFSET;
    int upper = OFFSET;

    while(n-- > 0) {

        int s, f;
        cin >> s >> f;

        if (s >= 0) {
            upper += s;
            for(int i = upper; i >= lower; i--) {
                if (table[i-s] != NINF)
                    table[i] = max(table[i], table[i-s]+f);
            }
        }
        else {
            lower += s;
            for(int i = lower; i <= upper; i++) {
                if (table[i-s] != NINF)
                    table[i] = max(table[i], table[i-s]+f);
            }
        }

    }

    int best = -1;
    for(int i = OFFSET; i <= upper; i++) {
        if (table[i] >= 0)
            best = max(best, i-OFFSET + table[i]);
    }
    cout << best << endl;

    return 0;
}



int main2() {

    int n;
    cin >> n;

    map<int,int> m;
    m[0] = 0;

    for(int i = 0; i < n; i++) {

        int s, f;
        cin >> s >> f;

        if (s >= 0) {
            for(map<int,int>::reverse_iterator it = m.rbegin(); it != m.rend(); ++it) {
                int s2 = it->first+s, f2 = it->second+f;
                if (m.count(s2) == 0)
                    m[s2] = NINF;
                m[s2] = max(m[s2], f2);
            }
        }
        else {
            for(map<int,int>::iterator it = m.begin(); it != m.end(); ++it) {
                int s2 = it->first+s, f2 = it->second+f;
                if (m.count(s2) == 0)
                    m[s2] = NINF;
                m[s2] = max(m[s2], f2);
            }
        }

    }

    int best = -1;
    for(map<int,int>::iterator it = m.begin(); it != m.end(); ++it) {
        int s = it->first, f = it->second;
        if (s >= 0 && f >= 0)
            best = max(best, s+f);
    }

    cout << best << endl;

    return 0;
}
