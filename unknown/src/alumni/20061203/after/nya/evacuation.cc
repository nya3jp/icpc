#include <iostream>
#include <string>
#include <complex>
#include <vector>
#include <map>
#include <queue>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define IN(i,l,u) ((l) <= (i) && (i) < (u))
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

typedef complex<int> P;

const P DIRS[4] = {P(1, 0), P(-1, 0), P(0, 1), P(0, -1)};
const int INF = 1000000;

namespace std {
  template<class T>
  bool operator<(const complex<T>& a, const complex<T>& b) {
    return make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag());
  }
}

map<P, int> shortest(const vector<string>& field, P start) {
  map<P, int> dists;

  queue<P> q;
  q.push(start);
  dists[start] = 0;

  while(!q.empty()) {
    P here = q.front();
    q.pop();

    REP(iDir, 4) {
      P there = here + DIRS[iDir];
      if (dists.count(there) == 0 && IN(there.real(), 0, field.size()) && IN(there.imag(), 0, field[0].size())) {
	if (field[there.real()][there.imag()] == '.') {
	  dists[there] = dists[here] + 1;
	  q.push(there);
	}
      }
    }
  }

  /*
  cout << start << " reaches to";
  FOR(it, dists)
    cout << " " << it->first << "(" << it->second << ")";
  cout << endl;
  //*/

  return dists;
}

struct Matcher {
  int n, m, nDoors, nPersons, maxTime;

  vector<int> toleft;
  vector<bool> visited;
  vector< vector<int> > g;

  Matcher(int nDoors, int nPersons, int maxTime)
    : n(maxTime*nDoors), m(nPersons),
      nDoors(nDoors), nPersons(nPersons), maxTime(maxTime),
      toleft(m, -1), g(n) {
  }

  void entry(int iDoor, int iPerson, int minTime) {
    for(int t = minTime; t < maxTime; t++)
      g[nDoors*t + iDoor].push_back(iPerson);
  }

  bool augment(int left) {
    if (left < 0)
      return true;
    assert(IN(left, 0, n));
    if (visited[left])
      return false;
    visited[left] = true;
    vector<int>& edges = g[left];
    REP(i, edges.size()) {
      int right = edges[i];
      assert(IN(right, 0, m));
      if (augment(toleft[right])) {
	toleft[right] = left;
	return true;
      }
    }
    return false;
  }

  int match() {
    int matches = 0;
    REP(left, n) {
      visited.assign(n, false);
      if (augment(left))
	matches++;
      if (matches == nPersons) {
	/*
	REP(i, nPersons)
	  cout << i << " go to " << toleft[i]%nDoors << " door at " << toleft[i]/nDoors << endl;
	//*/
	return left/nDoors;
      }
    }
    assert(false);
    return -1;
  }

};

int solve() {

  int height, width;
  cin >> height >> width;

  vector<string> field(height);
  REP(i, height)
    cin >> field[i];

  vector<P> doors, persons;
  REP(i, height) REP(j, width) {
    switch(field[i][j]) {
    case 'D':
      doors.push_back(P(i, j));
      break;
    case '.':
      persons.push_back(P(i, j));
      break;
    }
  }

  int nDoors = doors.size();
  int nPersons = persons.size();

  vector< vector<int> > schedule(nDoors, vector<int>(nPersons));

  REP(iDoor, nDoors) {
    map<P, int> dists = shortest(field, doors[iDoor]);
    REP(iPerson, nPersons) {
      P person = persons[iPerson];
      if (dists.count(person) == 0)
	schedule[iDoor][iPerson] = INF;
      else
	schedule[iDoor][iPerson] = dists[person];
    }
  }

  REP(iPerson, nPersons) {
    bool impossible = true;
    REP(iDoor, nDoors) {
      if (schedule[iDoor][iPerson] < INF)
	impossible = false;
    }
    if (impossible)
      return -1;
  }

  Matcher matcher(nDoors, nPersons, 200);
  REP(iDoor, nDoors) REP(iPerson, nPersons)
    matcher.entry(iDoor, iPerson, schedule[iDoor][iPerson]);

  return matcher.match();
}


int main() {
  int nCases;
  cin >> nCases;

  while(nCases-- > 0) {
    int res = solve();
    if (res < 0)
      cout << "impossible" << endl;
    else
      cout << res << endl;
  }

  return 0;
}
