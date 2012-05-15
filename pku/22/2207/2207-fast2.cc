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

#define REP(i,n) if(0);else for(int i = 0; i <(int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

// type definitions

#define N 100

//typedef vector<bool> Subset;
template<class T>
struct vectorN {
    T v[N];
    int n;

    vectorN() {
        clear();
    }
    vectorN(int m, const T& value = false) {
        n = m;
        assign(m, value);
    }
    inline void clear() {
        n = 0;
    }
    inline void resize(int m) {
        n = m;
    }
    inline void assign(int m, const T& value) {
        n = m;
        REP(i, n)
            v[i] = value;
    }
    inline void push_back(const T& value) {
        v[n++] = value;
    }
    inline T* begin() {
        return v;
    }
    inline T* end() {
        return v+n;
    }
    inline const T* begin() const {
        return v;
    }
    inline const T* end() const {
        return v+n;
    }
    inline int size() const {
        return n;
    }
    inline T& operator[](int i) {
        return v[i];
    }
    inline const T& operator[](int i) const {
        return v[i];
    }
};
template<class T>
bool operator<(const vectorN<T>& lhs, const vectorN<T>& rhs) {
    return lexicographical_compare(lhs.v, lhs.v+lhs.n, rhs.v, rhs.v+rhs.n);
}
template<class T>
bool operator==(const vectorN<T>& lhs, const vectorN<T>& rhs) {
    return equal(lhs.v, lhs.v+N, rhs.v);
}

typedef int SubsetI;
typedef vector<int> Edges;
typedef vector<Edges> Graph;
typedef vectorN<bool> Subset;


Graph g, r;
int n, m; // number of nodes, size of scope
vector<int> order; // topological order of g
vector<Subset> scope;
vector<Subset> lowers;
vector<int> literals;
vector<class Expr*> garbage;
Subset used_literals;
Subset logic_false, logic_true;
SubsetI logic_falseI, logic_trueI;

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
    REP(i, s.n)
        printf("%d", (s[i] ? 1 : 0));
    printf("]");
}


// Logical functions

void logic_max(Subset& s) {
    Subset t(n, false);
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
    s = lhs;
    REP(i, n)
        s[i] = s[i] || rhs[i];
    logic_max(s);
}

void logic_or(Subset& s, Subset& lhs, Subset& rhs) {
    Subset t(n, false);
    s.assign(n, false);
    REP(i, n)
        if (lhs[i])
            rdfs(i, s);
    REP(i, n)
        if (rhs[i])
            rdfs(i, t);
    REP(i, n)
        s[i] = s[i] && t[i];
    logic_max(s);
}

void logic_imply(Subset& s, Subset& lhs, Subset& rhs) {
    Subset t(n, false);
    REP(i, n)
        if (lhs[i])
            rdfs(i, t);
    REP(i, n)
        s[i] = rhs[i] && !t[i];
}

