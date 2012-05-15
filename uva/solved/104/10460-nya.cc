/*
 * UVA 10460 Find the Permuted String
 * 2005-08-23
 * by nya
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    int nCases;
    std::cin >> nCases;
    for(int iCase=0; iCase<nCases; iCase++) {
        std::string s;
        int index;
        std::cin >> s >> index;
        int n = (int)s.size();
        index--;

        std::vector<char> v(n);
        for(int i=0; i<n; i++)
            v[i] = i;

        for(int i=n-1; i>=0; i--) {
            int r = index % (i+1);
            index /= (i+1);
            std::rotate(v.begin()+r, v.begin()+r+1, v.begin()+i+1);
        }

        std::vector<char> t(n);
        for(int i=0; i<n; i++) {
            t[v[i]] = s[i];
        }

        std::cout << std::string(t.begin(), t.end()) << std::endl;
    }
    return 0;
}
