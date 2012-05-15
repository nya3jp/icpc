#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

typedef const char* sptr;


string parse1(sptr& p);

string parse6(sptr& p) {
    if (*p == '(') {
        string rpn = parse1(++p);
        p++;
        return rpn;
    }
    sptr q = p;
    while(isalpha(*p))
        p++;
    return string(q, p);
}
string parse5(sptr& p) {
    string rpn = parse6(p);
    while(*p == '^') {
        p++;
        rpn = rpn + parse6(p) + "^";
    }
    return rpn;
}
string parse4(sptr& p) {
    string rpn = parse5(p);
    while(*p == '/') {
        p++;
        rpn = rpn + parse5(p) + "/";
    }
    return rpn;
}
string parse3(sptr& p) {
    string rpn = parse4(p);
    while(*p == '*') {
        p++;
        rpn = rpn + parse4(p) + "*";
    }
    return rpn;
}
string parse2(sptr& p) {
    string rpn = parse3(p);
    while(*p == '-') {
        p++;
        rpn = rpn + parse3(p) + "-";
    }
    return rpn;
}
string parse1(sptr& p) {
    string rpn = parse2(p);
    while(*p == '+') {
        p++;
        rpn = rpn + parse2(p) + "+";
    }
    return rpn;
}




int main() {
    string line;
    getline(cin, line);
    int n;
    sscanf(line.c_str(), "%d", &n);
    while(n-- > 0) {
        getline(cin, line);
        const char* p = line.c_str();
        cout << parse1(p) << endl;
    }
    return 0;
}
