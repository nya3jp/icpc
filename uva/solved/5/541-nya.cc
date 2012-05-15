/*
 * UVA 541 Error Correction
 * 2004-11-07
 * by nya
 */

#include <iostream>
#include <algorithm>

using namespace std;

int matrix[100][100];

int main()
{
    int n;
    while(cin >> n, n > 0) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                cin >> matrix[i][j];
            }
        }
        int h=0, hp;
        for(int i=0; i<n; i++) {
            int c=0;
            for(int j=0; j<n; j++) {
                c += matrix[i][j];
            }
            if (c%2 == 1) {
                h++;
                hp=i;
            }
        }
        int v=0, vp;
        for(int j=0; j<n; j++) {
            int c=0;
            for(int i=0; i<n; i++) {
                c += matrix[i][j];
            }
            if (c%2 == 1) {
                v++;
                vp=j;
            }
        }
        if (h==0&&v==0) {
            cout << "OK" << endl;
        }
        else if (h==1&&v==1) {
            cout << "Change bit (" << (hp+1) << "," << (vp+1) << ")" << endl;
        }
        else {
            cout << "Corrupt" << endl;
        }
    }

    return 0;
}


