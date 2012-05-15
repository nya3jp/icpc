/*
 * UVA 10453 Make Palindrome
 * 2005-08-20
 * by nya
 */

#define NDEBUG

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define N 1000

int table[N+1][N+1];

void init() {
    for(int i=0; i<=N; i++) {
        for(int j=0; j<=i; j++) {
            table[i][j] = 0;
        }
    }
}

void make_match_table(const std::string& s) {
    int n = s.size();
    for(int i=n-1; i>=0; i--) {
        for(int j=i+1; j<n; j++) {
            if (s[i] == s[j]) {
                table[i][j] = table[i+1][j-1];
            }
            else {
                table[i][j] = std::min(table[i+1][j], table[i][j-1]) + 1;
            }
        }
    }
}

int make_match(const std::string& s) {
    int n = s.size();
    make_match_table(s);
#ifndef NDEBUG
    std::cerr << "match table:" << std::endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            std::cerr << table[i][j] << ' ';
        }
        std::cerr << std::endl;
    }
#endif
    return table[0][n-1];
}

std::string get_match(const std::string& s) {
    int n = s.size();
    std::vector<char> v1, v2;
#ifndef NDEBUG
    std::cerr << "get_match:" << std::endl;
#endif
    for(int i=0, j=n-1; i <= j; ) {
#ifndef NDEBUG
        std::cerr << "(" << i << "," << j << ")" << std::endl;
#endif
        if (s[i] == s[j]) {
            v1.push_back(s[i]);
            if (i < j)
                v2.push_back(s[j]);
            i++; j--;
        }
        else {
            if (table[i+1][j] < table[i][j-1]) {
                v1.push_back(s[i]);
                v2.push_back(s[i]);
                i++;
            }
            else {
                v1.push_back(s[j]);
                v2.push_back(s[j]);
                j--;
            }
        }
    }
    return (std::string(v1.begin(), v1.end()) + std::string(v2.rbegin(), v2.rend()));
}

std::string make_palindrome(const std::string& s) {
    make_match(s);
    return get_match(s);
}


int main() {
    init();
    std::string str;
    while(std::cin >> str) {
        std::string palindrome = make_palindrome(str);
        std::cout << (int)(palindrome.size() - str.size()) << ' ' << palindrome << std::endl;
    }
    return 0;
}
