#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End

enum InstructionCode {
    PRINT = -1,
    LOCK = -2,
    UNLOCK = -3,
};

int nPrograms;
int variables[26];
vector<pair<int,int> > programs[10];
int programCounters[10];
int executionTimes[5];
int quantum;

deque<int> readyQueue;
deque<int> blockQueue;
bool locked;

void process() {

    REP(i, 26)
        variables[i] = 0;
    locked = false;

    readyQueue.clear();
    blockQueue.clear();
    REP(iProgram, nPrograms) {
        readyQueue.push_back(iProgram);
        programCounters[iProgram] = 0;
    }

    int nPasses = 0;

    while(nPasses < nPrograms) {

        int nextProgram = readyQueue.front();
        readyQueue.pop_front();

        //cout << "Next program: " << nextProgram << endl;

        int& pc = programCounters[nextProgram];
        int timeSlice = quantum;

        bool blocking = false;

        while(timeSlice > 0) {

            //cout << " remaining time slice: " << timeSlice << endl;

            if (pc == (int)programs[nextProgram].size()) {
                nPasses++;
                //cout << " this program has already finished" << endl;
                break;
            }

            nPasses = 0;

            int cmd = programs[nextProgram][pc].first;
            int param = programs[nextProgram][pc].second;
            pc++;

            //cout << " pc" << pc << " -> " << cmd << " " << param << endl;

            switch(cmd) {
            case PRINT: {
                timeSlice -= executionTimes[1];
                cout << nextProgram+1 << ": " << variables[param] << endl;
                break;
            }
            case LOCK: {
                timeSlice -= executionTimes[2];
                if (locked) {
                    blocking = true;
                    pc--;
                    break;
                }
                else {
                    locked = true;
                }
                break;
            }
            case UNLOCK: {
                timeSlice -= executionTimes[3];
                assert(locked);
                locked = false;
                if (!blockQueue.empty()) {
                    readyQueue.push_front(blockQueue.front());
                    blockQueue.pop_front();
                }
                break;
            }
            default: {
                timeSlice -= executionTimes[0];
                variables[cmd] = param;
                break;
            }
            }
        }

        (blocking ? blockQueue : readyQueue).push_back(nextProgram);

    }


}

int main() {

    cin >> nPrograms;
    REP(i, 5)
        cin >> executionTimes[i];
    cin >> quantum;

    REP(iProgram, nPrograms) {
        for(;;) {
            char s[16];
            int k;
            scanf(" %[^= \t\r\n] = %d", s, &k);
            //cout << "\"" << s << "\"" << endl;
            string cmd(s);
            if (cmd == "print") {
                scanf(" %c", &s[0]);
                programs[iProgram].push_back(make_pair(PRINT, (int)(s[0]-'a')));
            }
            else if (cmd == "lock") {
                programs[iProgram].push_back(make_pair(LOCK, 0));
            }
            else if (cmd == "unlock") {
                programs[iProgram].push_back(make_pair(UNLOCK, 0));
            }
            else if (cmd == "end") {
                break;
            }
            else {
                programs[iProgram].push_back(make_pair((int)(s[0]-'a'), k));
            }
            //cout << programs[iProgram].back().first << "," << programs[iProgram].back().second << endl;
        }
    }

    process();

    return 0;
}

// Powered by Fate Testarossa
