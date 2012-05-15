#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)


int one(const vector<int>& cards, vector< vector<int> >& mem, int origin, int m);
int two(const vector<int>& cards, vector< vector<int> >& mem, int origin, int m);

int one(const vector<int>& cards, vector< vector<int> >& mem, int origin, int m) {

    if (m == 0)
        return 0;

    if (mem[origin][m] >= 0)
        return mem[origin][m];

    int res = max(cards[origin] + two(cards, mem, origin+1, m-1),
                  cards[origin+m-1] + two(cards, mem, origin, m-1));

    return mem[origin][m] = res;
}

int two(const vector<int>& cards, vector< vector<int> >& mem, int origin, int m) {

    int left = cards[origin];
    int right = cards[origin+m-1];

    if (left >= right)
        return one(cards, mem, origin+1, m-1) - left;
    return one(cards, mem, origin, m-1) - right;
}

int solve(vector<int> cards) {
    int n = cards.size();
    vector< vector<int> > mem(n+1, vector<int>(n+1, -1));
    return one(cards, mem, 0, n);
}

int main() {

    int iCase = 0;
    for(;;) {
        int n;

        cin >> n;
        if (n == 0)
            break;

        vector<int> cards(n);
        REP(i, n)
            cin >> cards[i];

        cout << "In game "
             << ++iCase
             << ", the greedy strategy might lose by as many as "
             << solve(cards)
             << " points."
             << endl;

    }    

    return 0;
}

