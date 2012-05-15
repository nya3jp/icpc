#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "sat"

#define N 310

bool g[N][N];
int clauses[N];
int nVariables, nClauses;

int matching[N];
bool visited[N];
int n, m;

bool augment(int left) {
  if (left < 0)
    return true;
  if (visited[left])
    return false;
  visited[left] = true;
  REP(right, m) {
    if (g[left][right]) {
      if (augment(matching[right])) {
	matching[right] = left;
	return true;
      }
    }
  }
  return false;
}

bool match(int nVariablesToMatch) {
  n = nClauses;
  m = nVariables;

  int types[] = {1, 0};
  int matches = 0;

  REP(i, m)
    matching[i] = -1;

  REP(t, 2) REP(iClause, nClauses) if (clauses[iClause] == types[t]) {
    memset(visited, 0, sizeof(visited));
    bool succ = augment(iClause);
    if (types[t] == 1 && !succ)
      return false;
    if (succ)
      matches++;
  }
  return (matches == nVariablesToMatch);
}

int main() {
  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  scanf("%d%d", &nVariables, &nClauses);

  int variables[nVariables][2];
  memset(variables, -1, sizeof(int)*nVariables*2);

  REP(iClause, nClauses) {
    int m;
    scanf("%d", &m);
    REP(i, m) {
      int a;
      scanf("%d", &a);
      int neg = (a < 0 ? 1 : 0);
      a = abs(a) - 1;
      variables[a][neg] = iClause;
    }
  }

  REP(i, nClauses)
    clauses[i] = 1;

  int nVariablesToMatch = 0;
  REP(i, nVariables) {
    if (variables[i][0] == variables[i][1]) {
      int c = variables[i][0];
      if (c >= 0) {
	if (clauses[c] < 0) {
	  puts("NO");
	  return 0;
	}
	clauses[c] = -1;
      }
    }
    else if (variables[i][0] < 0 || variables[i][1] < 0) {
      int c = max(variables[i][0], variables[i][1]);
      if (clauses[c] == 1)
	clauses[c] = 0;
    }
    else {
      int c0 = variables[i][0];
      int c1 = variables[i][1];
      g[c0][i] = g[c1][i] = true;
      nVariablesToMatch++;
    }
  }

  bool match_res = match(nVariablesToMatch);
  if (!match_res) {
    puts("NO");
    return 0;
  }

  puts("YES");

  bool clause_bool[nClauses];
  int assignments[nVariables];

  memset(clause_bool, 0, sizeof(bool)*nClauses);

  REP(i, nVariables) {
    if (matching[i] >= 0) {
      int c0 = variables[i][0];
      int c1 = variables[i][1];
      if (matching[i] == c0) {
	assignments[i] = 1;
	clause_bool[c0] = true;
      }
      else if (matching[i] == c1) {
	assignments[i] = 0;
	clause_bool[c1] = true;
      }
      else
	abort();
    }
  }

  REP(i, nVariables) {
    if (variables[i][0] == variables[i][1]) {
      int c = variables[i][0];
      if (c >= 0) {
	assignments[i] = 0;
	clause_bool[c] = true;
      }
      else {
	assignments[i] = 0;
      }
    }
    else if (variables[i][0] < 0 || variables[i][1] < 0) {
      int c = max(variables[i][0], variables[i][1]);
      int t = (c == variables[i][0] ? 1 : 0);
      if (clause_bool[c]) {
	assignments[i] = t^1;
      }
      else {
	assignments[i] = t;
	clause_bool[c] = true;
      }
    }
  }

  REP(i, nVariables)
    printf("%d%c", assignments[i], (i == nVariables-1 ? '\n' : ' '));

  return 0;
}

