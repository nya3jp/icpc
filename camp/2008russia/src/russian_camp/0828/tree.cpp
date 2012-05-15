#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "tree"

char res[2048][2048];

struct expr_t {
  expr_t() {}
  virtual ~expr_t() {}
  virtual void write(int top, int left, int& right, int& center) = 0;
};
struct term_t : public expr_t {
  char c;
  term_t(char c) : c(c) {}
  virtual ~term_t() {}
  virtual void write(int top, int left, int& right, int& center) {
    res[top][left] = c;
    right = left+1;
    center = left;
  }
};
struct op_t : public expr_t {
  char op;
  expr_t* l;
  expr_t* r;
  op_t(char op, expr_t* l, expr_t* r) : op(op), l(l), r(r) {}
  virtual ~op_t() {}
  virtual void write(int top, int left, int& right, int& center) {
    int lright, lcenter, rcenter;
    l->write(top+2, left, lright, lcenter);
    center = lright + 2;
    r->write(top+2, lright+5, right, rcenter);
    res[top+1][lcenter] = res[top+1][rcenter] = '|';
    res[top][lcenter] = res[top][rcenter] = '.';
    for(int i = lcenter+1; i < rcenter; i++)
      res[top][i] = '-';
    res[top][center-1] = '[';
    res[top][center] = op;
    res[top][center+1] = ']';
  }
};



expr_t* parse_expr(char*& p);

expr_t* parse_item(char*& p) {
  expr_t* e;
  if (*p == '(') {
    p++;
    e = parse_expr(p);
    assert(*p == ')');
    p++;
  }
  else {
    e = new term_t(*p++);
  }
  return e;
}

expr_t* parse_factor(char*& p) {
  expr_t* e = parse_item(p);
  while(*p == '^') {
    char op = *p++;
    expr_t* r = parse_factor(p);
    e = new op_t(op, e, r);
  }
  return e;
}

expr_t* parse_term(char*& p) {
  expr_t* e = parse_factor(p);
  while(*p == '*' || *p == '/') {
    char op = *p++;
    expr_t* r = parse_factor(p);
    e = new op_t(op, e, r);
  }
  return e;
}

expr_t* parse_expr(char*& p) {
  expr_t* e = parse_term(p);
  while(*p == '+' || *p == '-') {
    char op = *p++;
    expr_t* r = parse_term(p);
    e = new op_t(op, e, r);
  }
  return e;
}


int main() {
  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  char str[1024];
  gets(str);
  char* p = str;

  expr_t* e = parse_expr(p);

  memset(res, ' ', sizeof(res));
  int width, center;
  e->write(0, 0, width, center);

  int i = 0;
  for(;;) {
    int j = 2047;
    while(j > 0 && res[i][j-1] == ' ')
      j--;
    if (j == 0)
      break;
    res[i][j] = '\0';
    puts(res[i]);
    i++;
  }

  return 0;
}

