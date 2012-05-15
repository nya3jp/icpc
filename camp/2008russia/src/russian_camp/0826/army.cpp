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

void chop(char* p) {
  p += strlen(p);
  while(isspace(p[-1]))
    p--;
  *p = '\0';
}

int main() {

  if (!freopen("army.in", "r", stdin))
    abort();
  if (!freopen("army.out", "w", stdout))
    abort();

  int nOrcs, nArms, nPreferences;
  cin >> nOrcs >> nArms >> nPreferences;

  int capacity[nArms];
  REP(i, nArms)
    cin >> capacity[i];

  Orc orcs[nOrcs];
  REP(iOrc, nOrcs) {
    Orc& o = orcs[iOrc];
    /*
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
    */
    char namestr[1024];
    scanf(" %[^0-9]", namestr);
    chop(namestr);
    o.name = namestr;
    //cin >> o.score;
    scanf("%d", &o.score);

    int nPref;
    cin >> nPref;
    o.preference.resize(nPref);
    REP(i, nPref) {
      int a;
      //cin >> a;
      scanf("%d", &a);
      a--;
      //o.preference.push_back(a);
      o.preference[i] = a;
    }
  }

  //cerr << "hoge" << endl;

  sort(orcs, orcs+nOrcs);

  vector<string> res[nArms];

  //cerr << "hoge" << endl;

  REP(iOrc, nOrcs) {
    Orc& o = orcs[iOrc];
    REP(iPref, o.preference.size()) {
      int p = o.preference[iPref];
      //cerr << res[p].size() << "/" << capacity[p] << endl;
      if ((int)res[p].size() < capacity[p]) {
	res[p].push_back(o.name);
	break;
      }
    }
  }

  //cerr << "hoge" << endl;

  REP(iArm, nArms) {
    sort(ALLOF(res[iArm]), by_some_order);
    if (iArm > 0)
      cout << endl;
    //cerr << "army" << iArm << "-" << res[iArm].size() << endl;
    REP(i, res[iArm].size())
      puts(res[iArm][i].c_str());
      //cout << res[iArm][i] << endl;
  }

  //cerr << "hoge" << endl;

  return 0;
}

