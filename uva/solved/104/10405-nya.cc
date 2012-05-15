/*
 * UVA 10405 Longest Common Subsequence
 * 2005-07-27
 * by nya
 */

#include <cstdio>
#include <cstring>

#define MAX_STRING 1000

int chomp(char* p) {
    int len = std::strlen(p);
    if (p[len-1] == '\n')
        p[--len] = '\0';
    return len;
}

int main() {
    char s1[MAX_STRING+1];
    char s2[MAX_STRING+1];
    int lcs[MAX_STRING+1];

    while(true) {

        std::fgets(s1, sizeof(s1), stdin);
        std::fgets(s2, sizeof(s2), stdin);
        if (std::feof(stdin))
            break;

        int len1, len2;
        len1 = chomp(s1);
        len2 = chomp(s2);

        for(int j=-1; j<len2; j++) {
            lcs[j] = 0;
        }
        for(int i=0; i<len1; i++) {
            char c = s1[i];
            int prev = 0;
            for(int j=0; j<len2; j++) {
                if (s2[j] == c) {
                    int pr = prev;
                    prev = lcs[j];
                    lcs[j] = pr+1;
                }
                else {
                    prev = lcs[j];
                    if (lcs[j-1] > lcs[j]) {
                        lcs[j] = lcs[j-1];
                    }
                }
            }
        }
        std::printf("%d\n", lcs[len2-1]);
    }
    return 0;
}
