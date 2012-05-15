#include <iostream>
#include <cstdio>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

struct Term {
    long long int n;
    enum Type {
        Mul, Add, Fin, Nul
    } type;
};


int parse_expr(const string& expr, Term* terms) {
    int nTerms = 0;
    int len = expr.size();
    for(int pos = 0; pos < len; ) {
        Term& t = terms[nTerms];
        t.n = 0;
        while(isdigit(expr[pos])) {
            t.n = t.n * 10 + (expr[pos] - '0');
            pos++;
        }
        if (pos == len) {
            t.type = Term::Fin;
        }
        else {
            if (expr[pos] == '+') {
                t.type = Term::Add;
            }
            if (expr[pos] == '*') {
                t.type = Term::Mul;
            }
            pos++;
        }
        nTerms++;
    }
    return nTerms;
}



void search(Term* terms, const int nTerms, long long int& val_min, long long int& val_max) {
    /*
    for(int i = 0; i < nTerms; i++) {
        printf("%lld(%d) - ", terms[i].n, terms[i].type);
    }
    printf("\n");
    */
    bool single = true;
    int prev = -1;
    for(int i = 0; i < nTerms; i++) {
        if (terms[i].type != Term::Nul) {
            if (prev != -1) {
                Term a = terms[prev];
                Term b = terms[i];
                if (a.type == Term::Add)
                    terms[prev].n += b.n;
                if (a.type == Term::Mul)
                    terms[prev].n *= b.n;
                terms[prev].type = b.type;
                terms[i].type = Term::Nul;
                search(terms, nTerms, val_min, val_max);
                terms[prev] = a;
                terms[i] = b;
                single = false;
            }
            prev = i;
        }
    }
    if (single) {
        assert(terms[prev].type == Term::Fin);
        val_min = min(val_min, terms[prev].n);
        val_max = max(val_max, terms[prev].n);
    }
}


int main() {
    int nCases;
    cin >> nCases;
    for(int iCase = 0; iCase < nCases; iCase++) {

        string expr;
        cin >> expr;

        Term terms[15];
        int nTerms = parse_expr(expr, terms);

        long long int val_min = 0x7fffffffffffffffll, val_max = 0;
        search(terms, nTerms, val_min, val_max);

        cout << "The maximum and minimum are "
             << val_max
             << " and "
             << val_min
             << "." << endl;
    }
    return 0;
}
