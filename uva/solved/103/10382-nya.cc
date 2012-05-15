/*
 * UVA 10382 Watering Grass
 * 2005-05-25
 * by nya
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


struct Sprinkler {
    double left, right;

    friend bool operator<(const Sprinkler& a, const Sprinkler& b) {
        return (a.left < b.left);
    }
};


int main() {

    int nSprinklers;
    double length, width;
    while(cin >> nSprinklers >> length >> width) {

        std::vector<Sprinkler> sprinklers;
        for(int iSprinkler=0; iSprinkler<nSprinklers; iSprinkler++) {
            double center, radius;
            cin >> center >> radius;
            if (radius*2 > width) {
                double halflen;
                Sprinkler sp;
                halflen = sqrt( radius*radius - width*width/4 );
                sp.left = center - halflen;
                sp.right = center + halflen;
                sprinklers.push_back(sp);
            }
        }
        nSprinklers = sprinklers.size();
        sort(sprinklers.begin(), sprinklers.end());

        double position = 0.0;
        int nUsingSprinklers = 0;
        while(position < length) {
            Sprinkler sp;
            sp.right = position;
            for(int iSprinkler=0; iSprinkler<nSprinklers && sprinklers[iSprinkler].left <= position; iSprinkler++) {
                if (sp.right < sprinklers[iSprinkler].right) {
                    sp = sprinklers[iSprinkler];
                }
            }
            if (sp.right == position) {
                nUsingSprinklers = -1;
                break;
            }
            nUsingSprinklers++;
            position = sp.right;
        }

        cout << nUsingSprinklers << endl;

    }

    return 0;
}
