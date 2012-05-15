#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const char* TILES[19] = {
    "a1111000000000000",
    "b1100110000000000",
    "c1100011000000000",
    "d0110110000000000",
    "e1000111000000000",
    "f1110100000000000",
    "g0100111000000000",
    "a1000100010001000",
    "c0100110010000000",
    "d1000110001000000",
    "e1100100010000000",
    "f1100010001000000",
    "g1000110010000000",
    "e1110001000000000",
    "f0010111000000000",
    "g1110010000000000",
    "e0100010011000000",
    "f1000100011000000",
    "g0100110001000000",
};

struct Tile {
    long long int pattern;
    int width, height;
    Tile() : pattern(0) {}
};

Tile tiles[7][4];

void init() {
    int order[7];
    fill(order, order+7, 0);
    for(int i = 0; i < 19; i++) {
        int id = (int)(TILES[i][0] - 'a');
        int ord = order[id]++;
        //cout << id << "," << ord << endl;
        Tile& t = tiles[id][ord];
        long long int& ptn = t.pattern;
        ptn = 0;
        t.width = 0; t.height = 1;
        const char* s = TILES[i]+1;
        for(int x = 0; x < 4; x++) {
            for(int y = 0; y < 4; y++) {
                int j = y*4+x;
                int b = 1<<(y*6+x);
                if (s[j] == '1') {
                    t.width = max(t.width, x+1);
                    t.height = max(t.height, y+1);
                    ptn |= b;
                }
            }
        }
    }
    //cout << tiles[0][1].pattern << endl;
}

int mytiles[9];
bool used[9];
char map[36];

bool search(int iTile, int pos, long long int field, bool* used) {
    if (pos == 36) {
        //cout << "congratu" << endl;
        return true;
    }
    if (((field>>pos)&1) == 1)
        return search(iTile, pos+1, field, used);
    int x = pos%6;
    int y = pos/6;
    for(int ord = 0; ord < 4; ord++) {
        for(int i = 0; i < 9; i++) {
            Tile& t = tiles[mytiles[i]][ord];
            if (t.pattern == 0)
                continue;
            if (used[i])
                continue;
            if (t.width+x <= 6 && t.height+y <= 6 &&
                ((field>>pos)&t.pattern) == 0) {
                used[i] = true;
                if (search(iTile+1, pos, field|(t.pattern<<pos), used)) {
                    for(int k = 0; pos+k < 36; k++) {
                        if (((t.pattern>>k)&1) == 1) {
                            map[pos+k] = (char)('A'+i);
                        }
                    }
                    return true;
                }
                used[i] = false;
            }
        }
    }
    return false;
}

bool solve() {
    fill(used, used+9, false);
    return search(0, 0, 0, used);
}


int main() {
    init();
    int nCases;
    cin >> nCases;
    for(int iCase = 0; iCase < nCases; iCase++) {
        for(int i = 0; i < 9; i++) {
            cin >> mytiles[i];
            mytiles[i]--;
        }
        cout << "Data Set " << iCase+1 << endl;
        if (solve()) {
            cout << "The floor may be tiled." << endl;
            for(int i = 0; i < 6; i++) {
                cout << string(map+i*6, map+i*6+6) << endl;
            }
        }
        else {
            cout << "The floor may not be tiled." << endl;
        }
        cout << endl;
    }
    cout << "End of Output" << endl;

    return 0;
}
