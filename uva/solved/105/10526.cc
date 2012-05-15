#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;


struct sa_comparator {
    const int h, *g;
    sa_comparator(int h, int* g) : h(h), g(g) {
    }
    inline bool operator()(int a, int b) {
        return (a == b ? false :
                g[a] != g[b] ? (g[a] < g[b]) : (g[a+h] < g[b+h]) );
    }
};

const char** make_sa(const char* str) {
    const int n = strlen(str);

    int *v, *g, *b;
    v = new int[n+1]; g = new int[n+1]; b = new int[n+1];
    for(int i = 0; i <= n; i++) {
        v[i] = i;
        g[i] = (int)str[i] & 0xff;
    }
    sort(v, v+n+1, sa_comparator(0, g));

    for(int h = 1; ; h *= 2) {
        sa_comparator comp(h, g);
        sort(v, v+n+1, comp);

        b[0] = 0;
        for(int i = 1; i <= n; i++)
            b[i] = b[i-1] + (comp(v[i-1], v[i]) ? 1 : 0);
        if (b[n] == n)
            break;
        for(int i = 0; i <= n; i++)
            g[v[i]] = b[i];
    }

    const char** sa = new const char*[n];
    for(int i = 0; i < n; i++)
        sa[i] = str + v[i+1];

    delete[] v; delete[] g; delete[] b;

    return sa;
}


int match(const char** sa, int n, const char* s) {
    int lower = 0, upper = n;
    int matchlen = 0;
    while(upper-lower > 0) {
        int middle = (lower+upper)/2;
        int order = strcmp(sa[middle], s);
        {
            int len = 0;
            while(sa[middle][len] != '\0' && s[len] != '\0' && sa[middle][len] == s[len])
                len++;
            matchlen = max(matchlen, len);
        }
        if (order < 0)
            lower = middle+1;
        else if (order > 0)
            upper = middle;
        else
            break;
    }
    return matchlen;
}


#define MAX_SIZE 50000

char ibm[MAX_SIZE+10];
char sco[MAX_SIZE+10];

int main() {

    string line;

    for(int iCase = 0; ; iCase++) {

        int k;
        getline(cin, line);
        sscanf(line.c_str(), "%d", &k);

        if (k == 0)
            return 0;

        getline(cin, line);
        assert(line == "BEGIN TDP CODEBASE");

        for(char* p = sco;;) {
            getline(cin, line);
            if (line == "END TDP CODEBASE") {
                *p = '\0';
                break;
            }
            int len = line.size();
            copy(line.begin(), line.end(), p);
            p += len;
            *p++ = '\n';
        }

        getline(cin, line);
        assert(line == "BEGIN JCN CODEBASE");

        for(char* p = ibm;;) {
            getline(cin, line);
            if (line == "END JCN CODEBASE") {
                *p = '\0';
                break;
            }
            int len = line.size();
            copy(line.begin(), line.end(), p);
            p += len;
            *p++ = '\n';
        }

        int n = strlen(ibm);
        int m = strlen(sco);
        const char** sa = make_sa(sco);

        vector<pair<int, int> > v;
        int right = 0;
        for(int i = 0; i < n; i++) {
            int len = match(sa, m, ibm+i);
            if (len > 0 && i+len > right) {
                v.push_back(make_pair(-len, i));
                right = i+len;
            }
        }
        sort(v.begin(), v.end());

        if ((int)v.size() > k)
            v.resize(k);

        if (iCase > 0)
            cout << endl;

        cout << "CASE " << (iCase+1) << endl;

        for(int i = 0; i < (int)v.size(); i++) {
            int len = -v[i].first;
            int pos = v[i].second;
            cout << "INFRINGING SEGMENT " << (i+1) << " LENGTH " << len << " POSITION " << pos << endl;
            cout << string(ibm+pos, ibm+pos+len) << endl;
        }

    }

    return 0;
}
