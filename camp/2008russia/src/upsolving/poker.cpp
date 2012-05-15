#include <iostream>
#include <vector>
#include <complex>
#include <map>
#include <cstdio>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "poker"

const string RANKS = "23456789TJQKA";

struct Histgram {
    int v[13];
    Histgram() {
        memset(v, 0, sizeof(v));
    }
};

bool operator<(const Histgram& a, const Histgram& b) {
    return lexicographical_compare(a.v, a.v+13, b.v, b.v+13);
}
bool contains(const Histgram& a, const Histgram& b) {
    REP(i, 13)
        if (a.v[i] < b.v[i])
            return false;
    return true;
}


map<Histgram, vector< pair<Histgram, double> > > evolve_memo[11];

const vector< pair<Histgram, double> >& evolve(Histgram init, int d) {
    if (evolve_memo[d].count(init) == 0) {
        map<Histgram, double> prev;
        prev[init] = 1;
        REP(t, d) {
            map<Histgram, double> next;
            FOR(it, prev) {
                const Histgram& oldhist = it->first;
                int j = 12;
                for(int i = 12; i >= 0; i--) {
                    if (oldhist.v[i] != oldhist.v[j])
                        j = i;
                    Histgram newhist(oldhist);
                    newhist.v[j]++;
                    next[newhist] += it->second / 13;
                }
            }
            prev.swap(next);
        }
        evolve_memo[d][init] = vector< pair<Histgram, double> >(ALLOF(prev));
        fprintf(stderr, "evolve: %d nodes.\n", prev.size());
    }
    return evolve_memo[d][init];
}


Histgram make_histgram(string hands) {
    map<char, int> cnt;
    REP(i, hands.size())
        cnt[hands[i]]++;
    Histgram h;
    int k = 0;
    FOR(it, cnt)
        h.v[k++] = it->second;
    sort(h.v, h.v+13);
    return h;
}

int check_rank(Histgram hands, const vector<Histgram>& ranks) {
    int n = ranks.size();
    for(int i = n-1; i >= 0; i--)
        if (contains(hands, ranks[i]))
            return i+1;
    return 0;
}


map< Histgram, double > search_memo[110];

double search(string hands_str, string open_str, int rest_opens, int n, int m, const vector<Histgram>& ranks, Histgram append = Histgram()) {
    if (rest_opens == 0) {
        Histgram mine = make_histgram(hands_str);
        Histgram open = make_histgram(open_str);
        REP(i, 13)
            mine.v[i] += append.v[i];
        REP(i, 13)
            open.v[i] += append.v[i];
        sort(mine.v, mine.v+13);
        sort(open.v, open.v+13);
        int myRank = check_rank(mine, ranks);
        if (search_memo[myRank].count(open) == 0) {
            double res = 0;
            const vector< pair<Histgram, double> >& her = evolve(open, m);
            double lo = 0;
            //fprintf(stderr, "checking ranks...\n");
            FOR(it, her) {
                /*
                REP(i, 13)
                    fprintf(stderr, "%d ", it->first.v[i]);
                fprintf(stderr, "(%d)\n", check_rank(it->first, ranks));
                fprintf(stderr, "%.5f ", it->second);
                //*/
                if (check_rank(it->first, ranks) < myRank)
                    lo += it->second;
            }
            //fprintf(stderr, "\n");
            res += lo;
            search_memo[myRank][open] = res;
        }
        return search_memo[myRank][open];
    }
    else {
        double res = 0;
        REP(i, 13)
            res += search(hands_str, open_str + RANKS[i], rest_opens-1, n, m, ranks) / 13;
        return res;
    }
}

double search(string hands_str, string open_str, int rest_opens, int n, int m, const vector<Histgram>& ranks) {
}


int main() {

    if (!freopen(PROBLEM_NAME ".in", "r", stdin))
        abort();
    if (!freopen(PROBLEM_NAME ".out", "w", stdout))
        abort();

    int n, m, k;
    cin >> n >> m >> k >> ws;

    string hands_str, open_str;
    getline(cin, hands_str);
    getline(cin, open_str);

    int nRanks;
    cin >> nRanks;

    vector<Histgram> ranks;
    REP(iRank, nRanks) {
        Histgram h;
        int t;
        cin >> t;
        REP(i, t)
            cin >> h.v[i];
        sort(h.v, h.v+13);
        ranks.push_back(h);
    }

    double res = search(hands_str, open_str, k-open_str.size(), n, m, ranks);

    printf("%.10f\n", res);

    return 0;
}

