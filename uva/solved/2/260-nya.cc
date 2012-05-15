/*
 * UVA 260 Il Gioco dell'X
 * 2005-07-03
 * by nya
 */

#include <iostream>
#include <vector>
#include <algorithm>

#define N 200

int main() {

    int iCase = 0;
    int n;
    while(std::cin >> n && n != 0) {

        std::vector<bool> con(n, true);
        std::vector<int> v(n);

        for(int r=0; r<n; r++) {

            for(int i=0; i<n; i++) {
                char c;
                std::cin >> c;
                v[i] = (c == 'b' ? 1 : 0);
            }

            for(int i=0; i<n; i++) {
                if (v[i] == 1 && (con[i] || (i > 0 && con[i-1])) ) {
                    for(int j=i; j < n && v[j] == 1; j++) {
                        v[j] = 2;
                    }
                    for(int j=i-1; j >=0 && v[j] == 1; j--) {
                        v[j] = 2;
                    }
                }
            }

            for(int i=0; i<n; i++) {
                con[i] = (v[i] == 2);
            }

        }

        std::cout << (++iCase) << ' '
                  << (std::count(con.begin(), con.end(), true) > 0 ? 'B' : 'W')
                  << std::endl;

    }

    return 0;
}
