#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <string>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cassert>

using namespace std;

#define DEBUG
#undef DEBUG

#define REP(i,n) if(0);else for(int i = 0; i <(int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

// type definitions

#define N 100

//typedef vector<bool> Subset;
typedef int SubsetI;
/*
typedef bitset<100> Subset;
/*/
struct Subset {
    bool v[112];
    Subset() {
        clear();
    }
    inline void clear() {
        memset(v, 0, sizeof(v));
    }
    inline bool& operator[](int i) {
        return v[i];
    }
    inline bool operator==(const Subset& rhs) {
        return (memcmp(v, rhs.v, sizeof(v[0])*100) == 0);
    }
    inline Subset& operator|=(const Subset& rhs) {
        int* p = reinterpret_cast<int*>(v);
        const int* q = reinterpret_cast<const int*>(rhs.v);
        for(int i = 0; i < 28; i += 4) {
            p[i] |= q[i];
            p[i+1] |= q[i+1];
            p[i+2] |= q[i+2];
            p[i+3] |= q[i+3];
        }
        return *this;
    }
    inline Subset& operator&=(const Subset& rhs) {
        int* p = reinterpret_cast<int*>(v);
        const int* q = reinterpret_cast<const int*>(rhs.v);
        for(int i = 0; i < 28; i += 4) {
            p[i] &= q[i];
            p[i+1] &= q[i+1];
            p[i+2] &= q[i+2];
            p[i+3] &= q[i+3];
        }
        return *this;
    }
};
bool operator<(const Subset& lhs, const Subset& rhs) {
    return lexicographical_compare(lhs.v, lhs.v+N, rhs.v, rhs.v+N);
}
//*/
typedef vector<int> Edges;
typedef vector<Edges> Graph;


// global variables

Graph g, r;
int n, m; // number of nodes, size of scope
vector<int> order; // topological order of g
vector<Subset> scope;
vector<Subset> lowers;
vector<int> literals;
vector<class Expr*> garbage;
Subset used_literals;
Subset logic_false, logic_true;

int logic_and_table[N][N];
int logic_or_table[N][N];
int logic_imply_table[N][N];
int logic_equiv_table[N][N];
int logic_not_table[N];

void dfs(int here, Subset& visited) {
    if (visited[here])
        return;
    visited[here] = true;
    Edges& v = g[here];
    REP(i, v.size()) {
        int there = v[i];
        dfs(there, visited);
    }
}

void rdfs(int here, Subset& visited) {
    if (visited[here])
        return;
    visited[here] = true;
    Edges& v = r[here];
    REP(i, v.size()) {
        int there = v[i];
        rdfs(there, visited);
    }
}



// Subset functions

void subset_print(Subset& s) {
    printf("[");
    REP(i, n)
        printf("%d", (s[i] ? 1 : 0));
    printf("]");
}


// Logical functions

void logic_max(Subset& s) {
    //Subset t(n, false);
    Subset t; // BITSET
    REP(i, n) {
        if (s[i]) {
            Edges& v = r[i];
            REP(j, v.size())
                rdfs(v[j], t);
        }
    }
    REP(i, n)
        s[i] = s[i] && !t[i];
}

void logic_and(Subset& s, Subset& lhs, Subset& rhs) {
    //subset_or(s, lhs, rhs);
    s = lhs;
    s |= rhs;
    logic_max(s);
}

void logic_or(Subset& s, Subset& lhs, Subset& rhs) {
    //Subset t1(n, false), t2(n, false);
    s.clear();
    Subset t; // BITSET
    REP(i, n)
        if (lhs[i])
            rdfs(i, s);
    REP(i, n)
        if (rhs[i])
            rdfs(i, t);
    //subset_and(s, t1, t2);
    s &= t;
    logic_max(s);
}

void logic_imply(Subset& s, Subset& lhs, Subset& rhs) {
    //Subset t(n, false);
    Subset t; // BITSET
    REP(i, n)
        if (lhs[i])
            rdfs(i, t);
    REP(i, n)
        s[i] = rhs[i] && !t[i];
}

void logic_equiv(Subset& s, Subset& lhs, Subset& rhs) {
    //Subset t1(n), t2(n);
    Subset t1, t2; // BITSET
    logic_imply(t1, lhs, rhs);
    logic_imply(t2, rhs, lhs);
    logic_and(s, t1, t2);
}

void logic_not(Subset& s, Subset& t) {
    logic_imply(s, t, logic_false);
}




// Expr definitions

class Expr {
protected:
    SubsetI memory;
    Expr() : memory(-1) {
        garbage.push_back(this);
    }

public:
    virtual ~Expr() {
    }

public:
    virtual SubsetI eval0() = 0;
    virtual void print() = 0;
    virtual bool isRefreshed() = 0;

