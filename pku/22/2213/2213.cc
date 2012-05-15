#include <iostream>
#include <string>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int decode_graycode(int gray, int n) {
    if (n == 0)
        return 0;
    if (gray & (1<<(n-1)))
        return (1<<n)-1-decode_graycode(gray&((1<<n)-1), n-1);
    return decode_graycode(gray, n-1);
}

int parse_binary(string str) {
    int res = 0;
    REP(i, str.size())
        res = (res<<1) | (str[i] == '1' ? 1 : 0);
    return res;
}

int main() {
    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        int n;
        string bin;
        cin >> n >> bin;
        cout << "Poslanec "
             << iCase+1
             << " se posadi na sedadlo cislo "
             << decode_graycode(parse_binary(bin), n)+1
             << "."
             << endl;
    }
    return 0;
}
