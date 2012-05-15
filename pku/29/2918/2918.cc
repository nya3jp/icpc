#include <iostream>
#include <string>
#include <queue>
#include <cstdlib>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define SIZE 3
#define N (SIZE*SIZE)
#define FACE "0123456789"

struct field_t {
    int data[N][N];
    inline int* operator[](int i) { return data[i]; }
    inline const int* operator[](int i) const { return data[i]; }
};

field_t solution;

struct state_t {
    field_t field;
    field_t possible;
    double priority;
};
bool operator<(const state_t& a, const state_t& b) {
    return (a.priority < b.priority);
}

field_t parse_field(string line) {
    field_t field;
    REP(i, N) REP(j, N) {
        char c = line[i*N+j];
        field[i][j] = string(FACE).find(c);
    }
    return field;
}

void print_field(const field_t& field) {
    REP(i, N) {
        REP(j, N)
            printf("%c", FACE[field[i][j]]);
        printf("\n");
    }
}

int log2b(int b) {
    for(int r = N; r >= 0; r--)
        if (b&(1<<r))
            return r;
    assert(false);
    return -1;
}

void update_possibility(state_t& state, int i, int j) {
    int c = state.field[i][j];
    assert(1 <= c && c <= N);

    state.possible[i][j] = 1<<state.field[i][j];
    REP(ii, N) if (ii != i)
        state.possible[ii][j] &= ~(1<<c);
    REP(jj, N) if (jj != j)
        state.possible[i][jj] &= ~(1<<c);
    
    int si = i/SIZE*SIZE, sj = j/SIZE*SIZE;
    REP(di, SIZE) REP(dj, SIZE) {
        int ii = si+di, jj = sj+dj;
        if (!(ii == i && jj == j))
            state.possible[ii][jj] &= ~(1<<c);
    }
}

void calc_possiblility(state_t& state) {
    REP(i, N) REP(j, N)
        state.possible[i][j] = (state.field[i][j] == 0 ? ((1<<N)-1)<<1 : 1<<state.field[i][j]);

    REP(i, N) REP(j, N) if (state.field[i][j] > 0)
        update_possibility(state, i, j);
    return;
}

void calc_priority(state_t& state) {
    REP(i, N) REP(j, N) {
        int p = __builtin_popcount(state.possible[i][j]);
        state.priority += p*p;
    }
}

void apply_constraints(state_t& state) {

    bool last;
    do {
        last = true;
        REP(i, N) REP(j, N) {
            if (state.possible[i][j] == 0)
                return;
            if (state.field[i][j] == 0) {
                if (__builtin_popcount(state.possible[i][j]) == 1) {
                    state.field[i][j] = log2b(state.possible[i][j]);
                    update_possibility(state, i, j);
                    last = false;
                }

                {
                    int single = state.possible[i][j];
                    REP(ii, N) if (ii != i)
                        single &= ~state.possible[ii][j];
                    if (__builtin_popcount(single) == 1) {
                        state.field[i][j] = log2b(single);
                        update_possibility(state, i, j);
                        last = false;
                    }
                }
                {
                    int single = state.possible[i][j];
                    REP(jj, N) if (jj != j)
                        single &= ~state.possible[i][jj];
                    if (__builtin_popcount(single) == 1) {
                        state.field[i][j] = log2b(single);
                        update_possibility(state, i, j);
                        last = false;
                    }
                }
                {
                    int single = state.possible[i][j];
                    int si = i/SIZE*SIZE, sj = j/SIZE*SIZE;
                    REP(di, SIZE) REP(dj, SIZE) {
                        int ii = si+di, jj = sj+dj;
                        if (!(ii == i && jj == j))
                            single &= ~state.possible[ii][jj];
                    }
                    if (__builtin_popcount(single) == 1) {
                        state.field[i][j] = log2b(single);
                        update_possibility(state, i, j);
                        last = false;
                    }
                }
            }
        }
    } while(!last);

}

bool is_consistent(const state_t& state) {
    REP(i, N) REP(j, N)
        if (state.possible[i][j] == 0)
            return false;
    return true;
}

bool is_accepted(const state_t& state) {
    REP(i, N) REP(j, N)
        if (__builtin_popcount(state.possible[i][j]) != 1)
            return false;
    return true;
}

void expand(const state_t& cur, int i, int j, vector<state_t>& nexts) {
    REP(k, N+1) if (cur.possible[i][j] & (1<<k)) {
        state_t next = cur;
        next.field[i][j] = k;
        update_possibility(next, i, j);
        apply_constraints(next);
        if (is_consistent(next)) {
            calc_priority(next);
            nexts.push_back(next);
        }
    }
}

void deepen(const state_t& cur, vector<state_t>& nexts) {

    assert(!is_accepted(cur));

    int ni=-1, nj;

    REP(i, N) REP(j, N) if (cur.field[i][j] == 0) {
        if (ni < 0 || (__builtin_popcount(cur.possible[i][j]) < __builtin_popcount(cur.possible[ni][nj]))) {
            ni = i;
            nj = j;
        }
    }

    expand(cur, ni, nj, nexts);
}

bool solve_second(const state_t& cur) {

    if (is_accepted(cur)) {
        solution = cur.field;
        return true;
    }

    /*
    printf("Searching:\n");
    print_field(cur.field);
    printf("\n");
    //*/

    vector<state_t> nexts;
    deepen(cur, nexts);

    sort(ALLOF(nexts));

    REP(i, nexts.size())
        if (solve_second(nexts[i]))
            return true;

    return false;
}

bool solve_first(const state_t& cur, int depth=0) {

    if (is_accepted(cur)) {
        solution = cur.field;
        return true;
    }

    if (depth == 2)
        return solve_second(cur);

    assert(is_consistent(cur));

    //cerr << string(depth, '=') << '>' << string(60-depth, ' ') << "\r";

    /*
    printf("Searching:\n");
    print_field(cur.field);
    printf("\n");
    //*/

    vector<state_t> nexts;
    nexts.reserve(14000);
    nexts.push_back(cur);

    int k = 0;
    while(k < (int)nexts.size() && nexts.size() <= 10000) {
        state_t base = nexts[k++];
        int f = nexts.size();
        deepen(base, nexts);
        for(int i = f; i < (int)nexts.size(); i++) {
            if (is_accepted(nexts[i])) {
                solution = nexts[i].field;
                return true;
            }
        }
        sort(nexts.begin()+f, nexts.end());
    }

    sort(nexts.begin()+k, nexts.end());
    for(int i = k; i < (int)nexts.size(); i++)
        if (solve_first(nexts[i], depth+1))
            return true;

    return false;
    //return solve_second(cur);
}


int main() {

    int nCases;
    cin >> nCases;

    REP(iCase, nCases) {
        string line;
        REP(i, N) {
            string s;
            cin >> s;
            line += s;
        }
        if (!cin)
            break;
        { string s; getline(cin, s); }

        state_t state;
        state.field = parse_field(line);
        calc_possiblility(state);
        apply_constraints(state);

        solve_first(state);

        cout << "Scenario #" << iCase+1 << ":" << endl;
        print_field(solution);
        cout << endl;
    }

    return 0;
}
