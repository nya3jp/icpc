/*
 * UVA 10403 Escape from Tut's Tomb
 * 2005-08-11
 * by nya
 */

#include <cstdio>
#include <vector>
#include <map>
#include <ctype.h>
#include <utility>
#include <algorithm>
#include <cassert>

inline int sgn(int n) {
    return (n == 0 ? 0 : n > 0 ? 1 : -1);
}

struct Hint {
    unsigned int bits;
    int sign;
};
bool operator<(const Hint& a, const Hint& b) {
    return (a.bits < b.bits);
}

struct Found {};
struct Impossible {};

typedef std::vector< std::vector<Hint> > Hints;

void search(int depth,
            std::vector<int>& stones,
            std::vector<bool>& used,
            int nStones,
            const Hints& hints)
{
    if (depth == nStones)
        throw Found();

    {
        const Hints::value_type& chints = hints[depth];
        for(Hints::value_type::const_iterator it = chints.begin(); it != chints.end(); ++it) {
            const Hint& hint = *it;
            int sum = 0;
            for(int i=0; i<nStones; i++) {
                if ((hint.bits & (1 << i)) != 0)
                    sum += stones[i];
            }
            if (sgn(sum - ( nStones*(nStones+1)/2 - sum ) ) != hint.sign)
                return;
        }
    }

    // rough pruning
    for(int iPrun=depth+1; iPrun<nStones; iPrun++) {
        const Hints::value_type& chints = hints[iPrun];
        for(Hints::value_type::const_iterator it = chints.begin(); it != chints.end(); ++it) {
            const Hint& hint = *it;
            int sum = 0;
            for(int i=0; i<depth; i++) {
                if ((hint.bits & (1 << i)) != 0)
                    sum += stones[i];
            }
            int n = 0;
            for(int i=depth; i<iPrun; i++) {
                if ((hint.bits & (1 << i)) != 0)
                    n++;
            }
            assert(n != 0);
            if (hint.sign <= 0) {
                int min = sum + n*(n+1)/2;
                if ( min > ( nStones*(nStones+1)/2 - min ) )
                    return;
            }
            if (hint.sign >= 0) {
                int max = sum + (nStones-n+1 + nStones)*n/2;
                if ( max < ( nStones*(nStones+1)/2 - max ) )
                    return;
            }
        }
    }

    for(int iStone=0; iStone<nStones; iStone++) {
        if (! used[iStone]) {
            stones[depth] = iStone+1;
            used[iStone] = true;
            search(depth+1, stones, used, nStones, hints);
            used[iStone] = false;
        }
    }
}


bool read_hints(Hints& hints, int nStones, int nHints)
{
    bool possible = true;
    std::map<int, int> checks;
    for(int iHint=0; iHint<nHints; iHint++) {
        Hint hint;
        hint.bits = 0;
        hint.sign = 2;
        for(int i=0; i<nStones+1; i++) {
            char c;
            std::scanf(" %c", &c);
            if (hint.sign == 2) {
                if (isalpha(c)) {
                    hint.bits |= 1 << (int)(c - 'a');
                }
                else {
                    hint.sign = (c == '=' ? 0 : c == '<' ? -1 : 1);
                }
            }
        }
        if ((hint.bits & (1 << (nStones-1))) != 0) {
            hint.bits ^= (1 << nStones) - 1;
            hint.sign = -hint.sign;
        }

        int index = 26;
        while(index > 0) {
            if ((hint.bits & (1 << (index - 1))) != 0)
                break;
            index--;
        }
        hints[index].push_back(hint);

        if (! checks.insert( std::make_pair(hint.bits, hint.sign) ).second) {
            if (checks[hint.bits] != hint.sign)
                possible = false;
        }
        //std::fprintf(stderr, "Hint(%d) = {bits=%x(%d); sign=%d}\n", iHint, hint.bits, index, hint.sign);
    }

    return possible;
}


int main() {
    int nStones, nHints;
    while(std::scanf("%d%d", &nStones, &nHints) == 2) {
        Hints hints(nStones);

        bool precheck = read_hints(hints, nStones, nHints);
        if (! precheck) {
            std::printf("No solution possible!\n");
            continue;
        }

        std::vector<int> stones(nStones);
        std::vector<bool> used(nStones, false);
        try {
            search(0, stones, used, nStones, hints);
            std::printf("No solution possible!\n");
        }
        catch(Found) {
            std::printf("Solution:");
            for(int i=0; i<nStones; i++)
                std::printf(" %d", stones[i]);
            std::printf("\n");
        }
    }
    return 0;
}
