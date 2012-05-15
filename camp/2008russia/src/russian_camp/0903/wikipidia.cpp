#include <cstdio>
#include <iostream>
#include <climits>
#include <algorithm>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

#define PROBLEM_NAME "wikipidia"

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

char s[100000+100];
int n;
int dp[100000+100][5][1+1+1];

enum {
  ITALIC = -1,
  BOLD = -2,
};

const int TRANS[5][2] = {
  {2, 1},
  {3, 0},
  {0, 4},
  {1, -1},
  {-1, 2},
};

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  gets(s);
  n = strlen(s);
  reverse(s, s+n);

  memset(dp, -1, sizeof(dp));
  dp[0][0][0] = 0;
  dp[0][0][1] = 0;
  dp[0][0][2] = 0;

  REP(pos, n) {
    REP(state, 5) {
      if (dp[pos][state][0] >= 0) {
	if (s[pos] == '\'') {
	  if (s[pos+1] == '\'') {
	    if (TRANS[state][0] >= 0) {
	      dp[pos+2][TRANS[state][0]][0] = pos;
	      dp[pos+2][TRANS[state][0]][1] = state;
	      dp[pos+2][TRANS[state][0]][2] = ITALIC;
	    }
	    if (s[pos+2] == '\'') {
	      if (TRANS[state][1] >= 0) {
		dp[pos+3][TRANS[state][1]][0] = pos;
		dp[pos+3][TRANS[state][1]][1] = state;
		dp[pos+3][TRANS[state][1]][2] = BOLD;
	      }
	    }
	  }
	}
	else {
	  dp[pos+1][state][0] = pos;
	  dp[pos+1][state][1] = state;
	  dp[pos+1][state][2] = (int)s[pos];
	}
      }
    }
  }

  /*
  REP(i, n+1) {
    REP(j, 5)
      fprintf(stderr, "{%d %d %d} ", dp[i][j][0], dp[i][j][1], dp[i][j][2]);
    fprintf(stderr, "\n");
  }
  */

  if (dp[n][0][0] >= 0) {
    int pos = n;
    int state = 0;
    while(pos > 0) {
      //fprintf(stderr, "(%d,%d)\n", pos, state);
      int c = dp[pos][state][2];
      if (c == ITALIC) {
	if (state == 2 || state >= 3)
	  printf("</i>");
	else
	  printf("<i>");
      }
      else if (c == BOLD) {
	if (state == 1 || state >= 3)
	  printf("</b>");
	else
	  printf("<b>");
      }
      else {
	printf("%c", (char)c);
      }
      int newpos = dp[pos][state][0];
      int newstate = dp[pos][state][1];
      pos = newpos;
      state = newstate;
    }
    puts("");
  }
  else {
    puts("!@#$%");
  }

  return 0;
}

