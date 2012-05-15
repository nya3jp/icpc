/*
 * UVA 10409 Die Game
 * 2005-07-22
 * by nya
 */

#include <iostream>
#include <algorithm>
#include <string>

const int DICE_PRIM[24] = {
    1, 2, 4, 5,
    2, 0, 5, 3,
    4, 0, 1, 3,
    1, 5, 4, 2,
    0, 2, 3, 5,
    0, 4, 3, 1,
};

int DICE_ROTATE[24][6];

/*
 * north:7
 * east:23
 * west:10
 * south:16
 */


// DICE_ROTATEÇÃèâä˙âª
void init_dice() {
    for(int t=0; t<6; t++) { // í∏ì_ÇÃêîéö
        for(int r=0; r<4; r++) { // êÇíºé≤âÒì]
            int (&v)[6] = DICE_ROTATE[t*4+r];
            v[0] = t;
            v[1] = DICE_PRIM[t*4+r];
            v[2] = DICE_PRIM[t*4+(r+1)%4];
            v[3] = (v[0]+3)%6;
            v[4] = DICE_PRIM[t*4+(r+2)%4];
            v[5] = DICE_PRIM[t*4+(r+3)%4];
        }
    }
}

struct Dice {
    int face[6];


    // âÒì]ÇµÇΩóßï˚ëÃÇï‘Ç∑
    // r = 0Å`23
    Dice rotate(int r) const {
        Dice d;
        for(int i=0; i<6; i++) {
            d.face[i] = face[DICE_ROTATE[r][i]];
        }
        return d;
    }

    // âÒì]ê≥ãKâªÇµÇΩóßï˚ëÃÇï‘Ç∑
    Dice normalize() const {
        Dice d = rotate(0);
        for(int i=1; i<24; i++) {
            Dice t = rotate(i);
            if (t < d)
                d = t;
        }
        return d;
    }

    // î‰är
    friend bool operator<(const Dice& a, const Dice& b) {
        return std::lexicographical_compare(a.face, a.face+6, b.face, b.face+6);
    }

}; // struct Dice


int main() {
    init_dice();
    int n;
    while(std::cin >> n && n != 0) {
        Dice d = { {1, 5, 4, 6, 2, 3} };
        for(int i=0; i<n; i++) {
            std::string s;
            std::cin >> s;
            if (s == "north")
                d = d.rotate(7);
            else if (s == "east")
                d = d.rotate(23);
            else if (s == "west")
                d = d.rotate(10);
            else if (s == "south")
                d = d.rotate(16);
        }
        std::cout << d.face[0] << std::endl;
    }
    return 0;
}
