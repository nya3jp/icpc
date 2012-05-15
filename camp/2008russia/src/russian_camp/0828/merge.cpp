#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "merge"

struct expr_t {
  expr_t() {}
  virtual ~expr_t() {}
  virtual bool prun(int k) = 0;
  virtual void print() = 0;
};

struct and_t : public expr_t {
  expr_t* l;
  expr_t* r;
  bool al, ar;
  bool p;
  and_t(expr_t* l, expr_t* r) : l(l), r(r), al(true), ar(true), p(false) {}
  virtual ~and_t() {}
  virtual bool prun(int k) {
    if (!p) {
      p = true;
      al = l->prun(k);
      ar = r->prun(k);
    }
    return al || ar;
  }
  virtual void print() {
    if (al && ar)
      printf("(");
    if (al)
      l->print();
    if (al && ar)
      printf("&");
    if (ar)
      r->print();
    if (al && ar)
      printf(")");
  }
};
struct or_t : public expr_t {
  expr_t* l;
  expr_t* r;
  bool al, ar;
  bool p;
  or_t(expr_t* l, expr_t* r) : l(l), r(r), al(true), ar(true), p(false) {}
  virtual ~or_t() {}
  virtual bool prun(int k) {
    if (!p) {
      p = true;
      al = l->prun(k);
      ar = r->prun(k);
    }
    return al || ar;
  }
  virtual void print() {
    if (al && ar)
      printf("(");
    if (al)
      l->print();
    if (al && ar)
      printf("|");
    if (ar)
      r->print();
    if (al && ar)
      printf(")");
  }
};
struct term_t : public expr_t {
  int t, i;
  int nn[2];
  term_t(int t, int i, int n, int m) : t(t), i(i) {
    nn[0] = n;
    nn[1] = m;
  }
  virtual ~term_t() {}
  virtual bool prun(int k) {
    if (k < i)
      return false;
    if (k > nn[t^1]+i)
      return false;
    return true;
  }
  virtual void print() {
    printf("%c%d", (t == 0 ? 'x' : 'y'), i+1);
  }
};

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int n, m;
  cin >> n >> m;

  vector<expr_t*> v;
  REP(i, n) {
    v.push_back(new term_t(0, i, n, m));
  }

  REP(i, m) {
    expr_t* t = new term_t(1, i, n, m);

    vector<expr_t*> u(n+i+1);
    for(int j = 0; j <= n+i; j++) {
      /*
      if (j == 0) {
	u[j] = new and_t(v[j], t);
      }
      else if (j == n+i) {
	u[j] = new or_t(v[j-1], t);
      }
      else if (i == j) {
	u[j] = new and_t(v[j], t);
      }
      else if (j < i) {
	u[j] = v[j];
      }
      else {
	u[j] = new and_t(new or_t(v[j-1], t), v[j]);
      }
      u[j]->prun(j);
      */
      /*
      if (j < i) {
	u[j] = v[j];
      }
      else if (j == i) {
	u[j] = new and_t(v[j], t);
      }
      else {
	if (j >= n) {
	  u[j] = new or_t(v[j-1], t);
	}
	else {
	  u[j] = new and_t(new or_t(v[j-1], t), new term_t(0, j, n, m));
	}
      }
      */
    }
    v.swap(u);
  }

  REP(i, n+m) {
    v[i]->print();
    cout << endl;
  }

  return 0;

  return 0;
}

