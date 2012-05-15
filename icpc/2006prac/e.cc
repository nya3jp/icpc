/*

TODO:

初期化

 */


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>

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
    int moeCenter, upperMoeSpeed, lowerMoeSpeed, moeTime;
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

    int totalRescue = 0;

    double lastTime = 0;
    double prevTime = 0;
    int n = els.size();

    totalRescue += building.devices[0];
    building.devices[0] = 0;

    refresh(building, els, 0);

    while(true) {

        vector<double> times(n+2);
        for(int i = 0; i < n; i++) {
            times[i] = els[i].nextEvent;
        }
        times[n] = building.upperMoeSpeed * (building.upperMoeStep+1) + building.moeTime;// next uppermoetuki
        times[n+1] = building.lowerMoeSpeed * (building.lowerMoeStep+1) + building.moeTime;// next lowermoetuki

        if (*min_element(times.begin(), times.begin()+n) > 1.0e100)
            break;

        int iNextEvent = min_element(times.begin(), times.end()) - times.begin();

        double currentTime = times[iNextEvent];

        for(int i = 0; i < n; i++) {
            El& e = els[i];
            if (!e.working) {
                if (building.floorInterval*e.dest > e.pos) {
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
            if (building.moeCenter+building.upperMoeStep < (int)building.devices.size())
                building.devices[building.moeCenter+building.upperMoeStep] = 0;
            cout << currentTime << " floor " << (building.moeCenter+building.upperMoeStep) << " moetuki" << endl;
            // uppermoetuki
        }
        else if (iNextEvent == n+1) {
            building.lowerMoeStep++;
            if (building.moeCenter-building.lowerMoeStep >= 0)
                building.devices[building.moeCenter-building.lowerMoeStep] = 0;
            cout << currentTime << " floor " << (building.moeCenter-building.lowerMoeStep) << " moetuki" << endl;
            // lowermoetuki
        }
        else {
            El& e = els[iNextEvent];
            if (e.working) {
                cout << currentTime << " elevator " << iNextEvent << " working finished" << endl;
                e.working = false;
            }
            else {
                if (e.dest == 0) {
                    // rescued
                    cout << currentTime << " elevator " << iNextEvent << " rescued " << e.bag << endl;
                    totalRescue += e.bag;
                    e.bag = 0;
                    e.working = true;
                    e.nextEvent += e.wait;
                    lastTime = e.nextEvent;
                }
                else {
                    int getdevices = min(building.devices[e.dest], e.capacity-e.bag);
                    cout << currentTime << " elevator " << iNextEvent << " getting " << getdevices << " at " << e.dest << endl;
                    building.devices[e.dest] -= getdevices;
                    e.bag += getdevices;
                    e.working = true;
                    e.nextEvent += e.wait;
                }
            }
        }

        refresh(building, els, currentTime);

        prevTime = currentTime;

    }

    printf("%d %.3f\n", totalRescue, lastTime);

}



int main() {

    while(true) {

        int nFloors, nElevators, floorInterval;

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

        cin >> b.moeCenter >> b.moeTime >> b.upperMoeSpeed >> b.lowerMoeSpeed;
        b.moeCenter--;
        b.upperMoeSpeed += b.moeTime;
        b.lowerMoeSpeed += b.moeTime;

        sim(els, b);

    }


    return 0;
}
