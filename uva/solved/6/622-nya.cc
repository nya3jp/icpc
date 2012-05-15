/*
 * UVA 622 Grammer Evaluation
 * 2004-12-30
 * by nya
 */

#include <iostream>
#include <sstream>
#include <ctype.h>

using namespace std;

const size_t BUF_SIZE = 1024;

typedef unsigned int bignum;

struct IllegalExpressionException {
};



bignum parse_factor(const char*& p);
bignum parse_component(const char*& p);
bignum parse_expression(const char*& p);



bignum parse_factor(const char*& p)
{
    bignum n;
    if (isdigit(*p)) {
        n = 0;
        do {
            n = n*10 + (*p - '0');
            p++;
        } while(isdigit(*p));
    }
    else if (*p == '(') {
        p++;
        n = parse_expression(p);
        if (*p != ')') {
            throw IllegalExpressionException();
        }
        p++;
    }
    else {
        throw IllegalExpressionException();
    }
    return n;
}



bignum parse_component(const char*& p)
{
    bignum n;
    n = parse_factor(p);
    while(*p == '*') {
        p++;
        n *= parse_factor(p);
    }
    return n;
}


bignum parse_expression(const char*& p)
{
    bignum n;
    n = parse_component(p);
    while(*p == '+') {
        p++;
        n += parse_component(p);
    }
    return n;
}

bignum parse(const char* buf)
{
    const char* p;
    bignum n;

    p = buf;
    n = parse_expression(p);
    if (*p != '\0' && *p != '\r')
        throw IllegalExpressionException();
    return n;
}


int main(int argc, char** argv)
{
    char *buf;

    buf = new char[BUF_SIZE];

    cin.getline(buf, BUF_SIZE);
    int nCases;
    istringstream(buf) >> nCases;

    for(int iCase=0; iCase<nCases; iCase++) {

        cin.getline(buf, BUF_SIZE);

        try {
            bignum ans = parse(buf);
            cout << ans << endl;
        }
        catch(IllegalExpressionException e) {
            cout << "ERROR" << endl;
        }
    }

    delete[] buf;

    return 0;
}
