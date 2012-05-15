#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "pattern"

#define MOD 10000037
#define A   3
#define B   34247

int lens[MOD];
int memo[MOD];
char str[4096];
int n;

int main() {
  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  scanf("%s", str);
  n = strlen(str);
  REP(s, n) {
    int h = 0;
    int mapping[26];
    memset(mapping, -1, sizeof(mapping));
    int appeared = 0;
    for(int i = s; i < n; i++) {
      if (mapping[str[i]-'a'] < 0)
	mapping[str[i]-'a'] = appeared++;
      int k = mapping[str[i]-'a'];
      h = (int)(((long long)h * A + k + B) % MOD);
      //cout << string(str+s, str+i+1) << ": " << h << endl;
      if (lens[h] > 0 && lens[h] != i-s+1) {
	//for(;;);
	lens[h] = 1;
	memo[h] = 0;
      }
      lens[h] = i-s+1;
      memo[h]++;
    }
  }

  int best = 0;
  REP(h, MOD) {
    if (lens[h] * memo[h] > lens[best] * memo[best]) {
      best = h;
    }
  }

  REP(s, n) {
    int h = 0;
    int mapping[26];
    memset(mapping, -1, sizeof(mapping));
    int appeared = 0;
    for(int i = s; i < n; i++) {
      if (mapping[str[i]-'a'] < 0)
	mapping[str[i]-'a'] = appeared++;
      int k = mapping[str[i]-'a'];
      h = (int)(((long long)h * A + k + B) % MOD);
      if (h == best) {
	str[i+1] = '\0';
	puts(str+s);
	return 0;
      }
    }
  }

  puts("");

  return 0;
}

