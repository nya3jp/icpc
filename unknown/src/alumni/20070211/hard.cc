#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

#define N 100
#define EPS 1.0e-8
#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define R1 1000
#define R2 500

int n;
bool adj[N][N];
double lambda;

bool subset[N];
int interferes;
int ins[N], outs[N];
int nIns, nOuts;
double bestScore;
vector<int> bestSubset;

double choose(int n, int m) {
    double r = 1;
    REP(i, m)
        r *= (double)(n-i) / (i+1);
    return r;
}

double toss() {
    return (double)rand() / RAND_MAX;
}
int toss(int n) {
    return rand()/7%n;
}

double score() {
    return (double)interferes/nIns;
}

void subset_insert(int a) {
    assert(!subset[a]);
    REP(b, n)
        if (subset[b] && adj[a][b])
            interferes++;
    subset[a] = true;
    remove(outs, outs+nOuts--, a);
    ins[nIns++] = a;
}
void subset_erase(int a) {
    assert(subset[a]);
    subset[a] = false;
    REP(b, n)
        if (subset[b] && adj[a][b])
            interferes--;
    remove(ins, ins+nIns--, a);
    outs[nOuts++] = a;
}

void solve_r(int m) {

    if (m == 1) {
        bestScore = 0;
        bestSubset.assign(1, 0);
        return;
    }
    if (m == n) {
        bestScore = 0;
        REP(i, n) REP(j, n)
            if (i < j && adj[i][j])
                bestScore += 1;
        bestScore /= n;
        bestSubset.resize(n);
        REP(i, n)
            bestSubset[i] = i;
        return;
    }

    lambda = 1.0;
    bestScore = -1;

    REP(i, n)
        subset[i] = false;
    nIns = 0; nOuts = n;
    REP(i, n)
        outs[i] = i;
    interferes = 0;

    REP(i, m)
        subset_insert(i);

    REP(r1, min((double)R1/n, 100*choose(n, m))) {

        int accept = 0;
        REP(r2, R2) {
            int in = outs[toss(nOuts)];
            int out = ins[toss(nIns)];
            double scoreBefore = score();
            subset_insert(in);
            subset_erase(out);
            double scoreAfter = score();
            if (toss() > exp(lambda*(scoreAfter-scoreBefore))) {
                subset_erase(in);
                subset_insert(out);
                accept++;
            }
            double newScore = score();
            if (newScore > bestScore+EPS) {
                bestScore = newScore;
                bestSubset.clear();
                REP(i, n)
                    if (subset[i])
                        bestSubset.push_back(i);
            }
        }

        //cout << "accept rate: " << (int)(100*accept/R2) << "%" << endl;
        if (accept > R2*30/100) {
            lambda /= 2;
        }
        else {
            lambda *= 2;
        }
    }
}

void solve() {

    {
        double bestbestScore = -1;
        vector<int> bestbestSubset;
        for(int m = 1; m <= n; m++) {
            solve_r(m);
            if (bestScore > bestbestScore+EPS) {
                bestbestSubset = bestSubset;
                bestbestScore = bestScore;
            }
        }

        cout << bestbestSubset.size() << endl;
        REP(i, bestbestSubset.size())
            cout << bestbestSubset[i]+1 << endl;
        return;
    }

    if (n == 1) {
        cout << 1 << endl << 1 << endl;
        return;
    }

    lambda = 1.0;
    bestScore = -1;

    REP(i, n)
        subset[i] = false;
    nIns = 0; nOuts = n;
    REP(i, n)
        outs[i] = i;
    interferes = 0;

    subset_insert(0);

    REP(r1, R1/n) {

        int accept = 0;
        REP(r2, R2) {
            bool increase = (toss() <= 0.5);
            if (nIns == 1)
                increase = true;
            if (nOuts == 0)
                increase = false;

            if (increase) {
                int x = outs[toss(nOuts)];
                double scoreBefore = score();
                subset_insert(x);
                double scoreAfter = score();
                if (toss() > exp(lambda*(scoreAfter-scoreBefore))) {
                    subset_erase(x);
                    accept++;
                }
            }
            else {
                int x = ins[toss(nIns)];
                double scoreBefore = score();
                subset_erase(x);
                double scoreAfter = score();
                if (toss() > exp(lambda*(scoreAfter-scoreBefore))) {
                    subset_insert(x);
                    accept++;
                }
            }

            double newScore = score();
            if (newScore > bestScore+EPS) {
                bestScore = newScore;
                bestSubset.clear();
                REP(i, n)
                    if (subset[i])
                        bestSubset.push_back(i);
            }
        }

        //cout << "accept rate: " << accept << "%" << endl;
        if (accept > R2*30/100) {
            lambda /= 2;
        }
        else {
            lambda *= 2;
        }
    }

    cout << bestSubset.size() << endl;
    REP(i, bestSubset.size())
        cout << bestSubset[i]+1 << endl;
}


int main() {

    srand(283);

    //freopen("hard.in", "r", stdin);

    int nCases = 1;
    //cin >> nCases;

    REP(iCase, nCases) {
        int m;
        cin >> n >> m;

        REP(i, n) REP(j, n)
            adj[i][j] = false;

        REP(i, m) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            adj[a][b] = adj[b][a] = true;
        }

        solve();
    }


    return 0;
}
