#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <complex>
#include <numeric>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "fisher"

const double INF = 1e100;

struct boat_t {
  int start;
  int period;
  int coming;
  int coming2;
};

int h, w;
int field[500][500];
boat_t boat[500][500];
int peter[500][500];

int DIR[4][2] = {
  {-1, 0},
  {1, 0},
  {0, 1},
  {0, -1}
};

double res = INF;

inline bool valid(int i, int j) {
  return (0 <= i && i < h && 0 <= j && j < w);
}

void niceBoat(int si, int sj) {
  memset(boat, -1, sizeof(boat));

  boat[si][sj] = (boat_t){0, 0, -1};
  int ci = si, cj = sj;
  int t = 0;
  for(;;) {
    //cerr << "now (" << ci << "," << cj << ")" << endl;
    int dir = field[ci][cj];
    if (dir < 0) {
      // float
      boat[ci][cj].period = 1;
      boat[ci][cj].coming2 = -1;
      break;
    }
    else {
      // move
      int ni = ci + DIR[dir][0], nj = cj + DIR[dir][1];
      //cerr << "moving to (" << ni << "," << nj << ")" << endl;
      if (!valid(ni, nj)) {
	//cerr << " out of range" << endl;
	// go out
	break;
      }
      else if (boat[ni][nj].start < 0) {
	//cerr << " first visit" << endl;
	// first visit
	t += 2;
	boat[ni][nj].start = t;
	boat[ni][nj].period = 0;
	boat[ni][nj].coming = dir^1;
	boat[ni][nj].coming2 = dir^1;
      }
      else {
	//cerr << " second visit!" << endl;
	// second visit
	int pi = ni, pj = nj;
	int period = 0;
	do {
	  int ppi = pi + DIR[field[pi][pj]][0];
	  int ppj = pj + DIR[field[pi][pj]][1];
	  pi = ppi;
	  pj = ppj;
	  period+=2;
	} while(!(pi == ni && pj == nj));
	do {
	  boat[pi][pj].period = period;
	  int ppi = pi + DIR[field[pi][pj]][0];
	  int ppj = pj + DIR[field[pi][pj]][1];
	  boat[ppi][ppj].coming2 = field[pi][pj]^1;
	  pi = ppi;
	  pj = ppj;
	} while(!(pi == ni && pj == nj));
	break;
      }
      ci = ni, cj = nj;
    }
  }

}


struct Peter {
  int time;
  int i, j;
};
bool operator<(const Peter& a, const Peter& b) {
  return (a.time > b.time);
}

void nicePeter(int si, int sj) {

  memset(peter, -1, sizeof(peter));
  priority_queue<Peter> q;
  q.push((Peter){0, si, sj});

  while(!q.empty()) {
    Peter cur = q.top();
    q.pop();
    if (peter[cur.i][cur.j] < 0) {
      peter[cur.i][cur.j] = cur.time;
      int fdir = field[cur.i][cur.j];
      REP(sdir, 4) {
	int di = DIR[fdir][0] + DIR[sdir][0];
	int dj = DIR[fdir][1] + DIR[sdir][1];
	int cost = 2;
	if (fdir == sdir) {
	  cost = 1;
	  di /= 2;
	  dj /= 2;
	}
	Peter next = {cur.time + cost,
		      cur.i + di,
		      cur.j + dj};
	if (!valid(next.i, next.j)) {
	  res <?= (cur.time + cost*0.5) * 0.5;
	}
	else if (peter[next.i][next.j] < 0) {
	  q.push(next);
	}
      }
    }
  }

}



void helpMePeter() {
  REP(hi, h) REP(hj, w) {
    int peterTime = peter[hi][hj];
    if (peterTime < 0)
      continue;
    if (boat[hi][hj].start < 0)
      continue;
    int cdir;
    int boatTime;
    printf("peterTime=%d, start=%d, period=%d\n", peterTime, boat[hi][hj].start, boat[hi][hj].period);
    if (peterTime <= boat[hi][hj].start) {
      cdir = boat[hi][hj].coming;
      boatTime = boat[hi][hj].start;
    }
    else if (boat[hi][hj].period > 0) {
      cdir = boat[hi][hj].coming2;
      boatTime = (peterTime - boat[hi][hj].start + boat[hi][hj].period - 1)/boat[hi][hj].period*boat[hi][hj].period + boat[hi][hj].start;
    }
    else {
      continue;
    }
    printf("%d,%d boattime=%d\n", hi, hj, boatTime);
    if (boatTime == peterTime) {
      res <?= peterTime * 0.5;
      continue;
    }
    else {
      res <?= boatTime * 0.5;
      int fdir = field[hi][hj];
      if (fdir == cdir && fdir != -1) {
	if (peterTime % 2 == 0)
	  res <?= peterTime * 0.5 + 1.0/3.0;
	else
	  res <?= peterTime * 0.5 + 1.0/6.0;
      }
    }
  }
}


int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  scanf("%d%d", &h, &w);

  REP(i, h) REP(j, w) {
    char c;
    scanf(" %c", &c);
    field[i][j] = (int)(c - '1');
  }

  int si, sj, ti, tj;
  scanf("%d%d%d%d", &sj, &si, &tj, &ti);
  si--; sj--;
  ti--; tj--;

  //printf("%d,%d\n", ti, tj);
  niceBoat(ti, tj);

  REP(i, h) {
    REP(j, w) {
      printf("%d+%dn ", boat[i][j].start, boat[i][j].period);
    }
    puts("");
  }

  nicePeter(si, sj);

  /*
  REP(i, h) {
    REP(j, w) {
      printf("%d ", peter[i][j]);
    }
    puts("");
  }
  */

  helpMePeter();

  if (res == INF)
    printf("SOS\n");
  else
    printf("%.2f\n", res);

  return 0;
}
