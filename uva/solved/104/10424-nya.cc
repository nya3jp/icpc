/*
 * UVA 10424 Love Calculator
 * 2005-07-16
 * by nya
 */


#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>

int value_of_name(const std::string& name) {
    int n = name.size();
    int value = 0;
    for(int i=0; i<n; i++) {
        char c = name[i];
        if ('A' <= c && c <= 'Z') {
            value += (int)(c-'A') + 1;
        }
        else if ('a' <= c && c <= 'z') {
            value += (int)(c-'a') + 1;
        }
    }
    return value;
}

inline int compact(int n) {
    while(n >= 10) {
        int t = 0;
        while(n > 0) {
            t += n%10;
            n /= 10;
        }
        n = t;
    }
    return n;
}

int main() {

    while(true) {
        std::string girl, boy;
        std::getline(std::cin, girl);
        std::getline(std::cin, boy);
        if (! std::cin)
            break;

        int girl_n, boy_n;
        girl_n = compact( value_of_name(girl) );
        boy_n = compact( value_of_name(boy) );

        std::printf("%.2f %%\n", ((double)std::min(girl_n, boy_n) / std::max(girl_n, boy_n) * 100.0) );

    }

    return 0;
}
