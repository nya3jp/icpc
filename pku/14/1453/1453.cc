#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
#include <cstring>
using namespace std;
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALLOF(c) ((c).begin()), ((c).end())

#define DEFAULT "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
string cipher = DEFAULT;
string uncipher = DEFAULT;

void set_cipher(string newcipher) {
    cipher = "";
    FOR(it, newcipher)
        if (isalpha(*it))
            cipher.push_back(toupper(*it));

    if (cipher.size() == 26) {
        string test(cipher);
        sort(ALLOF(test));
        if (unique(ALLOF(test)) == test.end()) {
            REP(i, 26)
                uncipher[(int)(cipher[i]-'A')] = (char)('A' + i);
            cout << "Good cipher.  Using " << cipher << "." << endl;
            return;
        }
    }

    cout << "Bad cipher.  Using default." << endl;
    cipher = uncipher = DEFAULT;
}

inline int toInt(char c) {
    if (isalpha(c)) {
        if (isupper(c))
            return (int)(c - 'A');
        return (int)(c - 'a');
    }
    return 0;
}

inline char base(char c) {
    if (isalpha(c)) {
        if (isupper(c))
            return 'A';
        return 'a';
    }
    return c;
}

inline char add(char c, int d) {
    while(d < 0)
        d += 26;
    if (isalpha(c)) {
        if (isupper(c))
            return (char)('A' + ((int)c - 'A' + d) % 26);
        return (char)('a' + ((int)c - 'a' + d) % 26);
    }
    return c;
}

inline char norm(char c, char r) {
    if (isupper(r))
        return toupper(c);
    return tolower(c);
}

void encrypt(string words) {
    int n = words.size();

    cout << "RESULT:  ";

    int prev = uncipher[0] - 'A';
    for(int i = 0; i < n; i++) {
        int cur = uncipher[toInt(words[i])] - 'A';
        if (isalpha(words[i])) {
            int d = cur - prev;
            if (d < 0) d += 26;
            cout << norm(cipher[d], words[i]);
        }
        else {
            cout << words[i];
        }
        prev = cur;
    }

    cout << endl;
}
void decrypt(string words) {
    int n = words.size();

    cout << "RESULT:  ";

    int prev = uncipher[0] - 'A';
    for(int i = 0; i < n; i++) {
        int cur = uncipher[toInt(words[i])] - 'A';
        if (isalpha(words[i])) {
            int d = prev + cur;
            if (d >= 26) d -= 26;
            cout << norm(cipher[d], words[i]);
            prev = d;
        }
        else {
            prev = uncipher[0] - 'A';
            cout << words[i];
        }
    }

    cout << endl;
}

int main() {

    for(;;) {
        string line;
        getline(cin, line);
        if (!cin)
            break;

        istringstream is(line);
        string cmd, param;
        is >> cmd >> ws;
        getline(is, param);

        FOR(it, cmd)
            *it = toupper(*it);

        if (cmd == "ENCRYPT") {
            encrypt(param);
        }
        else if (cmd == "DECRYPT") {
            decrypt(param);
        }
        else if (cmd == "CIPHER") {
            set_cipher(param);
        }
        else {
            cout << "Command not understood." << endl;
        }

    }

    return 0;
}

