/*
 * UVA 10420 List of Conquests
 * 2005-07-17
 * by nya
 */

#include <cstdio>
#include <map>
#include <string>


int main() {
    int n;
    std::scanf("%d", &n);
    std::map< std::string, int > m;
    for(int i=0; i<n; i++) {
        char c[100];
        std::scanf("%s %*[^\n]", c);
        m[c]++;
    }
    for(std::map< std::string, int >::const_iterator it = m.begin();
        it != m.end();
        ++it) {
        std::printf("%s %d\n", it->first.data(), it->second);
    }
    return 0;
}


