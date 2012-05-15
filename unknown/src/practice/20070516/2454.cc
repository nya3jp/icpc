#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <numeric>
#include <cstdlib>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

struct area_t {
    int num;
    int id;
};

bool operator<(const area_t& a, const area_t& b) {
    return (a.num < b.num);
}

int rnd(int n) {
    return rand()/7%n;
}

double energy(int current, int lower, int upper) {
    const double f = 0.001; //てきとーな定数
    int middle = (lower+upper)/2;
    return exp(f*abs(current-middle));
}

vector<int> solve(int* v, int n, int lower, int upper) {

    area_t uses[60];
    area_t saves[60];

    { // てきとーに貪欲に初期状態をとる
        deque<area_t> areas;
        REP(i, 2*n) {
            areas.push_back((area_t){v[i], i});
        }
        sort(areas.begin(), areas.end());
        REP(i, n) {
            if (i%2 == 0) {
                uses[i] = areas.front(); areas.pop_front();
                saves[i] = areas.back(); areas.pop_back();
            }
            else {
                uses[i] = areas.back(); areas.pop_back();
                saves[i] = areas.front(); areas.pop_front();
            }
        }
    }

    // いまの合計
    int prev = 0;
    REP(i, n)
        prev += uses[i].num;

    while(!(lower <= prev && prev < upper)) {

        int a = rnd(n);
        int b = rnd(n);
        // とっかえたあとの合計
        int current = prev - uses[a].num + saves[b].num;

        // コインなげ
        double z = (double)rand()/RAND_MAX;
        if (z <= energy(prev, lower, upper)/energy(current, lower, upper)) {
            swap(uses[a], saves[b]);
            prev = current;
        }

    }

    vector<int> res;
    REP(i, n)
        res.push_back(uses[i].id);

    return res;
}

int main() {

    // Powered by Fate Testarossa
    srand(*(const int*)"FATE");

    int n;
    int v[180];
    scanf("%d", &n);
    REP(i, 3*n)
        scanf("%d", &v[i]);

    REP(i, 3*n) {
        v[i] *= 1000;
        v[i] += i+1;
    }
    sort(v, v+3*n);

    int ids[180];
    REP(i, 3*n) {
        ids[i] = v[i] % 1000;
        v[i] /= 1000;
    }

    REP(i, n)
        printf("%d\n", ids[i]);

    REP(i, 2*n) {
        v[i] = v[i+n];
        ids[i] = ids[i+n];
    }

    int total = accumulate(v, v+2*n, (int)0);

    int need_to_win = 1000 * n / 2 + 1;

    int not_matter = total - need_to_win*2;

    assert(not_matter >= 0);

    int lower = need_to_win;
    int upper = min(1000*n, need_to_win+not_matter) + 1;

    vector<int> res = solve(v, n, lower, upper);

    REP(i, n) {
        printf("%d\n", ids[res[i]]);
        ids[res[i]] = -1;
    }
    REP(i, 2*n) {
        if (ids[i] >= 0)
            printf("%d\n", ids[i]);
    }

    return 0;
}

