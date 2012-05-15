#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdio>

using namespace std;

int main() {
    int iCase = 0;
    int n, m;
    while(cin >> n >> m && !(n == 0 && m == 0)) {
        vector<string> v(n+2, string(m+2, '*'));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                cin >> v[i][j];
            }
        }

        if (iCase > 0)
            cout << endl;
        iCase++;
        cout << "puzzle #" << iCase << ":" << endl;

        // across
        cout << "Across" << endl;
        {
            int id = 0;
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= m; j++) {
                    if (v[i][j] != '*' && (v[i][j-1] == '*' || v[i-1][j] == '*')) {
                        id++;
                        if (v[i][j-1] == '*') {
                            //cout << "  " << id << ".";
                            printf("%3d.", id);
                            for(int k = j; v[i][k] != '*'; k++) {
                                cout << v[i][k];
                            }
                            cout << endl;
                        }
                    }
                }
            }
        }

        // down
        cout << "Down" << endl;
        {
            int id = 0;
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= m; j++) {
                    if (v[i][j] != '*' && (v[i][j-1] == '*' || v[i-1][j] == '*')) {
                        id++;
                        if (v[i-1][j] == '*') {
                            //cout << "  " << id << ".";
                            printf("%3d.", id);
                            for(int k = i; v[k][j] != '*'; k++) {
                                cout << v[k][j];
                            }
                            cout << endl;
                        }
                    }
                }
            }
        }

    }
    return 0;
}