void logic_equiv(Subset& s, Subset& lhs, Subset& rhs) {
    Subset t1(n), t2(n);
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
    int lastVer;
    Expr() : memory(-1), lastVer(-1) {
        garbage.push_back(this);
    }

public:
    virtual ~Expr() {
    }

public:
    virtual SubsetI eval0() = 0;
    virtual void print() = 0;
    virtual int getVersion() = 0;

    virtual SubsetI eval() {
        int ver = getVersion();
        if (ver != lastVer) {
            memory = eval0();
            lastVer = ver;
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
    virtual int getVersion() {
        return expr->getVersion();
    }
};

class BinaryFunction : public Expr {
protected:
    Expr* lhs;
    Expr* rhs;
    BinaryFunction(Expr* lhs, Expr* rhs) : lhs(lhs), rhs(rhs) {
    }

public:
    virtual int getVersion() {
        return (lhs->getVersion() + rhs->getVersion());
    }
};

class ConstantExpr : public Expr {
protected:
    bool value;

public:
    ConstantExpr(bool value) : value(value) {
    }

    virtual SubsetI eval0() {
        return (value ? logic_trueI : logic_falseI);
    }
    virtual void print() {
        printf("%d", (value?1:0));
    }
    virtual int getVersion() {
        return 0;
    }
};

class LiteralExpr : public Expr {
protected:
    int id;
    int lastValue;
    int ver;

public:
    LiteralExpr(int id) : id(id), ver(0) {
        lastValue = -1;
    }

    virtual SubsetI eval0() {
        return literals[id];
    }
    virtual void print() {
        printf("%c", (char)('A' + id));
        subset_print(scope[literals[id]]);
    }
    virtual int getVersion() {
        if (literals[id] != lastValue) {
            lastValue = literals[id];
            ver++;
        }
        return ver;
    }
};

class AndExpr : public BinaryFunction {
public:
    AndExpr(Expr* lhs, Expr* rhs) : BinaryFunction(lhs, rhs) {
    }

    virtual SubsetI eval0() {
        int left = lhs->eval();
        if (false && left == logic_falseI)
            return logic_falseI;
        int right = rhs->eval();
        return logic_and_table[left][right];
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
        int left = lhs->eval();
        if (false && left == logic_trueI)
            return logic_trueI;
        int right = rhs->eval();
        return logic_or_table[left][right];
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
        int right = rhs->eval();
        if (false && right == logic_trueI)
            return logic_trueI;
        int left = lhs->eval();
        return logic_imply_table[left][right];
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
        return (e->eval() == logic_trueI);
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

bool random_search(Expr* e) {
    int nLiterals = 0;
    REP(i, 26)
        if (used_literals[i])
            nLiterals++;

    {
        REP(i, 26)
            if (used_literals[i])
                literals[i] = logic_trueI;
        SubsetI s = e->eval();
        if (s != logic_trueI)
            return false;
    }
    {
        REP(i, 26)
            if (used_literals[i])
                literals[i] = logic_falseI;
        SubsetI s = e->eval();
        if (s != logic_trueI)
            return false;
    }

    REP(p, 100) {
        int t = rand() & ((1<<nLiterals)-1);
        REP(i, 26) {
            if (used_literals[i]) {
                literals[i] = ((t&1) != 0 ? logic_trueI : logic_falseI);
                t >>= 1;
            }
        }
        SubsetI s = e->eval();
        if (s != logic_trueI)
            return false;
    }

    REP(iCase, 100) {
        REP(i, 26)
            if (used_literals[i])
                literals[i] = (rand() / 7) % m;
        SubsetI s = e->eval();
        if (s != logic_trueI)
            return false;
    }
    return true;
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
    logic_true.assign(n, false);
    logic_false.assign(n, true);
    logic_max(logic_false);

    order.clear();
    {
        Subset visited(n, false);
        REP(i, n)
            topological_sort(i, visited);
    }

    lowers.assign(n, Subset(n, false));
    REP(i, n)
        rdfs(i, lowers[i]);

    scope.clear();
    {
        Subset s(n, false);
        vector<int> conflict(n, 0);
        search_scope(s, 0, conflict);
    }
    m = scope.size();

    /*
    printf("Scope:\n");
    REP(i, m) {
        subset_print(scope[i]);
        printf("\n");
    }
    */

    /*
    map<Subset, int> subsets;
    REP(i, m)
        subsets[scope[i]] = i;
    /*/
    vector<pair<Subset, int> > subsets;
    REP(i, m)
        subsets.push_back(make_pair(scope[i], i));
    sort(ALLOF(subsets));
    //*/

    /*
    logic_falseI = subsets[logic_false];
    logic_trueI = subsets[logic_true];
    /*/
    logic_falseI = lower_bound(ALLOF(subsets), make_pair(logic_false, -1))->second;
    logic_trueI = lower_bound(ALLOF(subsets), make_pair(logic_true, -1))->second;
    //*/

    REP(i, m) REP(j, m) {
        if (i <= j) {
            Subset s(n);
            logic_and(s, scope[i], scope[j]);
            //logic_and_table[i][j] = subsets[s];
            assert(lower_bound(ALLOF(subsets), make_pair(s, -1))->first == s);
            logic_and_table[i][j] = lower_bound(ALLOF(subsets), make_pair(s, -1))->second;
            logic_and_table[j][i] = logic_and_table[i][j];
            logic_or(s, scope[i], scope[j]);
            //logic_or_table[i][j] = subsets[s];
            assert(lower_bound(ALLOF(subsets), make_pair(s, -1))->first == s);
            logic_or_table[i][j] = lower_bound(ALLOF(subsets), make_pair(s, -1))->second;
            logic_or_table[j][i] = logic_or_table[i][j];
        }
    }
    REP(i, m) REP(j, m) {
        Subset s(n);
        logic_imply(s, scope[i], scope[j]);
        //logic_imply_table[i][j] = subsets[s];
        assert(lower_bound(ALLOF(subsets), make_pair(s, -1))->first == s);
        logic_imply_table[i][j] = lower_bound(ALLOF(subsets), make_pair(s, -1))->second;
    }
    REP(i, m) REP(j, m) {
        logic_equiv_table[i][j] = logic_and_table[logic_imply_table[i][j]][logic_imply_table[j][i]];
        //Subset s(n);
        //logic_equiv(s, scope[i], scope[j]);
        //logic_equiv_table[i][j] = subsets[s];
    }
    REP(i, m) {
        Subset s(n);
        logic_not(s, scope[i]);
        //logic_not_table[i] = subsets[s];
        assert(lower_bound(ALLOF(subsets), make_pair(s, -1))->first == s);
        logic_not_table[i] = lower_bound(ALLOF(subsets), make_pair(s, -1))->second;
    }

    assert((int)subsets.size() == m);
}

bool solve(const string& f) {

    used_literals.resize(26);
    REP(i, 26)
        used_literals[i] = (count(ALLOF(f), (char)('A' + i)) > 0);

    literals.assign(26, 0);

    Expr* e = parse(f);

    //bool result = exhaustive_search(0, e);
    bool result = random_search(e);

    clearGarbage();

    return result;
}

bool isws(char c) {
    return isspace(c);
}

int main() {

    srand(283);

    int nEdges;
    //cin >> n >> nEdges;
    scanf("%d%d", &n, &nEdges);

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


