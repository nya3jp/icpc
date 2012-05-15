#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "chip"

#define INCONSISTENT "inconsistent"

char res[600][600];

int main() {
  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int h, w, len;
  scanf("%d%d%d", &h, &w, &len);

  int a[h], b[w];
  REP(i, h) {
    scanf("%d", &a[i]);
    a[i] = w - a[i];
  }
  REP(j, w)
    scanf("%d", &b[j]);

  memset(res, '*', sizeof(res));

  {
    int sum = 0;
    REP(i, h)
      sum += a[i];
    REP(j, w)
      sum -= b[j] * len;
    if (sum != 0) {
      puts(INCONSISTENT);
      //cerr << 1 << endl;
      return 0;
    }
  }

  priority_queue< pair<int,int> > q;
  queue< vector< pair<int, int> > > recover;
  REP(j, w)
    q.push(make_pair(b[j], j));

  REP(i, len)
    recover.push(vector< pair<int, int> >());

  REP(i, h) {
    {
      vector< pair<int,int> >& rec = recover.front();
      REP(j, rec.size())
	q.push(rec[j]);
      recover.pop();
    }
    int k = a[i];
    vector< pair<int,int> > trush;
    REP(j, k) {
      pair<int,int> t = q.top();
      q.pop();
      if (t.first == 0) {
	puts(INCONSISTENT);
	//cerr << 2 << endl;
	return 0;
      }
      t.first--;
      int ci = i, cj = t.second;
      //fprintf(stderr, "place at (%d,%d)-(%d,%d)\n",
      //ci, cj, ci+len-1, cj);
      if (ci+len-1 >= h) {
	puts(INCONSISTENT);
	//cerr << 3 << endl;
	return 0;
      }
      REP(l, len)
	res[ci+l][cj] = '|';
      res[ci][cj] = '+';
      res[ci+len-1][cj] = '+';
      trush.push_back(t);
      for(int ii = i + 1; ii < i+len; ii++) {
	a[ii]--;
	if (a[ii] < 0) {
	  puts(INCONSISTENT);
	  //cerr << 4 << endl;
	  return 0;
	}
      }
    }
    recover.push(trush);
  }

  REP(i, h) {
    res[i][w] = '\0';
    puts(res[i]);
  }

  return 0;
}

