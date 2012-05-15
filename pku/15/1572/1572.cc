#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <utility>

using namespace std;

int main() {
    string line;
    while(true) {
        getline(cin, line);
        int n;
        sscanf(line.c_str(), "%d", &n);
        if (n == 0)
            break;

        vector<pair<string, string> > v(n);
        for(int i = 0; i < n; i++) {
            string a, b;
            getline(cin, a);
            getline(cin, b);
            v[i] = make_pair(a, b);
        }
        string s;
        getline(cin, s);

        for(int iRule = 0; iRule < n; iRule++) {
            pair<string,string> rule = v[iRule];
            int len = rule.first.size();
            while(true) {
                string::size_type pos = s.find(rule.first);
                if (pos == string::npos)
                    break;
                s = s.substr(0, pos) + rule.second + s.substr(pos+len);
            }
        }
        cout << s << endl;
    }
    return 0;
}
