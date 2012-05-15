#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "pattern"

int n;
char str[4096];
int mapping[4096][26];
int mapping_cnt[4096][26];
int appears[4096];
int best = 0;
int bestlen;
char* beststr;

void go(int* cands, int m, int len) {

  if (m == 0)
    return;

  if (m == 1)
    len = n - cands[0];

  if (len*m > best) {
    best = len*m;
    bestlen = len;
    beststr = str + cands[0];
  }

  if (m == 1)
    return;

  int cnt[26] = {0};
  REP(i, m) {
    int a = cands[i];
    char c = str[a+len];
    if (c == '\0')
      continue;
    int k = c - 'a';
    if (mapping_cnt[a][k]++ == 0)
      mapping[a][k] = appears[a]++;
    cnt[mapping[a][k]]++;
  }

  int all = accumulate(cnt, cnt+26, (int)0);
  int* v = new int[all];
  int* ptrs[26];

  ptrs[0] = v;
  for(int i = 1; i < 26; i++)
    ptrs[i] = ptrs[i-1] + cnt[i-1];

  REP(i, m) {
    int a = cands[i];
    char c = str[a+len];
    if (c == '\0')
      continue;
    int k = c - 'a';
    *ptrs[mapping[a][k]]++ = a;
  }

  ptrs[0] = v;
  for(int i = 1; i < 26; i++)
    ptrs[i] = ptrs[i-1] + cnt[i-1];

  REP(i, 26)
    go(ptrs[i], cnt[i], len+1);

  REP(i, m) {
    int a = cands[i];
    char c = str[a+len];
    if (c == '\0')
      continue;
    int k = c - 'a';
    if (--mapping_cnt[a][k] == 0) {
      mapping[a][k] = -1;
      appears[a]--;
    }
  }
}

int main() {
  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  gets(str);
  n = strlen(str);
  memset(mapping, -1, sizeof(mapping));
  memset(mapping_cnt, 0, sizeof(mapping_cnt));

  int* init = new int[n];
  REP(i, n)
    init[i] = i;
  go(init, n, 0);

  beststr[bestlen] = '\0';
  puts(beststr);

  cerr << "finished" << endl;

  return 0;
}

