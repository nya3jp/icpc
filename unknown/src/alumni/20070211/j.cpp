#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <complex>
#include <queue>
#include <deque>
#include <fstream>

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(v)    (v).begin(), (v).end()

using namespace std;


ifstream fin("java_c.in");

#define cin fin


enum Type {
    CPlusPlus = 0,
    Java,
    Invalid
};

string java2cplusplus(string str)
{
    string ret;
    REP(i, str.size()) {
        if (isupper(str[i])) {
            ret += string("_");
            ret += tolower(str[i]);
        } else {
            ret += str[i];
        }
    }
    return ret;
}

string cplusplus2java(string str)
{
    string ret;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '_') {
            i++;
            ret += toupper(str[i]);
        } else {
            ret += str[i];
        }
    }
    return ret;
}

enum Type judge(string str)
{
    if (isupper(str[0]))
        return Invalid;
    if (str[0] == '_')
        return Invalid;

    bool isJava = true;
    REP(i, str.size()) {
        char c = str[i];
        if (c == '_') {
            if (i < str.size() -1) {
                if (isupper(str[i + 1]))
                    return Invalid;
                else if (str[i + 1] == '_')
                    return Invalid;
                else
                    isJava = false;
            } else {
                return Invalid;
            }
        }
    }

    if (!isJava) {
        REP(i, str.size()) {
            if (str[i] != '_' && isupper(str[i]))
                return Invalid;
        }
    }

    return isJava ? Java : CPlusPlus;
}

int
main(void)
{
    int nCases;
    cin >> nCases;
    while (nCases--) {
        string str;
        cin >> str;

//        cout << ": " << str << endl;
        /*
        cout << judge(str) << endl;
        */

        switch (judge(str)) {
        case CPlusPlus:
            cout << cplusplus2java(str) << endl;
            break;

        case Java:
            cout << java2cplusplus(str) << endl;
            break;

        case Invalid:
            cout << "Error!" << endl;
            break;
        }
    }
}
