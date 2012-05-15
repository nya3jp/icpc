#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) (c).begin(), (c).end()


struct Orc {
  string name;
  int score;
  vector<int> preference;
};

bool operator<(const Orc& a, const Orc& b) {
  return (a.score > b.score);
}

bool by_some_order(const string& a, const string& b) {
  int n = min(a.size(), b.size());
  REP(i, n) {
    char ca = a[i], cb = b[i];
    if (tolower(ca) != tolower(cb))
      return (tolower(ca) < tolower(cb));
    if (ca != cb)
      return (ca < cb);
  }
  return (a.size() < b.size());
}

int main() {
  int nOrcs, nArms, nPreferences;
  cin >> nOrcs >> nArms >> nPreferences;

  vector<int> capacity(nArms);
  REP(i, nArms)
    cin >> capacity[i];

  vector<Orc> orcs(nOrcs);
  REP(iOrc, nOrcs) {
    Orc& o = orcs[iOrc];
    for(;;) {
      int score;
      cin >> score;
      if (cin) {
	o.score = score;
	break;
      }
      cin.clear();
      string s;
      cin >> s;
      if (o.name.empty())
	o.name = s;
      else
	o.name += string(" ") + s;
    }
    int nPref;
    cin >> nPref;
    REP(i, nPref) {
      int a;
      cin >> a;
      a--;
      o.preference.push_back(a);
    }
  }

  sort(ALLOF(orcs));

  vector< vector<string> > res(nArms);

  REP(iOrc, nOrcs) {
    Orc& o = orcs[iOrc];
    REP(iPref, o.preference.size()) {
      int p = o.preference[iPref];
      if ((int)res[p].size() < capacity[p]) {
	res[p].push_back(o.name);
	break;
      }
    }
  }

  REP(iArm, nArms) {
    sort(ALLOF(res[iArm]), by_some_order);
    if (iArm > 0)
      cout << endl;
    REP(i, res[iArm].size())
      cout << res[iArm][i] << endl;
  }

}

