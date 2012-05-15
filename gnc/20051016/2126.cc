#include <iostream>

int main() {
    int n;
    std::cin >> n;
    bool irreducible = false;
    if (n == 0 || n == 1) {
        irreducible = true;
    }
    else if (n == 2) {
        for(int i=0; i<n-2; i++) {
            int t;
            std::cin >> t;
        }
        int a2, a1, a0;
        std::cin >> a2 >> a1 >> a0;
        irreducible = (a1*a1 - 4*a2*a0 < 0);
    }
    else {
        irreducible = false;
    }
    std::cout << (irreducible ? "YES" : "NO") << std::endl;
    return 0;
}
