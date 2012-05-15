/*
 * UVA 10411 Another Game of Tetris
 * 2005-08-11
 * by nya
 */

#include <cstdio>
#include <cassert>

struct Block {
    int width;
    int base[4];
    int height[4];
};


const int BLOCKS = 19;
const Block blocks[] = {
    {1,
     {0},
     {4}},
    {4,
     {0, 0, 0, 0},
     {1, 1, 1, 1}},
    {2,
     {0, 0},
     {2, 2}},
    {3,
     {1, 0, 0},
     {1, 2, 1}},
    {3,
     {0, 0, 1},
     {1, 2, 1}},
    {2,
     {1, 0},
     {2, 2}},
    {2,
     {0, 1},
     {2, 2}},
    {3,
     {0, 0, 0},
     {1, 2, 1}},
    {3,
     {1, 0, 1},
     {1, 2, 1}},
    {2,
     {1, 0},
     {1, 3}},
    {2,
     {0, 1},
     {3, 1}},
    {3,
     {0, 1, 1},
     {2, 1, 1}},
    {3,
     {1, 1, 0},
     {1, 1, 2}},
    {3,
     {0, 0, 0},
     {2, 1, 1}},
    {3,
     {0, 0, 0},
     {1, 1, 2}},
    {2,
     {0, 2},
     {3, 1}},
    {2,
     {2, 0},
     {1, 3}},
    {2,
     {0, 0},
     {3, 1}},
    {2,
     {0, 0},
     {1, 3}},
};

/*
void normalize(std::vector<int>& v) {
    std::transform(v.begin(), v.end(), v.begin(), std::bind2nd(std::minus<int>(), *std::min_element(v.begin(), v.end())));
}
*/

//bool acceptable(const std::vector<int>& v) {
bool acceptable(const int* field, int nWidth) {
    bool result = true;
    for(int i=1; i<nWidth; i++) {
        if (field[i] != field[0]) {
            result = false;
            break;
        }
    }
    return result;
}

inline int abs(int i) {
    return (i < 0 ? -i : i);
}

//int evaluate(const std::vector<int>& v) {
int evaluate(const int* field, int nWidth) {
    int value = 0;
    int max = field[0]; //*std::max_element(field, field+nWidth);
    for(int i=1; i<nWidth; i++) {
        int h = field[i];
        if (h != field[i-1]) { // なるべくでこぼこしてない方が良い
            value += 1; //abs(field[i] - field[i-1]);
        }
        if (h > max)
            max = h;
    }
    value += max*1000; // 最大の高さは低い方が良い
    return value;
}

struct Turn {
    int iBlock, iPos, value;
};

//Turn search(int depth, std::vector<int>& field) {
Turn search(int depth, int* field, int nWidth) {
    Turn turn;
    turn.value = 0x7fffffff; // std::numeric_limits<int>::min();

    if (acceptable(field, nWidth)) {
        turn.iBlock = turn.iPos = -1;
        turn.value = -1;
    }
    else if (depth == 0) {
        turn.iBlock = turn.iPos = -1;
        turn.value = evaluate(field, nWidth);
    }
    else {
        for(int iBlock=0; iBlock<BLOCKS; iBlock++) {
            const Block& b = blocks[iBlock];
            for(int iPos=0; iPos<=nWidth-b.width; iPos++) {
                int offset = field[iPos] - b.base[0];
                bool ok = true;
                for(int i=1; i<b.width; i++) {
                    if (field[iPos+i] != b.base[i] + offset) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    for(int i=0; i<b.width; i++) {
                        field[iPos+i] += b.height[i];
                    }
                    //normalize(newfield);
                    Turn t = search(depth-1, field, nWidth);
                    for(int i=0; i<b.width; i++) {
                        field[iPos+i] -= b.height[i];
                    }
                    if (t.value < turn.value) {
                        turn.value = t.value;
                        turn.iBlock = iBlock;
                        turn.iPos = iPos;
                        if (turn.value < 0)
                            break;
                    }
                }
            }
        }
    }

    return turn;
}


int main() {
    int nCases;
    std::scanf("%d", &nCases);
    for(int iCase=0; iCase<nCases; iCase++) {
        int nWidth;
        std::scanf("%d", &nWidth);
        //std::vector<int> field(nWidth);
        int field[nWidth];
        for(int i=0; i<nWidth; i++)
            std::scanf("%d", &field[i]);
        //normalize(field);

        int iRound;
        for(iRound = 0; iRound <= 10010 && !acceptable(field, nWidth); iRound++) {
            Turn turn = search(1, field, nWidth);
            assert(turn.iBlock >= 0);

            {
                const Block& b = blocks[turn.iBlock];
                for(int i=0; i<b.width; i++) {
                    field[turn.iPos+i] += b.height[i];
                }
            }
            //normalize(field);

#if 1
            std::printf("%d %d\n", turn.iBlock+1, turn.iPos+1);
#endif
#if 0
            for(int i=0; i<nWidth; i++) {
                std::printf("%6d", field[i]);
            }
            std::printf("\n");
#endif

        }

        if (iRound > 10000) {
            //std::printf("Output Limit Exceeded\n");
        }

        std::printf("-1 -1\n");
        
    }
    return 0;
}








