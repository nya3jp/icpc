#include <iostream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)


#define PROBLEM_NAME "permutations"

#define N 100000

int n, mod;
int perm[N];
bool visited[N];
int loops[N+10];

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  scanf("%d%d", &n, &mod);
  
  REP(i, n){
    int a;
    scanf("%d", &a);
    a--;
    perm[a] = i;
  }
  
  REP(i, n){
    if(visited[i])
      continue;
    long long loopSize = 0;
    for(int cur = i; !visited[cur]; cur = perm[cur]){
      loopSize++;
      visited[cur] = true;
    }
    loops[loopSize]++;
  }
  
  long long res = 1;
  for(int loopSize = 1; loopSize <= n; ++loopSize){
    int nLoops = loops[loopSize];
    REP(j, nLoops)
      res = (res * loopSize) % mod;
    while(nLoops > 0)
      res = (res * nLoops--) % mod;
  }
  cout << res << endl;
  
  return 0;
}
