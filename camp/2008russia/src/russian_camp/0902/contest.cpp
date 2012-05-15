#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)


#define PROBLEM_NAME "contest"

#define N 100

int n, m, mod;
int winners[N+10];
int memo[N+10][N+10];

inline int mul(int a, int b) {
  return ((long long) a * b) % mod;
}


int choose(int n, int k) {
  if (k == 0)
    return 1;
  if (n == 0)
    return 0;
  int& res = memo[n][k];
  if (res == -1)
    res = (choose(n-1, k) + choose(n-1, k-1)) % mod;
  return res;
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();
  
  memset(memo, -1, sizeof(memo));
  
  cin >> n >> m >> mod;

//   for(int i = 1; i <= 20; ++i){
//     for(int j = 1; j <= i; ++j){
//       cerr << choose(i, j) << " ";
//     }
//     cerr << endl;
//   }
  
  REP(i, m){
    cin >> winners[i];
    winners[i]--;
  }
  sort(winners, winners + m);
  reverse(winners, winners + m);
  
  int toChoose = n / m - 1;
  int rest = 0;
  int res = 1;
  REP(iWinner, m){
    int winner = winners[iWinner];
    if(iWinner > 0)
      rest += winners[iWinner-1]-1 - winner;
    else
      rest += n-1 - winner;
    
    if(rest < toChoose){
      cout << -1 << endl;
      return 0;
    }
    
    res = mul(res, choose(rest, toChoose));
    rest -= toChoose;
  }
  
  cout << res << endl;
  
  return 0;
}
