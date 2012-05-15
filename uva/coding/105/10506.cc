#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n, m;
int nm;
bool table[65536];
int seq[65536];

bool search(int last, int k) {
    if (k == nm) {
        int next = last;
        for(int i = 0; i < n-1; i++) {
            next = next*m%nm;
            if (table[next])
                return false;
        }
        return true;
    }
    for(int i = 0; i < m; i++) {
        int next = last*m%nm+i;
        if (!table[next]) {
            table[next] = true;
            if (search(next, k+1)) {
                seq[k] = i;
                return true;
            }
            table[next] = false;
        }
    }
    return false;
}

int main() {
    while(cin >> n >> m) {
        nm = 1;
        for(int i = 0; i < n; i++)
            nm *= m;
        fill(table, table+nm, false);
        table[0] = true;
        fill(seq, seq+nm, 0);
        search(0, n);
        for(int i = 0; i < nm; i++)
            printf("%d", seq[i]);
        printf("\n");
    }
    return 0;
}
