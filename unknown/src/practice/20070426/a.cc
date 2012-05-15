#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int parseTime(string time) {
    //cout << "parse(" << time << endl;
    if (time == "-:--:--")
        return -1;
    int h, m, s;
    sscanf(time.c_str(), "%d:%d:%d", &h, &m, &s);
    return ((h*60+m)*60+s);
}

int main() {

    int nSections;
    double totalDistance;

    cin >> nSections >> totalDistance >> ws;

    for(string line; getline(cin, line); ) {

        istringstream is(line);

        int teamID;
        is >> teamID;

        int timeTotal = 0;
        bool error = false;
        REP(i, nSections) {
            string time;
            is >> time;
            int timeLocal = parseTime(time);
            if (timeLocal < 0)
                error = true;
            else
                timeTotal += timeLocal;
        }

        //cout << timeTotal << " / " << totalDistance << endl;

        int res = (int)((double)timeTotal / totalDistance + 0.5);

        printf("%3d: ", teamID);
        if (error)
            printf("-\n");
        else
            printf("%d:%02d min/km\n", res/60, res%60);

    }

    return 0;
}