    virtual SubsetI eval() {
        if (memory < 0 || isRefreshed()) {
            memory = eval0();
        }
        return memory;
    }
};

class UnaryFunction : public Expr {
protected:
    Expr* expr;
    UnaryFunction(Expr* expr) : expr(expr) {
    }

public:
    virtual bool isRefreshed() {
        return expr->isRefreshed();
    }
};

class BinaryFunction : public Expr {
protected:
    Expr* lhs;
    Expr* rhs;
    BinaryFunction(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {
    }

public:
    virtual bool isRefreshed() {
        return (lhs->isRefreshed() || rhs->isRefreshed());
    }
};

class ConstantExpr : public Expr {
protected:
    bool value;

public:
    ConstantExpr(bool value) : value(value) {
    }

    virtual SubsetI eval0() {
        return (value ? m-1 : 0);
    }
    virtual void print() {
        printf("%d", (value?1:0));
    }
    virtual bool isRefreshed() {
        return false;
    }
};

class LiteralExpr : public Expr {
protected:
    int id;
    int lastValue;

public:
    LiteralExpr(int id) : id(id) {
        lastValue = -1;
    }

    virtual SubsetI eval0() {
        return (lastValue = literals[id]);
    }
    virtual void print() {
        printf("%c", (char)('A' + id));
        subset_print(scope[literals[id]]);
    }
    virtual bool isRefreshed() {
        return (lastValue != literals[id]);
    }
};

class AndExpr : public BinaryFunction {
public:
    AndExpr(Expr* lhs, Expr* rhs) : BinaryFunction(lhs, rhs) {
    }

    virtual SubsetI eval0() {
        return logic_and_table[lhs->eval()][rhs->eval()];
    }
    virtual void print() {
        printf("(");
        lhs->print();
        printf("&");
        rhs->print();
        printf(")");
    }
};

class OrExpr : public BinaryFunction {
public:
    OrExpr(Expr* lhs, Expr* rhs) : BinaryFunction(lhs, rhs) {
    }

    virtual SubsetI eval0() {
        return logic_or_table[lhs->eval()][rhs->eval()];
    }
    virtual void print() {
        printf("(");
        lhs->print();
        printf("|");
        rhs->print();
        printf(")");
    }
};

class ImplyExpr : public BinaryFunction {
public:
    ImplyExpr(Expr* lhs, Expr* rhs) : BinaryFunction(lhs, rhs) {
    }

    virtual SubsetI eval0() {
        return logic_imply_table[lhs->eval()][rhs->eval()];
    }
    virtual void print() {
        printf("(");
        lhs->print();
        printf("=>");
        rhs->print();
        printf(")");
    }
};

class EquivExpr : public BinaryFunction {
public:
    EquivExpr(Expr* lhs, Expr* rhs) : BinaryFunction(lhs, rhs) {
    }

    virtual SubsetI eval0() {
        return logic_equiv_table[lhs->eval()][rhs->eval()];
    }
    virtual void print() {
        printf("(");
        lhs->print();
        printf("=");
        rhs->print();
        printf(")");
    }
};

class NotExpr : public UnaryFunction {
public:
    NotExpr(Expr* expr) : UnaryFunction(expr) {
    }

