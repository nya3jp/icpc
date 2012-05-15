/*
 * Tell me the frequencies! - UVA 10062
 * 2004-12-18
 * coded by nya
 */

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct freq {
    char code;
    int n;
    freq(char code=0, int n=0) : code(code), n(n) {}
};

bool operator<(const freq& a, const freq& b)
{
    if (a.n != b.n)
        return (a.n < b.n);
    return ((unsigned char)a.code > (unsigned char)b.code);
}

int main(int argc, char** argv)
{

    for(int iCase=0; ; iCase++) {
        char buf[1024];
        cin.getline(buf, sizeof(buf));
        if (! cin)
            break;

        const string text(buf);

        map<char, int> f;
        for(int i=0; i<text.length(); i++) {
            f[text[i]]++;
        }

        vector<freq> v;
        for(map<char,int>::const_iterator it = f.begin(); it != f.end(); it++) {
            v.push_back(freq(it->first, it->second));
        }

        sort(v.begin(), v.end());

        if (iCase > 0)
            cout << endl;

        for(int i=0; i<v.size(); i++) {
            cout << (int)(unsigned char)v[i].code << " " << v[i].n << endl;
        }

    }

    return 0;
}
