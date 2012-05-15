#include <iostream>
#include <cstdio>
#include <complex>
#include <cstring>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

#define for if(0);else for
#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "asterisk"

int n;
int seq[10010];

/*
char res[100000+10];
char* p;
bool appear[10010];

bool solve(int left, int right, int from, int to) {
  int m = right-left;
  bool ok = true;
  REP(i, m) {
    if (seq[left+i] != from+i) {
      ok = false;
      break;
    }
  }
  if (ok) {
    // as-is
    p += sprintf(p, "(%d", seq[left]+1);
    for(int i = 1; i < m; i++)
      p += sprintf(p, ",%d", seq[left+i]+1);
    p += sprintf(p, ")");
    return true;
  }

  REP(i, m)
    appear[from+i] = false;

  p += sprintf(p, "(");
  int s = 0;
  int last = 0;
  REP(i, m) {
    appear[seq[right-1-i]] = true;
    while(appear[from+s])
      s++;
    if (s == i+1) {
      int cur = i+1;
      if (last == 0 && cur == m) {
	// not reversible
	return false;
      }
      if (!solve(right-cur, right-last, from+last, from+cur))
	return false;
      if (cur < m)
	p += sprintf(p, "*");
      last = cur;
    }
  }
  p += sprintf(p, ")");

  return true;
}
*/

struct node_t {
  node_t() {}
  virtual ~node_t() {}
  virtual int from() = 0;
  virtual int to() = 0;
  virtual void print(bool first = true) = 0;
};

struct asterisk_t : public node_t {
  node_t* l;
  node_t* r;
  int f, t;
  asterisk_t(node_t* l, node_t* r) : l(l), r(r) {
    f = l->from();
    t = r->to();
  }
  virtual ~asterisk_t() {}
  virtual int from() {
    return f;
  }
  virtual int to() {
    return t;
  }
  virtual void print(bool first) {
    l->print();
    printf("*");
    r->print();
  }
};

struct cons_t : public node_t {
  node_t* car;
  node_t* cdr;
  int f, t;
  cons_t(node_t* car, node_t* cdr) : car(car), cdr(cdr) {
    f = car->from();
    t = (cdr ? cdr->to() : car->to());
  }
  virtual int from() {
    return f;
  }
  virtual int to() {
    return t;
  }
  virtual void print(bool first) {
    if (first)
      printf("(");
    car->print(false);
    if (cdr) {
      printf(",");
      cdr->print(false);
    }
    if (first) {
      printf(")");
    }
  }
};

struct number_t : public node_t {
  int n;
  number_t(int n) : n(n) {}
  virtual ~number_t() {}
  virtual int from() { return n; }
  virtual int to() { return n; }
  virtual void print(bool first) {
    printf("%d", n);
  }
};

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  scanf("%d", &n);
  REP(i, n) {
    scanf("%d", &seq[i]);
  }

  /*
  p = res;
  if (solve(0, n, 0, n)) {
    p--;
    *p = '\0';
    puts(res+1);
  }
  else {
    puts("IMPOSSIBLE");
  }
  */

  vector<node_t*> st;
  REP(iSeq, n) {
    node_t* next = new cons_t(new number_t(seq[iSeq]), NULL);
    while(!st.empty()) {
      node_t* last = st.back();
      if (last->to() + 1 == next->from()) {
	st.pop_back();
	next = new cons_t(last, next);
      }
      else if (next->to() + 1 == last->from()) {
	st.pop_back();
	next = new asterisk_t(next, last);
      }
      else {
	break;
      }
    }
    st.push_back(next);
  }

  if (st.size() == 1) {
    st.back()->print();
    puts("");
  }
  else {
    puts("IMPOSSIBLE");
  }

  return 0;
}

