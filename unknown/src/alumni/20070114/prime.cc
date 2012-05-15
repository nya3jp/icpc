#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("g.in");
#define cin fin

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define MAX_PRIME 10000

bool isprime[MAX_PRIME+1];

int solve(int src, int dest) {

    vector<int> dists(10000, -1);
    REP(i, 1000)
        dists[i] = 0;

    queue<int> q;
    dists[src] = 0;
    q.push(src);
    while(!q.empty()) {
        int here = q.front();
        q.pop();
        for(int digit = 1; digit < 10000; digit *= 10) {
            for(int k = (digit == 1000 ? 1 : 0); k < 10; k++) {
                int there = here / (digit*10) * (digit*10) + here % digit + digit * k;
                //cerr << here << " -> " << there << endl;
                if (isprime[there] && dists[there] < 0) {
                    assert(there >= 1000 && there < 10000);
                    q.push(there);
                    dists[there] = dists[here]+1;
                }
            }
        }
    }

    return dists[dest];
}

int main() {
    int nCases;
    cin >> nCases;

    REP(i, MAX_PRIME+1)
        isprime[i] = true;
    isprime[0] = isprime[1] = false;
    for(int i = 2; i <= MAX_PRIME; i++) {
        if (isprime[i]) {
            for(int j = i*i; j <= MAX_PRIME; j+=i)
                isprime[j] = false;
        }
    }

    REP(iCase, nCases) {
        int src, dest;
        cin >> src >> dest;
        int res = solve(src, dest);
        if (res < 0)
            cout << "Impossible" << endl;
        else
            cout << res << endl;
    }

    return 0;
}
