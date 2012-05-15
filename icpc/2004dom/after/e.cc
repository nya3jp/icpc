#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <complex>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)


struct Cell {
    double leftPos, rightPos;
    double leftHeight, rightHeight;
    double volume;
    double rate;
};

struct Query {
    double pos, time, result;
};

double flowTime(Cell c) {
    return ((c.rightPos-c.leftPos)*min(c.leftHeight, c.rightHeight) - c.volume) / c.rate;
}

void goFlow(Cell& c, double t) {
    c.volume += c.rate * t;
}

bool isFull(Cell c) {
    return (abs((c.rightPos-c.leftPos)*min(c.leftHeight, c.rightHeight) - c.volume) < 1.0e-10);
}

double heightOf(Cell c) {
    return c.volume / (c.rightPos-c.leftPos);
}

void solve(vector<Cell> cells, vector<Query>& queries) {

    double now = 0.0;

    for(;;) {
        double next = numeric_limits<double>::max();
        REP(i, cells.size())
            if (!isFull(cells[i]) && cells[i].rate > 1.0e-10)
                next <?= now + flowTime(cells[i]);
        REP(i, queries.size())
            if (now <= queries[i].time + 1.0e-10 && queries[i].result < -1.0e-10)
                next <?= queries[i].time;

        /*
        cout << now << endl;
        REP(i, cells.size())
            cout << heightOf(cells[i]) << " ";
        cout << endl;
        */

        REP(i, cells.size())
            goFlow(cells[i], next-now);
        now = next;

    REDO:
        REP(i, cells.size()) {
            Cell& c = cells[i];
            if (isFull(c) && c.rate > 1.0e-10) {
                //cout << "cell " << i << " is full" << endl;
                if (abs(c.leftHeight- c.rightHeight) < 1.0e-10)
                    goto FINISHED;
                if (c.leftHeight < c.rightHeight) {
                    if (!isFull(cells[i-1])) {
                        cells[i-1].rate += cells[i].rate;
                        cells[i].rate = 0;
                    }
                    else {
                        cells[i-1].rightHeight = cells[i].rightHeight;
                        cells[i-1].rightPos = cells[i].rightPos;
                        cells[i-1].volume += cells[i].volume;
                        cells[i-1].rate += cells[i].rate;
                        cells.erase(cells.begin()+i);
                    }
                }
                else {
                    if (!isFull(cells[i+1])) {
                        cells[i+1].rate += cells[i].rate;
                        cells[i].rate = 0;
                    }
                    else {
                        cells[i+1].leftHeight = cells[i].leftHeight;
                        cells[i+1].leftPos = cells[i].leftPos;
                        cells[i+1].volume += cells[i].volume;
                        cells[i+1].rate += cells[i].rate;
                        cells.erase(cells.begin()+i);
                    }
                }
                goto REDO;
            }
        }

        REP(i, queries.size()) {
            if (abs(now-queries[i].time) < 1.0e-10) {
                REP(j, cells.size()) {
                    if (cells[j].leftPos < queries[i].pos && queries[i].pos < cells[j].rightPos)
                        queries[i].result = heightOf(cells[j]);
                }
            }
        }
    }

FINISHED:

    REP(i, queries.size())
        if (queries[i].result < -1.0e-10)
            queries[i].result = 50;
}



void solve() {

    int nSeparators;
    cin >> nSeparators;

    vector< pair<int,int> > separators(nSeparators);
    REP(i, nSeparators) {
        pair<int,int>& x = separators[i];
        cin >> x.first >> x.second;
    }

    separators.insert(separators.begin(), make_pair(0, 50));
    separators.insert(separators.end(), make_pair(100, 50));

    vector<Cell> cells(nSeparators+1);
    REP(i, nSeparators+1) {
        int left = separators[i].second;
        int right = separators[i+1].second;

        cells[i] = (Cell){separators[i].first, separators[i+1].first, left, right, 0, 0};
    }

    int nSources;
    cin >> nSources;
    REP(i, nSources) {
        int pos, rate;
        cin >> pos >> rate;
        REP(i, nSeparators+1) {
            if (separators[i].first < pos && pos < separators[i+1].first) {
                cells[i].rate += rate / 30.0;
            }
        }
    }

    int nQueries;
    cin >> nQueries;

    vector<Query> schedule;
    REP(i, nQueries) {
        int pos, time;
        cin >> pos >> time;
        schedule.push_back((Query){pos, time, -1});
    }

    solve(cells, schedule);

    REP(i, nQueries) {
        printf("%.10f\n", schedule[i].result);
    }

}

int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases)
        solve();

    return 0;
}


