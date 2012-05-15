#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
#include <ext/hash_map>
#include <tr1/functional>
using namespace std;
using namespace __gnu_cxx;
using namespace std::tr1;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

int n;
double p;
double res = 0;

double search(vector<int>& u, vector<int>& v, int k);
double solve(vector<int> v, int k);

double search(vector<int>& u, vector<int>& v, int k) {
    if (v.empty())
        return solve(u, k+1);
    int t = v.back();
    v.pop_back();
    double q = pow(1.0-p, (double)t);
    double res = 0;
    u.push_back(t);
    res += q * search(u, v, k);
    u.pop_back();
    u[0] += t;
    res += (1.0 - q) * search(u, v, k);
    u[0] -= t;
    v.push_back(t);
    return res;
}
template<class T>
struct vector_hash : public unary_function<vector<T>, size_t> {
    size_t operator()(const vector<T>& v) const {
        return Fnv_hash<>::hash(reinterpret_cast<const char*>(&v[0]), sizeof(T)*v.size());
    }
};
typedef hash_map<vector<int>, double, vector_hash<int> > hash_type;
hash_type memo;


double solve(vector<int> v, int k) {
    if (k == n)
        return (v.size() == 1 ? 1 : 0);
    sort(ALLOF(v));
    hash_type::iterator it = memo.find(v);
    if (it == memo.end()) {
        if (k == n-1) {
            double res = 1;
            REP(i, v.size())
                res *= 1.0 - pow((1.0-p), (double)v[i]);
            memo[v] = res;
        }
        else {
            vector<int> u(1, 1);
            memo[v] = search(u, v, k);
        }
    }
    return memo[v];
}

int main() {
    cin >> n >> p;
    vector<int> v(1, 1);
    double res = solve(v, 1);
    printf("%.10f\n", res);
    return 0;
}
