#include <iostream>
#include <cstdio>
#include <vector>
#include <functional>
#include <complex>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) (c).begin(), (c).end()

typedef complex<int> P;

namespace std {
bool operator<(const P& a, const P& b) {
  if (a.imag() != b.imag())
    return (a.imag() < b.imag());
  return (a.real() < b.real());
}
}

int n;
vector<P> gs[100010];
vector<P> lines[100010][2];
int polyorder[100010];
vector<P>::iterator mids[100010];

bool by_container(int a, int b) {
  return (gs[a][0] < gs[b][0]);
}

double interpolate(vector<P>& ps, int y) {
  int lo = 0, hi = ps.size() -1;
  while(lo < hi) {
    int mid = (lo+hi+1)/2;
    if (ps[mid].imag() <= y) {
      lo = mid;
    }
    else {
      hi = mid-1;
    }
  }
  P d = ps[lo+1]-ps[lo];
  return ps[lo].real() + (double)d.real()*(y-ps[lo].imag())/d.imag();
}

bool contains(int gid, const P& p) {
  int lo = lines[gid][0][0].imag(), hi = lines[gid][0].back().imag();
  int y = p.imag();
  if (y <= lo || hi <= y)
    return false;
  double a = interpolate(lines[gid][0], y);
  double b = interpolate(lines[gid][1], y);
  int x = p.real();
  return (a-x)*(b-x) < 0;
}

int container(P p) {
  if (!contains(polyorder[0], p))
    return -1;
  int lo = 0, hi = n-1;
  while(lo < hi) {
    int mid = (lo+hi+1)/2;
    if (contains(polyorder[mid], p))
      lo = mid;
    else
      hi = mid-1;
  }
  return lo;
}

double area(const vector<P>& g) {
  int n = g.size();
  double res = 0;
  REP(i, n) {
    int j = (i+1)%n;
    const P& a = g[i];
    const P& b = g[j];
    res += (double)a.real()*b.imag()-(double)a.imag()*b.real();
  }
  return abs(res*0.5);
}

int main() {

  if (!freopen("castle.in", "r", stdin))
    abort();
  if (!freopen("castle.out", "w", stdout))
    abort();

  scanf("%d", &n);

  REP(i, n) {
    int m;
    scanf("%d", &m);
    vector<P>& g = gs[i];
    g.resize(m);
    REP(j, m) {
      int x, y;
      scanf("%d%d", &x, &y);
      g[j] = P(x, y);
    }
    rotate(g.begin(), min_element(ALLOF(g)), g.end());
    mids[i] = max_element(ALLOF(g));
    copy(g.begin(), mids[i]+1, back_inserter(lines[i][0]));
    copy(mids[i], g.end(), back_inserter(lines[i][1]));
    lines[i][1].push_back(g[0]);
    reverse(ALLOF(lines[i][1]));
  }

  REP(i, n)
    polyorder[i] = i;
  sort(polyorder, polyorder+n, by_container);

  vector<bool> fired(n, false);
  int m;
  scanf("%d", &m);
  REP(i, m) {
    int x, y;
    scanf("%d%d", &x, &y);
    int id = container(P(x, y));
    if (id >= 0)
      fired[id] = true;
  }

  vector<double> areas(n);
  REP(i, n)
    areas[i] = area(gs[polyorder[i]]);
  areas.push_back(0);

  double res = 0;
  REP(i, n)
    if (fired[i])
      res += areas[i] - areas[i+1];

  printf("%.6f\n", res);

  return 0;
}

