#include <cstdio>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

#define PROBLEM_NAME "rmq"

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

struct Query {
  int from, to, a;
};

struct Tree {
  Tree* left;
  Tree* right;
  int from, mid, to;
  int value;
  Tree(int from, int to, int value) : from(from), to(to), value(value) {
    if (to-from > 1) {
      mid = (from+to)/2;
      left = new Tree(from, mid, value);
      right = new Tree(mid, to, value);
    }
    else {
      mid = -1;
      left = right = NULL;
    }
  }
  void maximize(int newfrom, int newto, int newvalue) {
    //fprintf(stderr, "maximize(%d,%d,%d) on (%d,%d,%d)\n", newfrom, newto, newvalue, from, mid, to);
    if (newfrom == newto) {
    }
    else if (newfrom == from && to == newto) {
      value >?= newvalue;
    }
    else {
      if (newfrom < mid) {
	left->maximize(newfrom, min(newto, mid), newvalue);
      }
      if (mid < newto) {
	right->maximize(max(newfrom, mid), newto, newvalue);
      }
    }
  }
  int apply(int maxi = INT_MIN) {
    maxi >?= value;
    int mini = INT_MAX;
    if (mid >= 0) {
      mini <?= left->apply(maxi);
      mini <?= right->apply(maxi);
    }
    else {
      mini = maxi;
    }
    return value = mini;
  }
  int range_min(int newfrom, int newto) {
    int res = INT_MAX;
    if (newfrom == newto) {
    }
    else if (newfrom == from && to == newto) {
      res = value;
    }
    else {
      if (newfrom < mid)
	res <?= left->range_min(newfrom, min(newto, mid));
      if (mid < newto)
	res <?= right->range_min(max(newfrom, mid), newto);
    }
    return res;
  }
  void debug_print(int depth = 0) {
    cerr << string(depth, ' ') << value << endl;
    if (mid >= 0) {
      left->debug_print(depth+1);
      right->debug_print(depth+1);
    }
  }
  void print(bool last = true) {
    if (mid < 0) {
      printf("%d", value);
      if (last)
	printf("\n");
      else
	printf(" ");
    }
    else {
      left->print(false);
      right->print(last);
    }
  }
};

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, m;
  scanf("%d%d", &n, &m);

  Query* queries = new Query[m];
  REP(i, m) {
    Query& q = queries[i];
    scanf("%d%d%d", &q.from, &q.to, &q.a);
    q.from--;
  }

  Tree* root = new Tree(0, n, INT_MIN);
  //cerr << "hoge" << endl;

  REP(i, m) {
    Query& q = queries[i];
    root->maximize(q.from, q.to, q.a);
  }
  //root->debug_print();
  //cerr << "hoge" << endl;
  root->apply();
  //root->debug_print();
  //cerr << "hoge" << endl;
  REP(i, m) {
    Query& q = queries[i];
    //fprintf(stderr, "query%d: %d\n", i, root->range_min(q.from, q.to));
    if (root->range_min(q.from, q.to) != q.a) {
      puts("inconsistent");
      return 0;
    }
  }
  //cerr << "hoge" << endl;
  puts("consistent");
  root->print();

  return 0;
}

