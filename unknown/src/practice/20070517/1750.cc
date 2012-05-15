#include <cstdio>
#include <complex>
#include <vector>
#include <cctype>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

int main() {

    char chain[20] = {'\0'};

    bool first = true;
    for(;;) {
        char word[20];
        if (scanf("%s", word) != 1)
            break;
        /*
        gets(word);
        if (feof(stdin))
            break;
        */

        int match_length = 0;
        while(chain[match_length] != '\0') {
            if (chain[match_length] != word[match_length])
                break;
            match_length++;
        }
        if (!first)
            printf("\n");
        first = false;
        for(int i = 0; i < match_length; i++)
            putc(' ', stdout);
        printf("%s", word);
        chain[match_length] = word[match_length];
        /*
        if (isspace(chain[match_length]))
            chain[match_length] = '\0';
        */
    }

    fflush(stdout);

    return 0;
}
