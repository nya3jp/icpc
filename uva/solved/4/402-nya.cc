/*
 * UVA 402 M*A*S*H
 * 2004-12-29
 * by nya
 */

#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>

using namespace std;


int main(int argc, char** argv)
{

    for(int iCase=0; ; iCase++) {

        int nPeople;
        int nLuckyes;

        cin >> nPeople;
        cin >> nLuckyes;
        if (! cin) break;

        int deck[20];
        for(int i=0; i<20; i++) {
            cin >> deck[i];
        }

        list<int> line;
        for(int i=0; i<nPeople; i++) {
            line.push_back(i);
        }

        {
            list<int>::iterator current = line.begin();

            for(int iCard=0; iCard<20; ) {
                if (line.size() <= nLuckyes)
                    break;

                for(int i = 0; i < (deck[iCard]-1) && current != line.end(); i++) {
                    current++;
                }
                if (current != line.end()) {
                    line.erase(current++);
                }
                if (current == line.end()) {
                    current = line.begin();
                    iCard++;
                }

#if 0
                    cerr << "step" << iCard << endl;
                    ostream_iterator<int> o(cerr, " ");
                    copy(line.begin(), line.end(), o);
                    cerr << endl;
#endif
            }
        }

        cout << "Selection #" << (iCase+1) << endl;
        for(list<int>::const_iterator it = line.begin(); it != line.end(); it++) {
            if (it != line.begin())
                cout << " ";
            cout << (*it+1);
        }
        cout << endl << endl;

    }

    return 0;
}




