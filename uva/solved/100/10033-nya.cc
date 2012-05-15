/*
 * UVA 10033 Interpreter
 * 2004-12-17
 * coded by nya
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

#define BUFSIZE (16*1024)

int run(vector<int>& ram, vector<int>& reg)
{
    int nInstructions = 0;
    int iProgramCounter = 0;

    while(true) {
        nInstructions++;
        int inst = ram[iProgramCounter];
        int type = inst/100;
        int high = inst/10%10;
        int low = inst%10;

        if (inst == 100)
            break;

        switch(type) {
        case 2:
            reg[high] = low;
            break;
        case 3:
            reg[high] = (reg[high] + low)%1000;
            break;
        case 4:
            reg[high] = (reg[high] * low)%1000;
            break;
        case 5:
            reg[high] = reg[low];
            break;
        case 6:
            reg[high] = (reg[high] + reg[low])%1000;
            break;
        case 7:
            reg[high] = (reg[high] * reg[low])%1000;
            break;
        case 8:
            reg[high] = ram[reg[low]];
            break;
        case 9:
            ram[reg[low]] = reg[high];
            break;
        case 0:
            if (reg[low] != 0)
                iProgramCounter = reg[high] - 1;
            break;
        }
        iProgramCounter++;
    }

    return nInstructions;
}

int main(int argc, char** argv)
{

    int nCases;
    cin >> nCases >> ws;

    for(int iCase = 0; iCase < nCases; iCase++) {

        vector<int> reg, ram;
        reg.resize(10);
        ram.resize(1000);

        {
            int iPos = 0;
            char* buf = new char[BUFSIZE];
            while(true) {
                cin.getline(buf, BUFSIZE);
                size_t len = strlen(buf);
                if (len == 0 || (! cin))
                    break;
                char* p = buf;
                while(true) {
                    while(isspace(*p))
                        p++;
                    if (*p == '\0')
                        break;
                    int t = 0;
                    for(int i=0; i<3; i++) {
                        t = t*10 + (*p - '0');
                        p++;
                    }
                    ram[iPos++] = t;
                }
            }
            delete [] buf;
        }

        if (iCase > 0)
            cout << endl;

        cout << run(ram, reg) << endl;
    }

    return 0;
}
