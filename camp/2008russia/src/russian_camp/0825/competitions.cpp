#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <complex>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "competitions"

#define BIG 20000000

struct Event {
  long long time;
  int nextStage;
  int id;
  int ride;
  int strength;
};

bool operator<(const Event& a, const Event& b) {
  if (a.time != b.time)
    return (a.time > b.time);
  return (a.strength < b.strength);
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, m;
  scanf("%d%d", &n, &m);

  priority_queue<Event> q;
  REP(i, n) {
    int swim, ride, strength;
    scanf("%d%d%d", &swim, &ride, &strength);
    q.push((Event){BIG-swim, 0, i+1, ride, strength});
  }

  int A[m], B[n];
  REP(i, m)
    scanf("%d", &A[i]);
  REP(j, n)
    scanf("%d", &B[j]);

  int** horses = new int*[m];
  REP(i, m)
    horses[i] = new int[n];

  REP(i, m) REP(j, n) {
    horses[i][j] = 3*A[i]*A[i] + 5*A[i]*B[j] + 2*B[j]*B[j];
  }
  REP(i, m)
    sort(horses[i], horses[i]+n, greater<int>());

  vector<int> res;
  while(!q.empty()) {
    Event e = q.top();
    q.pop();
    if (e.nextStage == m) {
      // goal
      res.push_back(e.id);
    }
    else {
      int h = *horses[e.nextStage]++;
      q.push((Event){e.time+BIG-e.ride-h, e.nextStage+1, e.id, e.ride, e.strength});
    }
  }

  REP(i, n) {
    if (i > 0)
      printf(" ");
    printf("%d", res[i]);
  }
  printf("\n");

  return 0;
}
