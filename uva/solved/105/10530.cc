#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {

    bool v[10];
    fill(v, v+10, true);

    for(string line;;) {

        int k;
        getline(cin, line);
        sscanf(line.c_str(), "%d", &k);
        k--;

        if (k < 0)
            break;

        getline(cin, line);
        if (line == "right on") {
            cout << (v[k] ? "Stan may be honest" : "Stan is dishonest") << endl;
            fill(v, v+10, true);
        }
        else if (line == "too high") {
            fill(v+k, v+10, false);
        }
        else if (line == "too low") {
            fill(v, v+k+1, false);
        }

    }

    return 0;
}
