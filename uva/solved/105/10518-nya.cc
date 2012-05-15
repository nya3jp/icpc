/*
 * UVA 10518 How Many Calls?
 * 2005-06-28
 * by nya
 */

#include <iostream>
#include <vector>

std::vector<unsigned int> v;

unsigned int solve(unsigned long long int n, unsigned int b) {
    if (b == 1)
        return 0;

    v.clear();
    v.reserve(5000);

    v.push_back(1);
    v.push_back(1);
    unsigned int loop = 0;
    unsigned int pp, p;
    pp = p = 1;
    do {
        unsigned int next = (pp + p + 1)%b;
        pp = p;
        p = next;
        v.push_back(next);
        loop++;
    } while(! (pp == 1 && p == 1));

    return v[ n % loop ];
}

int main() {

    unsigned long long int n;
    unsigned int b;
    int iCase = 0;
    while(std::cin >> n >> b && !(n == 0 && b == 0)) {

        std::cout << "Case " << ++iCase << ": "
                  << n << " " << b << " " << solve(n, b)
                  << std::endl;

    }

    return 0;
}
