#include <cstdio>
#include <iostream>
#include <climits>
#include <algorithm>
#include <deque>

using namespace std;

#define PROBLEM_NAME "prefixes"

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

char str[500000+10];

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  deque<char> q;

  gets(str);
  char* p = str;
  q.push_front(*p++);

  while(*p != '\0') {
    if (*p <= q.front())
      q.push_front(*p);
    else
      q.push_back(*p);
    p++;
  }

  cout << string(ALLOF(q)) << endl;

  return 0;
}

