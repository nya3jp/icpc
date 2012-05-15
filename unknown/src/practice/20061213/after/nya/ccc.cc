#include <iostream>
#include <complex>
#include <map>
#include <utility>
#include <queue>
#include <set>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

typedef complex<int> place;

namespace std {
    bool operator<(const place& a, const place& b) {
        return (make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag()));
    }
}

set<place> field;
place start, goal;

bool isWall(const place& pos) {
    return (field.count(pos) == 0);
}

int solve_hand(place hand) {
    place here = start;
    place dir = place(1, 0);
    int res = 0;
    while(here != goal) {
        place front = here + dir;
        place side = here + dir*hand;
        if (!isWall(side)) {
            dir *= hand;
            here = side;
            res++;
        }
        else {
            if (isWall(front)) {
                dir *= conj(hand);
            }
            else {
                here = front;
                res++;
            }
        }
    }
    res++;
    return res;
}

const place ADJ[4] = {place(+1,0),
                      place(-1,0),
                      place(0,+1),
                      place(0,-1),};

int solve_shortest() {
    map<place,int> dists;
    queue<place> q;
    dists[start] = 0;
    q.push(start);
    while(!q.empty()) {
        place here = q.front();
        q.pop();
        REP(dir, 4) {
            place there = here + ADJ[dir];
            if (!isWall(there) && dists.count(there) == 0) {
                dists[there] = dists[here] + 1;
                q.push(there);
            }
        }
    }
    return dists[goal] + 1;
}

void solve() {

    field.clear();

    int w, h;
    cin >> w >> h;
    REP(i, h) {
        string row;
        cin >> row;
        REP(j, w) {
            if (row[j] != '#')
                field.insert(place(i, j));
            if (row[j] == 'S')
                start = place(i, j);
            if (row[j] == 'E')
                goal = place(i, j);
        }
    }

    cout << solve_hand(place(0, +1))
         << " "
         << solve_hand(place(0, -1))
         << " "
         << solve_shortest()
         << endl;
}

int main() {
    int nCases;
    cin >> nCases;
    while(nCases-- > 0)
        solve();
    return 0;
}


