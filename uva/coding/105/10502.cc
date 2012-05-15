#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_SIZE 100

int table[MAX_SIZE][MAX_SIZE][MAX_SIZE]; // row->left->(width-1)

int main() {
    int h, w;
    while(cin >> h >> w && h > 0) {
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                char c;
                cin >> c;
                table[i][j][0] = (c == '1' ? 1 : 0);
            }
        }
        for(int i = 0; i < h; i++)
            for(int j = w-1; j >= 0; j--)
                for(int d = 1; j+d < w; d++)
                    table[i][j][d] = (table[i][j][0] == 1 ?
                                      table[i][j+1][d-1] : 0);
        long long int count = 0;
        for(int j = 0; j < w; j++) {
            for(int d = 0; j+d < w; d++) {
                //printf("(%d-%d) : ", j, j+d);
                int local = 0;
                for(int i = 0; i < h; i++) {
                    if (table[i][j][d] == 0) {
                        //printf("%d ", local);
                        count += local*(local+1)/2;
                        local = 0;
                    }
                    else {
                        local++;
                    }
                }
                count += local*(local+1)/2;
                //printf("%d\n", local);
            }
        }
        cout << count << endl;
    }
    return 0;
}

