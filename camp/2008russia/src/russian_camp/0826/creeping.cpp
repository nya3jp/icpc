#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) (c).begin(), (c).end()

#define N 20

int memo[1<<N];
int trace[1<<N];
int levels[110];
int hps[110];
int attacks[110];
int cures[110];

struct Enemy {
  int hp, dmg, exp;
};

Enemy enemies[N];

int main() {

  if (!freopen("creeping.in", "r", stdin))
    abort();
  if (!freopen("creeping.out", "w", stdout))
    abort();

  int nEnemies, nLevels;
  scanf("%d%d", &nEnemies, &nLevels);

  REP(i, nLevels) {
    scanf("%d%d%d%d",
	  &levels[i], &hps[i], &attacks[i], &cures[i]);
  }

  REP(i, nEnemies) {
    Enemy& e = enemies[i];
    scanf("%d%d%d", &e.hp, &e.dmg, &e.exp);
  }

  REP(i, 1<<nEnemies)
    memo[i] = 1234567;

  memset(trace, -1, sizeof(trace));
  memo[0] = 0;

  REP(beaten, 1<<nEnemies) {
    int ex = 0;
    REP(j, nEnemies)
      if (beaten & (1<<j))
	ex += enemies[j].exp;
    int level = upper_bound(levels, levels+nLevels, ex) - levels - 1;
    int hp = hps[level], atk = attacks[level], res = cures[level];

    if (memo[beaten] >= hp) {
      memo[beaten] = -1;
      continue;
    }

    REP(iEnemy, nEnemies) {
      if (beaten&(1<<iEnemy))
	continue;
      Enemy& e = enemies[iEnemy];
      int my = atk;
      int your = e.dmg - res;
      int turns = (e.hp + my - 1) / my;
      long long nextmemo = /*memo[beaten] + */(long long)your * turns;
      if (nextmemo >= hp)
	continue;
      if (nextmemo < 0)
	nextmemo = 0;
      if (nextmemo < memo[beaten|(1<<iEnemy)]) {
	memo[beaten|(1<<iEnemy)] = nextmemo;
	trace[beaten|(1<<iEnemy)] = iEnemy;
      }
    }
  }

  /*
  REP(p, 1<<nEnemies) {
    printf("%d: %d\n", p, memo[p]);
  }
  */

  int best = 0;
  int bestex = 0;
  REP(beaten, 1<<nEnemies) {
    if (memo[beaten] >= 0) {
      int ex = 0;
      REP(j, nEnemies)
	if (beaten & (1<<j))
	  ex += enemies[j].exp;
      if (ex > bestex) {
	best = beaten;
	bestex = ex;
      }
    }
  }

  vector<int> route;
  for(int p = best; p > 0; p &= ~(1<<trace[p])) {
    route.push_back(trace[p]);
  }
  reverse(ALLOF(route));

  printf("%d\n", bestex);
  printf("%d\n", route.size());
  REP(i, route.size())
    printf("%d%c", route[i]+1, (i == route.size()-1 ? '\n' : ' ' ));

  return 0;
}