    virtual SubsetI eval0() {
        return logic_not_table[expr->eval()];
    }
    virtual void print() {
        printf("(~");
        expr->print();
        printf(")");
    }
};


void clearGarbage() {
    REP(i, garbage.size())
        delete garbage[i];
    garbage.clear();
}



Expr* parse6(char *(&p)) {
    Expr* e;
    if (*p == '(') {
        p++;
        Expr* parse0(char *(&));
        e = parse0(p);
        assert(*p == ')');
        p++;
    }
    else if (isalpha(*p)) {
        e = new LiteralExpr((int)((*p) - 'A'));
        p++;
    }
    else if (*p == '0' || *p == '1') {
        e = new ConstantExpr(*p == '1');
        p++;
    }
    else {
        assert(false);
    }
    return e;
}

Expr* parse5(char *(&p)) {
    Expr* e;
    if (*p == '~') {
        p++;
        e = new NotExpr(parse5(p));
    }
    else {
        e = parse6(p);
    }
    return e;
}

Expr* parse4(char *(&p)) {
    Expr* e = parse5(p);
    while(*p == '&') {
        p++;
        e = new AndExpr(e, parse5(p));
    }
    return e;
}

Expr* parse3(char *(&p)) {
    Expr* e = parse4(p);
    while(*p == '|') {
        p++;
        e = new OrExpr(e, parse4(p));
    }
    return e;
}

Expr* parse2(char *(&p)) {
    Expr* e = parse3(p);
    if (p[0] == '=' && p[1] == '>') {
        p+=2;
        e = new ImplyExpr(e, parse2(p));
    }
    return e;
}

Expr* parse1(char *(&p)) {
    Expr* e = parse2(p);
    if (*p == '=') {
        p++;
        Expr* last = parse2(p);
        e = new EquivExpr(e, last);
        while(*p == '=') {
            p++;
            Expr* next = parse2(p);
            e = new AndExpr(e, new EquivExpr(last, next));
            last = next;
        }
    }
    return e;
}

Expr* parse0(char *(&p)) {
    return parse1(p);
}

Expr* parse(const string& text) {
    int len = text.size();
    char* buf = new char[len+1];
    REP(i, len)
        buf[i] = text[i];
    buf[len] = '\0';

    char* p = buf;
    Expr* e = parse0(p);
    delete[] buf;

    return e;
}



void topological_sort(int here, Subset& visited) {
    if (visited[here])
        return;
    visited[here] = true;
    Edges& v = g[here];
    REP(i, v.size()) {
        int there = v[i];
        topological_sort(there, visited);
    }
    order.push_back(here);
}

bool exhaustive_search(int iLiteral, Expr* e) {
    if (iLiteral == 26) {
        return (e->eval() == m-1); // BITSET
    }

    if (used_literals[iLiteral]) {
        REP(i, m) {
            literals[iLiteral] = i;
            if (!exhaustive_search(iLiteral+1, e))
                return false;
        }
        return true;
    }
    else {
        return exhaustive_search(iLiteral+1, e);
    }
}

void search_scope(Subset& s, int iOrder, vector<int>& conflict) {
    if (iOrder == n) {
        scope.push_back(s);
        return;
    }

    int iNode = order[iOrder];
    if (conflict[iNode] == 0) {
        REP(i, n)
            if (lowers[iNode][i])
                conflict[i]++;
        s[iNode] = true;
        search_scope(s, iOrder+1, conflict);
        REP(i, n)
            if (lowers[iNode][i])
                conflict[i]--;
        s[iNode] = false;
    }

    search_scope(s, iOrder+1, conflict);
}

void graph_init() {
    REP(i, n)
        logic_true[i] = false;
    REP(i, n)
        logic_false[i] = true;
    logic_max(logic_false);

    order.clear();
    {
        //Subset visited(n, false);
        Subset visited; // BITSET
        REP(i, n)
            topological_sort(i, visited);
    }

    //lowers.assign(n, Subset(n, false));
    lowers.assign(n, Subset());
    {
        REP(i, n)
            rdfs(i, lowers[i]);
    }

    scope.clear();
    {
        //Subset s(n, false);
        Subset s; // BITSET
        vector<int> conflict(n, 0);
        search_scope(s, 0, conflict);
    }
    m = scope.size();

    map<Subset, int> subsets;
    REP(i, m)
        subsets[scope[i]] = i;

    REP(i, m) REP(j, m) {
        Subset s;
        logic_and(s, scope[i], scope[j]);
        logic_and_table[i][j] = subsets[s];
        logic_or(s, scope[i], scope[j]);
        logic_or_table[i][j] = subsets[s];
        logic_imply(s, scope[i], scope[j]);
        logic_imply_table[i][j] = subsets[s];
        logic_equiv(s, scope[i], scope[j]);
        logic_equiv_table[i][j] = subsets[s];
    }
    REP(i, m) {
        Subset s;
        logic_not(s, scope[i]);
        logic_not_table[i] = subsets[s];
    }

#ifdef DEBUG
    printf("Scope:\n");
    REP(i, m) {
        subset_print(scope[i]);
        printf("\n");
    }
    assert(scope.front() == logic_false);
    assert(scope.back() == logic_true);
#endif
}

bool solve(const string& f) {

    //used_literals.resize(26); // BITSET
    REP(i, 26)
        used_literals[i] = (count(ALLOF(f), (char)('A' + i)) > 0);

    int nLiterals = 0;
    REP(i, 26)
        if (used_literals[i])
            nLiterals++;

    literals.assign(26, 0);

    Expr* e = parse(f);

    //printf("Search cost: %d^%d = %.0f\n", m, nLiterals, pow((double)m, nLiterals));

    bool result = exhaustive_search(0, e);

    clearGarbage();

    return result;
}

bool isws(char c) {
    return isspace(c);
}

int main() {

    int nEdges;
    //cin >> n >> nEdges;
    if (scanf("%d%d", &n, &nEdges) == 0)
        return 1;

    g.assign(n, Edges());
    r.assign(n, Edges());

    REP(i, nEdges) {
        int a, b;
        //cin >> a >> b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g[a].push_back(b);
        r[b].push_back(a);
    }

    graph_init();

    int nCases;
    cin >> nCases;
    cin >> ws;

    REP(iCase, nCases) {

        string f;
        getline(cin, f);
        f.erase(remove_if(ALLOF(f), isws), f.end());

        cout << (solve(f) ? "valid" : "invalid") << endl;

    }

    return 0;
}


