#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

const int INF = 10000000;

typedef const char *sptr;

long long int parseint(sptr& p) {
    long long int t = 0;
    while(isdigit(*p)) {
        t = t*10 + (int)(*p - '0');
        if (t > INF)
            t = INF;
        p++;
    }
    return t;
}

long long int length(sptr& p) {
    long long int len = 0;
    while(true) {
        if (isdigit(*p)) {
            long long int mul = parseint(p);
            if (*p == '(') {
                p++;
                len += mul * length(p);
                assert(*p == ')');
                p++;
            }
            else {
                assert(isalpha(*p));
                len += mul;
                p++;
            }
        }
        else if (*p == '\0' || *p == ')') {
            break;
        }
        else {
            //if (!isalpha(*p)) {
            //cout << p << endl;
            assert(isalpha(*p));
            //}
            p++;
            len++;
        }
        if (len > INF)
            len = INF;
    }
    return len;
}

char query(sptr& p, long long int index) {
    //cout << "query(" << index << ") " << p << endl;
    if (isdigit(*p)) {
        long long int mul = parseint(p);
        if (*p == '(') {
            //cout << "kakko" << endl;
            p++;
            sptr q = p;
            long long int locallen = length(q);
            //cout << "length=" << locallen << endl;
            //cout << "p=" << p << endl;
            //cout << "q=" << q << endl;
            if (index < locallen*mul) {
                return query(p, index%locallen);
            }
            assert(*q == ')');
            q++;
            return query(q, index-locallen*mul);
        }
        else {
            assert(isalpha(*p));
            if (index < mul)
                return *p;
            p++;
            return query(p, index-mul);
        }
    }
    else if (*p == '\0' || *p == ')') {
        return '0';
    }
    else {
        assert(isalpha(*p));
        if (index == 0)
            return *p;
        p++;
        return query(p, index-1);
    }
    assert(false);
}


int main() {

    string s;
    int index;
    while(cin >> s >> index && !(s == "0" && index == 0)) {

        sptr p = s.c_str();
        cout << query(p, index) << endl;

    }

    return 0;
}

