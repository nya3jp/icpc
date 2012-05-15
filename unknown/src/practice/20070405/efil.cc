#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

#define ID(i,j) ((i)*w+(j))

map<pair<int,int>, int*> table;

int process(int now, int h, int w) {
    int future = 0;
    REP(i, h) REP(j, w) {
        int c = 0;
        if (now & 1<<ID((i+0)%h,(j+1)%w)) c++;
        if (now & 1<<ID((i+0)%h,(j+w-1)%w)) c++;
        if (now & 1<<ID((i+1)%h,(j+0)%w)) c++;
        if (now & 1<<ID((i+h-1)%h,(j+0)%w)) c++;
        if (now & 1<<ID((i+1)%h,(j+1)%w)) c++;
        if (now & 1<<ID((i+h-1)%h,(j+1)%w)) c++;
        if (now & 1<<ID((i+1)%h,(j+w-1)%w)) c++;
        if (now & 1<<ID((i+h-1)%h,(j+w-1)%w)) c++;
        if (now & 1<<ID(i,j))
            future |= (2 <= c && c <= 3 ? 1 : 0) << ID(i, j);
        else
            future |= (c == 3 ? 1 : 0) << ID(i, j);
    }
    return future;
}

void make(int h, int w) {
    int n = h * w;
    int*& mem = table[make_pair(h, w)];
    mem = new int[1<<n];
    REP(old, 1<<n)
        mem[old] = process(old, h, w);
}

int solve(int future, int h, int w) {

    int n = h * w;

    int res = 0;
    int* mem = table[make_pair(h, w)];

    REP(old, 1<<n) {
        //if (process(old, h, w) == future)
        if (mem[old] == future)
            res++;
    }

    return res;
}


int main() {

    for(int h = 1; h <= 16; h++) {
        for(int w = 1; w <= h && w*h <= 16; w++) {
            //cerr << h << "," << w << endl;
            make(h, w);
        }
    }

    int iCase = 0;
    for(;;) {
        int h, w;
        cin >> h >> w;
        if (h == 0 && w == 0)
            break;

        bool sw = false;
        if (h < w) {
            sw = true;
            swap(h, w);
        }

        int future = 0;

        int m;
        cin >> m;
        REP(i, m) {
            int a, b;
            cin >> a >> b;
            if (sw)
                swap(a, b);
            future |= 1<<(a*w+b);
        }

        cout << "Case " << ++iCase << ": ";
        int res = solve(future, h, w);
        if (res == 0)
            cout << "Garden of Eden." << endl;
        else
            cout << res << " possible ancestors." << endl;

    }


    return 0;
}
