#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

typedef Car {
    int time, side;
};



void solve() {

    int nCapacity, crossTime, nCars;

    deque<Car> q;
    REP(i, nCars) {
        Car car;
        string sideStr;
        cin >> car.time >> sideStr;
        car.side = (sideStr == "left" ? 0 : 1);
        q.push_back(car);
    }

    vector<int> results(nCars);

    vector<int> loads;
    int arrivalTime = 0;
    int arrivalSide = 0;

    deque<int> waits[2];

    int iCar = 0;
    for(;;) {

        int currentTime = cars[iCar].time;

        while(currentTime >= arrivalTime) {
            REP(i, loads.size())
                results[i] = arrivalTime;
            loads.clear();
            deque<int>& hereWaits = waits[arrivalSide];
            deque<int>& thereWaits = waits[arrivalSide^1];
            if (!hereWaits.empty()) {
                while(loads.size() < nCapacity && !hereWaits.empty()) {
                    loads.push_back(hereWaits.front());
                    hereWaits.pop_front();
                }
                arrivalTime += crossTime;
                arrivalSide ^= 1;
            }
            else if (!thereWaits.empty()) {
                arrivalTime += crossTime;
                arrivalSide ^= 1;
            }
            else {
                break;
            }
        }

        if (iCar == nCars)
            break;

        for(; iCar < nCars && cars[iCar].time == currentTime; iCar++) {
            Car car = cars[iCar];
            waits[car.side].push_back(iCar);
        }

    }

}

