#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <set>
#include <queue>
#include <map>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

typedef complex<int> place;

namespace std {
  bool operator<(const place &a, const place &b) {
    return (make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag()));
  }
}

set<place> field;
place start;
place end;
#define I place(0, 1)

static bool can_pass(place pos, place dir)
{
  place p = pos + dir;
  return field.find(p) != field.end();
}

static void solve_left()
{
  place cur = start;
  place dir = place(1, 0);
  unsigned int nstep = 0;

  while (cur != end) {
    // cout << cur << " " << dir << endl;

    if (can_pass(cur, dir / I)) {
      // 右が壁でない
      dir = dir / I;
      cur += dir;
      nstep++;
    } else {
      // 右が壁
      if (can_pass(cur, dir)) {
        // 前が壁でない
        cur += dir;
        nstep++;
      } else {
        // 前が壁
        dir = dir * I;
      }
    }
  }

  nstep++;
  cout << nstep << " ";
}

static void solve_right()
{
  place cur = start;
  place dir = place(1, 0);
  unsigned int nstep = 0;

  while (cur != end) {
    // cout << cur << " " << dir << endl;

    if (can_pass(cur, dir * I)) {
      // 右が壁でない
      dir = dir * I;
      cur += dir;
      nstep++;
    } else {
      // 右が壁
      if (can_pass(cur, dir)) {
        // 前が壁でない
        cur += dir;
        nstep++;
      } else {
        // 前が壁
        dir = dir / I;
      }
    }
  }

  nstep++;
  cout << nstep << " ";
}

static void solve_shortest()
{
  place cur = start;
  unsigned int nstep = 0;

  queue<place> q;
  q.push(cur);

  map<place, int> trace;
  trace[start] = 0;

  while (!q.empty()) {
    place p = q.front();
    q.pop();
    if (p == end)
      break;

    place dir = place(1, 0);
    REP(i, 4) {
      dir *= I;
      if (trace.count(p + dir) == 0 && can_pass(p, dir)) {
        trace[p + dir] = trace[p] + 1;
        q.push(p + dir);
      }
    }
  }

  nstep = trace[end];
  nstep++;
  cout << nstep << endl;
}

int main(void)
{
  int n;
  cin >> n;
  while (n--) {
    field.clear();

    vector<string> table;
    table.clear();

    int width, height;
    cin >> width;
    cin >> height;

    string line;
    table.push_back(string(width + 2, '#'));
    REP(iLine, height) {
      cin >> line;
      table.push_back(string("#") + line + string("#"));
    }
    table.push_back(string(width + 2, '#'));

    REP(y, table.size()) {
      REP(x, table[y].size()) {
        if (table[y][x] == 'S') {
          start = place(x, y);
        }
        if (table[y][x] == 'E') {
          end = place(x, y);
        }

        if (table[y][x] != '#')
          field.insert(place(x, y));
      }
    }

    solve_left();
    solve_right();
    solve_shortest();
  }
}