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

#define PROBLEM_NAME "elevator"

bool go(vector<int> building, int capacity, int rescue, long long int energy) {
  int n = building.size();

  {
    int remain = rescue;
    REP(i, n) {
      int lo = min(remain, building[i]);
      building[i] = lo;
      remain -= lo;
    }
  }

  //cout << "trying " << rescue << endl;

  int fl = n-1;
  while(rescue > 0) {
    while(fl >= 0 && building[fl] == 0)
      fl--;
    assert(fl >= 0);
    //cout << "start from floor " << fl+1 << endl;
    if (building[fl]/capacity >= 1) {
      int times = building[fl]/capacity;
      energy -= (long long)(fl+1)*times;
      rescue -= capacity * times;
      building[fl] -= capacity*times;
    }
    else {
      energy -= fl+1;
      int remain = capacity;
      while(fl >= 0 && remain > 0) {
	int lo = min(building[fl], remain);
	//cout << " rescue " << lo << " from floor " << fl+1 << endl;
	remain -= lo;
	rescue -= lo;
	building[fl] -= lo;
	if (remain == 0)
	  break;
	fl--;
      }
    }
    //cout << " done" << endl;
  }
  return (energy >= 0);
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, capacity, cost, time;
  cin >> n >> capacity >> cost >> time;

  int energy = time / cost / 2;

  vector<int> building(n);
  REP(i, n)
    cin >> building[i];

  int lo = 0, hi = accumulate(ALLOF(building), (int)0);
  while(lo < hi) {
    int mid = (lo+hi+1)/2;
    if (go(building, capacity, mid, energy))
      lo = mid;
    else
      hi = mid-1;
  }
  cout << lo << endl;

  return 0;
}
