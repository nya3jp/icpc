/*
 * UVA 10404 Bachet's Game
 * 2005-07-22
 * by nya
 */

#include <iostream>
#include <vector>


int main() {
    bool* v = new bool[1000000+1];
    int n, m;
    while(std::cin >> n >> m) {
        std::vector<int> s(m);
        for(int i=0; i<m; i++)
            std::cin >> s[i];
        for(int i=0; i<=n; i++) {
            v[i] = false;
        }
        for(int i=0; i<=n; i++) {
            if (! v[i]) {
                for(int j=0; j<m; j++) {
                    int k = i+s[j];
                    if (k <= n)
                        v[k] = true;
                }
            }
        }
        std::cout << (v[n] ? "Stan" : "Ollie") << " wins" << std::endl;
    }
    delete[] v;
    return 0;
}
