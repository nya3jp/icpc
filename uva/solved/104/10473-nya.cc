/*
 * UVA 10473 Simple Base Conversion
 * 2005-08-02
 * by nya
 */

#include <iostream>
#include <string>
#include <cstdio>

int main() {
    while(true) {
        std::string s;
        std::cin >> s;
        if (s[0] == '-')
            break;
        int n;
        if (s.substr(0, 2) == "0x") {
            std::sscanf(s.c_str()+2, "%x", &n);
            std::printf("%d\n", n);
        }
        else {
            std::sscanf(s.c_str(), "%d", &n);
            std::printf("0x%X\n", n);
        }
    }
    return 0;
}
