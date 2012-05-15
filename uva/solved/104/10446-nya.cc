/*
 * UVA 10446 The Marriage Interview :-)
 * 2005-08-19
 * by nya
 */

#include <iostream>
#include <vector>

const unsigned long long int NIL = 0;

template<class T>
struct Matrix : public std::vector< std::vector<T> > {
    Matrix(int n, T def = T()) : std::vector< std::vector<T> >(n, std::vector<T>(n, def)) {
    }
};
typedef Matrix<unsigned long long int> Memory;

unsigned long long int trib(int n, int back, Memory& m) {
    if (n <= 1)
        return 1;
    if (back <= 0)
        return 1;
    if (m[n][back] == NIL) {
        unsigned long long int calls = 1;
        for(int i=1; i<=back; i++)
            calls += trib(n-i, back, m);
        m[n][back] = calls;
    }
    return m[n][back];
}

int main() {

    Memory m(61, NIL);

    int iCase=0;
    int n, back;
    while(std::cin >> n >> back) {
        if (n > 60)
            break;

        std::cout << "Case " << (++iCase) << ": " << trib(n, back, m) << std::endl;
    }
    return 0;
}
