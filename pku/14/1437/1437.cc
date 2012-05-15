#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
#include <cstring>
using namespace std;
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

inline bool is_cons(char c) {
    switch(c) {
    case 'a':
    case 'i':
    case 'u':
    case 'e':
    case 'o':
    case 'y':
    case 'A':
    case 'I':
    case 'U':
    case 'E':
    case 'O':
    case 'Y':
        return false;
    }
    return isalpha(c);
}

int count_cons(string message) {
    int max_cons = 0;
    int current_cons = 0;
    REP(i, message.size()) {
        if (is_cons(message[i])) {
            current_cons++;
            max_cons >?= current_cons;
        }
        else {
            current_cons = 0;
        }
    }
    return max_cons;
}

int main() {

    string message;

    int nCases;
    getline(cin, message);
    sscanf(message.c_str(), "%d", &nCases);

    deque<string> history;

    REP(iCase, nCases) {

        getline(cin, message);

        bool rejected = false;

        int max_cons = count_cons(message);
        if (max_cons > 5)
            rejected = true;

        if (max_cons > 4) {
            int r = 0;
            REP(i, history.size())
                if (count_cons(history[i]) >= 4)
                    r++;
            if (r > 2)
                rejected = true;
        }

        {
            int r = 0;
            REP(i, history.size())
                if (history[i] == message)
                    r++;
            if (r > 1)
                rejected = true;
        }

        cout << (rejected?'n':'y') << endl;

        history.push_back(message);
        while(history.size() > 10)
            history.pop_front();

    }

    return 0;
}
