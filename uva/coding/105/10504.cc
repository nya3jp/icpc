#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_SIZE 100

char field[MAX_SIZE][MAX_SIZE];

inline bool in_range(int a, int l, int h) {
    return (l <= a && a < h);
}

int main() {

    for(;;) {

        int n, q;
        cin >> n >> q;
        if (n == 0)
            break;

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                cin >> field[i][j];

        while(q-- > 0) {
            char c;
            cin >> c;
            int count = 0;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if (field[i][j] == c) {
                        for(int di = 0; i+di < n; di++) {
                            for(int dj = 1; j+dj < n; dj++) {
                                int i1 = i+dj, j1 = j-di;
                                int i2 = i+di+dj, j2 = j+dj-di;
                                if (!in_range(i1, 0, n))
                                    goto DJ_BREAK;
                                if (!in_range(j1, 0, n))
                                    goto DI_BREAK;
                                if (!in_range(i2, 0, n))
                                    goto DJ_BREAK;
                                if (!in_range(j2, 0, n))
                                    goto NO_COMPARE;
                                if (field[i+di][j+dj] == c &&
                                    field[i1][j1] == c && field[i2][j2] == c)
                                    count++;
                            NO_COMPARE:;
                            }
                        DJ_BREAK:;
                        }
                    DI_BREAK:;
                    }
                }
            }
            cout << c << ' ' << count << endl;
        }
        cout << endl;

    }
    return 0;
}
