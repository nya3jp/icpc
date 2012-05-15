#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

const char* KEYS[12] = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

const int MAJORS[] = {
    0, 2, 4, 5, 7, 9, 11
};

const int UNMAJORS[] = {
    1, 3, 6, 8, 10
};

int main() {

    map<string,int> keyToInt;
    for(int i = 0; i < 12; i++)
        keyToInt[KEYS[i]] = i;

    string line;
    while(getline(cin, line) && line != "END") {

        istringstream is(line);
        bool keys[12];
        fill(keys, keys+12, false);
        for(string s; is >> s; ) {
            int k = keyToInt[s];
            keys[k] = true;
        }

        bool majors[12];
        fill(majors, majors+12, true);
        for(int i = 0; i < 12; i++) {
            if (keys[i]) {
                for(int j = 0; j < 5; j++)
                    majors[(i-UNMAJORS[j]+12)%12] = false;
            }
        }

        bool first = true;
        for(int i = 0; i < 12; i++) {
            if (majors[i]) {
                if (!first)
                    cout << " ";
                first = false;
                cout << KEYS[i];
            }
        }
        cout << endl;

    }

    return 0;
}
