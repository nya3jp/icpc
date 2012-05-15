#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

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

void make_suffix_array(const char* str, vector<const char*>& sa) {
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

    sa.resize(n);
    for(int i = 0; i < n; i++)
        sa[i] = str + v[i+1];

    delete[] v; delete[] g; delete[] b;
}




inline bool strless(const char* a, const char* b) {
    return (strcmp(a, b) < 0);
}

int main() {
    ifstream fin("english.in");
    string line;

    int iCase = 0;
    while(getline(fin, line) && line == "%%%%%") {
        ostringstream os;
        while(getline(fin, line) && line != "%%%%%")
            os << line << ' ';
        string body_str = os.str();
        const char* body = body_str.c_str();

        vector<const char*> sa;
        make_suffix_array(body, sa);

        if (iCase > 0)
            cout << endl;
        cout << "Case " << ++iCase << ":" << endl;

        while(getline(fin, line) && line != "%%%%%") {
            string query = line;
            string query_next = line;
            query_next[query_next.size()-1]++;
            int hits = lower_bound(sa.begin(), sa.end(), query_next.c_str(), strless)
                     - lower_bound(sa.begin(), sa.end(), query.c_str(), strless);
            cout << hits << endl;
        }
        getline(fin, line);
    }


    return 0;
}













