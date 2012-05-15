#include <algorithm>
#include <cstring>

using namespace std;

struct sa_comparator {
    const int h;
    const int* g;
    sa_comparator(int h, const int* g) : h(h), g(g) {
    }
    inline bool operator()(int a, int b) {
        if (g[a] != g[b])
            return (g[a] < g[b]);
        return (g[a+h] < g[b+h]);
    }
};

void make_suffix_array(const char* str, const char** sa) {
    const int n = strlen(str);

    int v[n+1], g[n+1], ng[n+1]; // gcc extension
    for(int i = 0; i <= n; i++)
        g[i] = str[v[i] = i];

    for(int h = 0; h < n; h ? h *= 2 : h++) {
        sa_comparator comp(h, g);
        sort(v, v+n+1, comp);

        ng[0] = 0;
        for(int i = 1; i <= n; i++)
            ng[i] = ng[i-1] + (comp(v[i-1], v[i]) ? 1 : 0);
        for(int i = 0; i <= n; i++)
            g[v[i]] = ng[i];
    }

    for(int i = 0; i < n; i++)
        sa[i] = str + v[i+1];
}



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>


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
        const int n = body_str.size();

        const char* sa[n];
        make_suffix_array(body, sa);

        if (iCase > 0)
            cout << endl;
        cout << "Case " << ++iCase << ":" << endl;

        while(getline(fin, line) && line != "%%%%%") {
            string query = line;
            string query_next = line;
            query_next[query_next.size()-1]++;
            int hits = lower_bound(sa, sa+n, query_next.c_str(), strless)
                     - lower_bound(sa, sa+n, query.c_str(), strless);
            cout << hits << endl;
        }
        getline(fin, line);
    }


    return 0;
}
