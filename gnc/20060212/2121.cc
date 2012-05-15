#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cassert>

using namespace std;

struct Dictionary {
    const char* english;
    int number;
};

const Dictionary DICTIONARY[] = {
    {"negative", -1},
    {"zero", 0},
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
    {"ten", 10},
    {"eleven", 11},
    {"twelve", 12},
    {"thirteen", 13},
    {"fourteen", 14},
    {"fifteen", 15},
    {"sixteen", 16},
    {"seventeen", 17},
    {"eighteen", 18},
    {"nineteen", 19},
    {"twenty", 20},
    {"thirty", 30},
    {"forty", 40},
    {"fifty", 50},
    {"sixty", 60},
    {"seventy", 70},
    {"eighty", 80},
    {"ninety", 90},
    {"hundred", 100},
    {"thousand", 1000},
    {"million", 1000000},
    {0, 0},
};

int main() {

    string line;
    while(getline(cin, line) && !line.empty()) {
        vector<string> strings;
        {
            istringstream in(line);
            copy(istream_iterator<string>(in),
                 istream_iterator<string>(),
                 back_inserter(strings));
        }
        const int n = strings.size();
        vector<int> seq;
        for(int i = 0; i < n; i++) {
            int j;
            for(j = 0; ; j++) {
                assert(DICTIONARY[j].english);
                if (strings[i] == DICTIONARY[j].english)
                    break;
            }
            seq.push_back(DICTIONARY[j].number);
        }

        {
            int columns[3] = {0, 0, 0};
            bool negative = false;
            int i = 0;
            while(i < n) {
                if (seq[i] < 0) {
                    negative = true;
                    i++;
                }
                else if (seq[i] == 1000000) {
                    columns[2] = columns[0];
                    columns[0] = 0;
                    i++;
                }
                else if (seq[i] == 1000) {
                    columns[1] = columns[0];
                    columns[0] = 0;
                    i++;
                }
                else if (i+1 < n && seq[i+1] == 100) {
                    columns[0] += seq[i] * 100;
                    i += 2;
                }
                else {
                    columns[0] += seq[i];
                    i++;
                }
            }

            int total = (columns[2]*1000 + columns[1])*1000 + columns[0];

            if (negative)
                total = -total;

            cout << total << endl;
        }

    }
    
    return 0;
}
