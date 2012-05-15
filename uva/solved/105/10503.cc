#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

bool solve(int used, int current,
           int nUsed,
           vector<pair<int,int> >& pieces, int nToUse, int goal,
           map<int, map<int, bool> > mem)
{
    int nPieces = pieces.size();
    if (nUsed == nToUse)
        return (current == goal);
    if (mem[used].count(current) == 0) {
        bool result = false;
        for(int i = 0; i < nPieces; i++) {
            if ((used&(1<<i)) == 0) {
                int a = pieces[i].first, b = pieces[i].second;
                if (a != current)
                    swap(a, b);
                if (a == current) {
                    if (solve(used|(1<<i), b,
                              nUsed+1,
                              pieces, nToUse, goal, mem)) {
                        result = true;
                        break;
                    }
                }
            }
        }
        mem[used][current] = result;
    }
    return mem[used][current];
}


int main() {
    for(;;) {

        int nToUse, nPieces;
        cin >> nToUse >> nPieces;
        if (nToUse == 0)
            break;

        int start, goal;
        {
            int t;
            cin >> t >> start >> goal >> t;
        }

        vector< pair<int,int> > pieces(nPieces);
        for(int i = 0; i < nPieces; i++) {
            int a, b;
            cin >> a >> b;
            pieces[i] = make_pair(a, b);
        }

        map<int, map<int, bool> > mem;
        cout << (solve(0, start, 0, pieces, nToUse, goal, mem) ? "YES" : "NO") << endl;

    }
    return 0;
}
