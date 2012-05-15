/*
 * Strategic Defense Initiative
 * 2005-06-14
 * by nya
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>

struct EmptyLineException {};

template<class T>
T getLine(std::istream& is) {
    std::string s;
    std::getline(is, s);
    if (! is) throw EmptyLineException();
    std::istringstream is2(s);
    T t;
    is2 >> t;
    if (! is2) throw EmptyLineException();
    return t;
}

void feedLine(std::istream& is) {
    std::string s;
    std::getline(is, s);
}

int main() {

    int nCases = getLine<int>(std::cin);
    feedLine(std::cin);

    for(int iCase=0; iCase<nCases; iCase++) {

        std::vector<int> vMissile;

        while(true) {
            int h;
            try {
                h = getLine<int>(std::cin);
            }
            catch(EmptyLineException) {
                break;
            }
            vMissile.push_back(h);
        }

        int nMissiles = vMissile.size();

        std::vector< std::pair<int,int> > vTable;

        for(int iLast=0; iLast<nMissiles; iLast++) {
            std::pair<int, int> best(1, -1);
            for(int iPrev=0; iPrev<iLast; iPrev++) {
                if (vMissile[iPrev] < vMissile[iLast] && vTable[iPrev].first+1 > best.first) {
                    best.first = vTable[iPrev].first + 1;
                    best.second = iPrev;
                }
            }
            //std::cerr << best.first << ',' << best.second << std::endl;
            vTable.push_back(best);
        }

        {
            std::pair<int, int> last(0, -1);
            for(int iLast=0; iLast<nMissiles; iLast++) {
                if (vTable[iLast].first > last.first) {
                    last.first = vTable[iLast].first;
                    last.second = iLast;
                }
            }
            std::vector<int> vCommand;
            for(int missile = last.second; missile != -1; missile = vTable[missile].second) {
                vCommand.push_back(vMissile[missile]);
            }

            if (iCase > 0)
                std::cout << std::endl;
            std::cout << "Max hits: " << vCommand.size() << std::endl;
            std::copy(vCommand.rbegin(), vCommand.rend(), std::ostream_iterator<int>(std::cout, "\n"));
        }

    }

    std::cout.flush();
    return 0;
}
