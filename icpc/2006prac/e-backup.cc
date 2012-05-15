/*

TODO:

初期化

 */


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define EQ(a, b) (abs((a)-(b)) < 1.0e-8)

struct El {
    int dest, bag, capacity;
    double pos, speed, wait;
    bool working;
    double nextEvent;
    El() {
        bag = 0;
        working = false;
    }
};


struct Building {
    vector<int> devices;
    int lowerMoeStep, upperMoeStep;
    int moeCenter, upperMoeSpeed, lowerMoeSpeed;
    int floorInterval;
};

void refresh(Building& building, vector<El>& els, double currentTime) {
    int n = els.size();
    for(int i = 0; i < n; i++) {
        El& e = els[i];
        if (e.working) {
            // do nothing
        }
        else {
            int dest = (int)building.devices.size() - 1;
            while(dest > 0) {
                if (building.devices[dest] > 0)
                    break;
                dest--;
            }
            if (e.bag == e.capacity)
                dest = 0;
            if (dest == 0 && EQ(e.pos, 0)) {
                e.working = true;
                e.nextEvent = 2.0e100;
            }
            else {
                e.dest = dest;
                e.nextEvent = currentTime + abs(building.floorInterval*dest - e.pos) / e.speed;
            }
        }
    }
}

void sim(vector<El>& els, Building& building) {

    double prevTime = 0;
    int n = els.size();

    refresh(building, els, 0);

    while(true) {

        vector<double> times(n+2);
        for(int i = 0; i < n; i++) {
            times[i] = els[i].nextEvent;
        }
        times[n] = building.upperMoeSpeed * (building.upperMoeStep+1);// next uppermoetuki
        times[n+1] = building.lowerMoeSpeed * (building.lowerMoeStep+1);// next lowermoetuki

        if (*min_element(times.begin(), times.begin()+n) > 1.0e100)
            break;

        int iNextEvent = min_element(times.begin(), times.end()) - times.begin();

        double currentTime = times[iNextElement];

        for(int i = 0; i < n; i++) {
            El& e = els[i];
            if (!e.working) {
                if (building.floorInterval*dest > e.pos) {
                    // moving upward
                    e.pos += (currentTime - prevTime) * e.speed;
                }
                else {
                    // moving downward
                    e.pos += (currentTime - prevTime) * -e.speed;
                }
            }
        }

        if (iNextEvent == n) {
            building.upperMoeStep++;
            if (moeCenter+building.upperMoeStep < (int)building.devices.size())
                building.devices[moeCenter+building.upperMoeStep] = 0;
            // uppermoetuki
        }
        else if (iNextEvent == n+1) {
            building.lowerMoeStep++;
            if (moeCenter-building.lowerMoeStep >= 0)
                building.devices[moeCenter-building.lowerMoeStep] = 0;
            // lowermoetuki
        }
        else {
            El& e = els[iNextEvent];
            if (e.working) {
                e.working = false;
            }
            else {
                if (e.dest == 0) {
                    // rescued
                    cout << "elevator " << iNextEvent << " rescued " << e.bag << endl;
                    e.bag = 0;
                }
                else {
                    int getdevices = min(building.devices[e.dest], e.capacity-e.bag);
                    buliding.devices[e.dest] -= getdevices;
                    e.bag += getdevices;
                    e.working = true;
                    e.nextEvent += e.wait;
                }
            }
        }

        refresh(building, els, currentTime);

        prevTime = currentTime;

    }

}



int main() {

    while(true) {

        cin >> nFloors >> nElevators
            >> floorInterval;

        if (nFloors == 0 && nElevators == 0)
            break;

        Building b;
        vector<El> els(nElevators);
        b.devices.resize(nFloors);
        b.floorInterval = floorInterval;

        for(int i = 0; i < nFloors; i++) {
            cin >> b.devices[i];
        }

        for(int i = 0; i < nElevators; i++) {
            El& e = els[i];

            int flr;
            cin >> e.capacity >> e.speed >> e.wait >> flr;
            e.pos = (flr-1)*floorInterval;
        }

        int moeTime;
        cin >> b.moeCenter >> moeTime >> b.upperMoeSpeed >> b.lowerMoeSpeed;
        b.moeCenter--;
        b.upperMoeSpeed += moeTime;
        b.lowerMoeSpeed += moeTime;

        sim(b, els);

    }


    return 0;
}
