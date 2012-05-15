#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <complex>

using namespace std;

#define EPS 1.0e-8
#define REP(i,n) for(int i = 0; i < (int)(n); i++)

typedef complex<double> P;
struct L { P pos, dir; };


vector<L> edges;
vector< vector<int> > lst;
vector< vector< pair<int,int> > > adjs;

double outp(const P& a, const P& b) {
    return (conj(a)*b).imag();
}
double ratio(const L& l, const L& m) {
    double num = outp(m.dir, m.pos-l.pos);
    double denom = outp(m.dir, l.dir);
    if (abs(denom) < EPS)
        return -1;
    return num / denom;
}

vector<int> intersects(int here) {
    int n = edges.size();
    vector<pair<double,int> > v;
    REP(there, n) {
        double r = ratio(edges[here], edges[there]);
        double rr = ratio(edges[there], edges[here]);
        if (0 <= r && r <= 1 && 0 <= rr && rr <= 1) {
            v.push_back(make_pair(r, there));
        }
    }
    sort(v.begin(), v.end());
    vector<int> res(v.size());
    REP(i, v.size())
        res[i] = v[i].second;
    return res;
}

int solve() {
    int n = edges.size();

    lst.clear();
    REP(i, n) {
        lst.push_back(intersects(i));
    /*
        cout << i << ": ";
        REP(j, lst.back().size())
            cout << lst.back()[j] << ' ';
        cout << endl;
    */
    }

    adjs.clear();
    REP(i, n) {
        adjs.push_back(vector<pair<int,int> >(n, make_pair(-1-i, -1-i)));
    }
    REP(i, n) {
        REP(j, (int)lst[i].size()) {
            if (j == 0) {
                adjs[i][lst[i][j]] = make_pair(-1-i, lst[i][j+1]);
            }
            else if (j+1 == lst[i].size()) {
                adjs[i][lst[i][j]] = make_pair(lst[i][j-1], -1-i);
            }
            else {
                adjs[i][lst[i][j]] = make_pair(lst[i][j-1], lst[i][j+1]);
            }
        }
    }

    int cnt = 0;
    REP(here, n) {
        vector<int>& thisline = lst[here];
        REP(i, (int)thisline.size() - 1) { 
            int id1 = thisline[i];
            int id2 = thisline[i+1];
            pair<int,int> a = adjs[id1][here];
            pair<int,int> b = adjs[id2][here];
            if ((a.first == id2 || a.second == id2) && (b.first == id1 || b.second == id1)) {
                cnt++;
                //printf("%d,%d,%d\n", here, id1, id2);
            }
        }
    }

    return cnt/3;
}

int main() {
    freopen("hills.in", "r", stdin);

    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        edges.clear();
        int n;
        cin >> n;
        REP(i, n) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            P p(x1, y1);
            P q(x2, y2);
            L l = {p, q-p};
            edges.push_back(l);
        }
        cout << solve() << endl;
    }

    return 0;
}
