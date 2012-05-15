/*
 * UVA 10493 Cats, with or without Hats
 * 2005-07-20
 * by nya
 */

#include <iostream>

int main() {
    int n, m;
    while(std::cin >> n >> m && n != 0) {
        std::cout << n << ' ' << m << ' ';
        if (n == 1) {
            if (m == 1) {
                std::cout << "Multiple";
            }
            else {
                std::cout << "Impossible";
            }
        }
        else {
            if ((m-n)%(n-1) == 0) {
                std::cout << ( (n+1) + n*( (m-n)/(n-1) ) );
            }
            else {
                std::cout << "Impossible";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
