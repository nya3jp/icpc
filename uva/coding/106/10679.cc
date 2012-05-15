/**
 * @file
 * 文字列:Suffix Array
 *
 * @version
 * rev. 02
 *
 * @note
 * Larsson Sadakane法を使用。
 * 計算量はO(N(logN)^2)。
 */


#include <algorithm>
#include <vector>
#include <numeric>
#include <cstring>

using namespace std;


void radix_sort_block(int* v, int* u, int n, int h, int* g) {
    // dangerous... dependent on 
    int r_[1025];
    int* r = r_+1;
    for(int s = 0; s < 3; s++) {
        fill(r-1, r+1024, 0);
        for(int i = 0; i < n; i++)
            r[(g[v[i]+h]>>(10*s))%1024]++;
        partial_sum(r-1, r+1024, r-1);
        for(int i = n-1; i >= 0; i--)
            u[--r[(g[v[i]+h]>>(10*s))%1024]] = v[i];
        swap(v, u);
    }
}

void radix_sort(int* v, int* u, int n, int h, int* g) {
    int i, j;
    for(i = 0; i < n; i = j) {
        int g0 = g[v[i]];
        for(j = i+1; j < n; j++) {
            if (v[g[j]] != g0)
                break;
        }
        radix_sort_block(v+i, u+i, j-i, h, g);
    }
}

void make_suffix_array(const char* str, vector<const char*>& sa) {
    const int n = strlen(str);

    assert(n > 0);

    int *v, *u, *g, *b;
    v = new int[n]; u = new int[n]; g = new int[n*2]; b = new int[n];
    for(int i = 0; i < n; i++) {
        v[i] = i;
        g[i] = (int)str[i] & 0xff;
    }
    fill(g+n, g+n*2, -1);
    radix_sort_block(v, u, n, 0, g);
    swap(v, u);

    for(int h = 1; ; h *= 2) {
        radix_sort(v, u, n, h, g);
        swap(v, u);

        b[0] = 0;
        for(int i = 1; i < n; i++)
            b[i] = b[i-1] + ((g[v[i-1]] != g[v[i]] || g[v[i-1]+h] != g[v[i]+h]) ? 1 : 0);
        if (b[n-1] == n-1)
            break;
        for(int i = 0; i < n; i++)
            g[v[i]] = b[i];
    }

    sa.resize(n);
    for(int i = 0; i < n; i++)
        sa[i] = str + v[i];

    delete[] v; delete[] u; delete[] g; delete[] b;
}

#include <stdio.h>


int main() {
    char* buf = new char[100010];
    char* query = new char[1010];
    int nCases;
    fgets(buf, 100010, stdin);
    sscanf(buf, "%d", &nCases);
    for(int iCase = 0; iCase < nCases; iCase++) {
        fgets(buf, 100010, stdin);
        vector<const char*> sa;
        make_suffix_array(buf, sa);
        fgets(query, 1010, stdin);
        int nQueries;
        sscanf(query, "%d", &nQueries);
        for(int iQuery = 0; iQuery < nQueries; iQuery++) {
            fgets(query, 1010, stdin);
        }
    }
    return 0;
}
