#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int field[50][50];
int w, h;
int others[412][2];
int checks[88][2];
int nOthers, nChecks;

inline bool in_range(int x, int y) {
    return (0 <= x && x < w && 0 <= y && y < h);
}

inline int norm(int x1, int y1, int x2, int y2) {
    int dx = x2-x1;
    int dy = y2-y1;
    return dx*dx+dy*dy;
}

typedef complex<int> P;

bool cmp(const P& a, const P& b) {
    return (a.real()*b.imag() < a.imag()*b.real());
}

void init() {
    vector<P> vchecks;
    for(int x = 1; x <= 6; x++) {
        for(int y = 0; y <= 6; y++) {
            int n = norm(0, 0, x, y);
            if (n <= 36)
                vchecks.push_back(P(x, y));
        }
    }
    for(int i = 0; i < (int)vchecks.size(); i++) {
        P p = vchecks[i];
        checks[i*4+0][0] = p.real();
        checks[i*4+0][1] = p.imag();
        checks[i*4+1][0] = (p*P(0, 1)).real();
        checks[i*4+1][1] = (p*P(0, 1)).imag();
        checks[i*4+2][0] = (p*P(-1, 0)).real();
        checks[i*4+2][1] = (p*P(-1, 0)).imag();
        checks[i*4+3][0] = (p*P(0, -1)).real();
        checks[i*4+3][1] = (p*P(0, -1)).imag();
    }
    checks[vchecks.size()*4][0] = 0;
    checks[vchecks.size()*4][1] = 0;
    nChecks = vchecks.size()*4+1;
    assert(nChecks == 113);


    vector<P> vothers;
    for(int x = 1; x <= 12; x++) {
        for(int y = 0; y <= 12; y++) {
            int n = norm(0, 0, x, y);
            if (9 < n && n <= 144)
                vothers.push_back(P(x, y));
        }
    }

    for(int i = 0; i < (int)vothers.size(); i++) {
        P p = vothers[i];
        others[i*4+0][0] = p.real();
        others[i*4+0][1] = p.imag();
        others[i*4+1][0] = (p*P(0, 1)).real();
        others[i*4+1][1] = (p*P(0, 1)).imag();
        others[i*4+2][0] = (p*P(-1, 0)).real();
        others[i*4+2][1] = (p*P(-1, 0)).imag();
        others[i*4+3][0] = (p*P(0, -1)).real();
        others[i*4+3][1] = (p*P(0, -1)).imag();
    }
    nOthers = vothers.size()*4;
    //cout << nOthers << endl;
    assert(nOthers == 412);

}

int calcMinTax(int cx, int cy, int bestTax) {
    int minTax = numeric_limits<int>::max();
    for(int iOther = 0; iOther < nOthers; iOther++) {
        int ox = cx+others[iOther][0];
        int oy = cy+others[iOther][1];
        if (in_range(ox, oy) && field[ox][oy] > 0) {
            int tax = 0;
            for(int iCheck = 0; iCheck < nChecks; iCheck++) {
                int x = cx+checks[iCheck][0];
                int y = cy+checks[iCheck][1];
                if (in_range(x, y)) {
                    if (norm(cx, cy, x, y) < norm(ox, oy, x, y))
                        tax += field[x][y];
                }
                if (tax > minTax)
                    break;
            }
            minTax = min(minTax, tax);
            if (minTax < bestTax)
                return -1;
        }
    }
    return minTax;
}

int main() {
    init();

    cin >> w >> h;
    for(int y = 0; y < h; y++)
        for(int x = 0; x < w; x++)
            cin >> field[x][y];

    int bestTax = -1;
    int bx=-1, by=-1;
    for(int cx = 0; cx < w; cx++) {
        for(int cy = 0; cy < h; cy++) {
            if (field[cx][cy] > 0) {
                int tax = calcMinTax(cx, cy, bestTax);
                if (tax > bestTax) {
                    bx = cx; by = cy;
                    bestTax = tax;
                }
            }
        }
    }

    cout << "Place your castle at: " << bx << ' ' << by << endl;

    return 0;
}

