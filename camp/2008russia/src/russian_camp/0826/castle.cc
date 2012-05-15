#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) (c).begin(), (c).end()

#define N 20

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
    scanf("%d%d%d", &e.hp, &e.dms, &e.exp);
  }

  memset(trace, -1, sizeof(trace));
  trace[0] = 12345;

  REP(beaten, 1<<nEnemies) {
    if (trace[beaten] < 0)
      continue;
    int ex = 0;
    REP(j, nEnemies)
      if (beaten & (1<<j))
	ex += enemies[j].exp;
    int level = upper_bound(levels, levels+nLevels, ex) - levels - 1;
    int hp = hps[level], atk = attacks[level], res = cures[level];
    REP(iEnemy, nEnemies) {
      if (beaten&(1<<iEnemy))
	continue;
      Enemy& e = enemies[iEnemy];
      int my = atk;
      int your = e.dmg - res;
      int turns = (e.hp + my - 1) / my;
      int 
    }
  }

  return 0;
}

