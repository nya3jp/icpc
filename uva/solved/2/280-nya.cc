/*
 * UVA 280 Vertex
 * 2004-11-07
 * by nya
 */

#include <iostream>

using namespace std;

bool matrix[100][100];
bool visited[100];
int n;
int c;

void dive(int pos)
{
    for(int i=0; i<n; i++) {
        if ((! visited[i]) && matrix[pos][i]) {
            visited[i] = true;
            c--;
            dive(i);
        }
    }
}

int main()
{
    while(cin >> n, n > 0) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                matrix[i][j] = false;
            }
        }
        int k;
        while(cin >> k, k > 0) {
            int t;
            while(cin >> t, t > 0) {
                matrix[(k-1)][(t-1)] = true;
            }
        }
        int m;
        cin >> m;
        while(m-- > 0) {
            int t;
            cin >> t;
            for(int i=0; i<n; i++) {
                visited[i] = false;
            }
            c = n;
            dive(t-1);
            cout << c;
            for(int i=0; i<n; i++) {
                if (! visited[i])
                    cout << ' ' << (i+1);
            }
            cout << endl;
        }
    }

    return 0;
}
