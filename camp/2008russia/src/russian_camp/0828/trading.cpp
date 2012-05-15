#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <sstream>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()


#define PROBLEM_NAME "trading"

struct player_t {
  string name;
  string wants;
  map<string, int> has;
};

const int INF = 123456789;

#define residue(i,j) (cap[i][j] - flow[i][j])
vector< vector<int> > max_flow(vector< vector<int> > cap, int s, int t) {
  int n = cap.size();
  vector< vector<int> > flow(n, n);
  for(;;) {
    vector<int> trace(n, -1);
    queue<int> q;
    q.push(s);
    trace[s] = s;
    while(!q.empty()) {
      int cur = q.front();
      q.pop();
      REP(next, n) if (residue(cur, next) > 0 && trace[next] < 0) {
	trace[next] = cur;
	q.push(next);
      }
    }
    if (trace[t] < 0)
      break;
    int f = INF;
    for(int i = t; trace[i] != i; i = trace[i])
      f <?= residue(trace[i], i);
    for(int i = t; trace[i] != i; i = trace[i])
      flow[trace[i]][i] += f, flow[i][trace[i]] -= f;
  }
  return flow;
}

int main() {
  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int nPlayers, nResources, nBuildings;
  cin >> nPlayers >> nResources >> nBuildings;

  vector<string> resources(nResources);
  REP(i, nResources)
    cin >> resources[i];

  map<string, map<string, int> > buildings;
  REP(i, nBuildings) {
    string name;
    cin >> name;
    { string requires; cin >> requires >> ws; }
    string itemList;
    getline(cin, itemList);
    replace(ALLOF(itemList), ',', ' ');
    istringstream is(itemList);
    for(;;) {
      int nItems;
      string itemName;
      is >> nItems >> itemName;
      if (!is)
	break;
      buildings[name][itemName] = nItems;
    }
  }

  vector<player_t> players(nPlayers);
  REP(i, nPlayers) {
    cin >> players[i].name;
    { string wants; cin >> wants >> ws; }

    string itemList;
    getline(cin, itemList);
    replace(ALLOF(itemList), ',', ' ');

    istringstream is(itemList);
    is >> players[i].wants;
    { string has; is >> has >> ws; }
    for(;;) {
      int nItems;
      string itemName;
      is >> nItems >> itemName;
      if (!is)
	break;
      players[i].has[itemName] = nItems;
    }
  }

  int n = nResources + nPlayers + 2;
  int s = n-2;
  int t = n-1;
  vector< vector<int> > cap(n, n);
  REP(i, nResources) {
    cap[s][i] = players[0].has[resources[i]];
    cap[i][t] = buildings[players[0].wants][resources[i]];
  }

  REP(iResource, nResources) REP(iPlayer, nPlayers) {
    if (iPlayer == 0)
      continue;
    int kResource = iResource;
    int kPlayer = nResources + iPlayer;
    int need = buildings[players[iPlayer].wants][resources[iResource]] - players[iPlayer].has[resources[iResource]];
    if (need > 0)
      cap[kResource][kPlayer] = need;
    if (need < 0)
      cap[kPlayer][kResource] = -need;
  }

  vector< vector<int> > flow = max_flow(cap, s, t);

  bool success = true;
  REP(i, n)
    if (flow[i][t] != cap[i][t])
      success = false;

  if (!success) {
    cout << "No way" << endl;
    return 0;
  }

  for(;;) {
    int startItem = -1;
    REP(i, n)
      if (flow[s][i] > 0)
	startItem = i;
    if (startItem < 0)
      break;
    flow[s][startItem]--;
    int curItem;
    for(curItem = startItem; flow[curItem][t] == 0; ) {
      int nextPlayer = -1;
      REP(iPlayer, nPlayers) {
	int kPlayer = nResources + iPlayer;
	if (flow[curItem][kPlayer] > 0) {
	  flow[curItem][kPlayer]--;
	  nextPlayer = iPlayer;
	  break;
	}
      }
      assert(nextPlayer >= 0);
      int nextItem = -1;
      REP(iItem, nResources) {
	if (flow[nextPlayer+nResources][iItem] > 0) {
	  flow[nextPlayer+nResources][iItem]--;
	  nextItem = iItem;
	  break;
	}
      }
      assert(nextItem >= 0);
      cout << "trade with "
	   << players[nextPlayer].name
	   << " "
	   << resources[curItem]
	   << " for "
	   << resources[nextItem]
	   << endl;
      curItem = nextItem;
    }
    flow[curItem][t]--;
  }

  cout << "build " << players[0].wants << endl;

  return 0;
}

