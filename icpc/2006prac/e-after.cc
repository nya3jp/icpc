#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;


inline double sgn(double a) {
    return (a == 0 ? 0 : a > 0 ? 1 : -1);
}


struct Elevator {
    double pos;
    int contents;
    double workUntil;
    int destFloor;
    
    int capacity;
    double speed;
    double workTime;
};


struct DataCenter {

    int nFloors, nElevators;
    double floorHeight;
    vector<double> fireTimes;
    vector<bool> fired;

    vector<Elevator> elevators;
    vector<int> devices;
    double currentTime;

    double lastRescueTime;
    int rescuedDevices;

    enum EventType {
        HALT,
        ELEVATOR_ARRIVE,
        ELEVATOR_FINISH,
        BURNOUT_FLOOR
    };

    struct Event {
        double time;
        EventType type;
        int index;

        Event() {
        }
        Event(double time, EventType type, int index) : time(time), type(type), index(index) {
        }
        friend bool operator<(const Event& a, const Event& b) {
            return (a.time < b.time);
        }
    };

    static const double INF = 1.0e100;

    DataCenter(int nFloors, int nElevators, double floorHeight,
               const vector<Elevator>& elevators, const vector<int>& devices,
               int iFireCenterFloor, double burnoutTime, double upFireTime, double downFireTime) :
        nFloors(nFloors), nElevators(nElevators), floorHeight(floorHeight),
        fireTimes(nFloors), fired(nFloors, false), elevators(elevators), devices(devices), currentTime(0),
        lastRescueTime(0), rescuedDevices(0)
    {

        for(int i = 0; i < iFireCenterFloor; i++)
            fireTimes[i] = downFireTime * (iFireCenterFloor - i) + burnoutTime;
        for(int i = iFireCenterFloor; i < nFloors; i++)
            fireTimes[i] = upFireTime * (i - iFireCenterFloor) + burnoutTime;

        rescuedDevices += this->devices[0];
        this->devices[0] = 0;

    }


    void redetermine_action() {

        int iTargetFloor;
        for(iTargetFloor = nFloors-1; iTargetFloor > 0; iTargetFloor--)
            if (devices[iTargetFloor] > 0)
                break;

        for(int i = 0; i < nElevators; i++) {
            Elevator& e = elevators[i];
            if (e.workUntil < 0) {
                if (e.contents < e.capacity) {
                    if (iTargetFloor == 0 && e.contents == 0) {
                        e.workUntil = INF;
                    }
                    else {
                        e.destFloor = iTargetFloor;
                    }
                }
                else {
                    e.destFloor = 0;
                }
            }
        }
    }

    Event determine_next_event() {

        Event event;
        event.type = HALT;
        event.time = INF/2;

        for(int i = 0; i < nElevators; i++) {
            Elevator& e = elevators[i];
            if (e.workUntil < 0) {
                event = min(event,
                            Event(currentTime + abs(e.destFloor*floorHeight - e.pos) / e.speed,
                                  ELEVATOR_ARRIVE, i));
            }
            else {
                event = min(event,
                            Event(e.workUntil,
                                  ELEVATOR_FINISH, i));
            }
        }

        for(int i = 0; i < nFloors; i++)
            if (!fired[i])
                event = min(event,
                            Event(fireTimes[i],
                                  BURNOUT_FLOOR, i));

        return event;
    }


    void elapse(double nextTime) {

        double dt = nextTime - currentTime;

        for(int i = 0; i < nElevators; i++) {
            Elevator& e = elevators[i];
            if (e.workUntil < 0)
                e.pos += sgn(e.destFloor*floorHeight - e.pos) * e.speed * dt;
        }

        currentTime = nextTime;
    }



    void elevator_arrive(int iElevator) {

        Elevator& e = elevators[iElevator];

        if (e.destFloor == 0) {
            //cout << "elevator " << iElevator << " rescued " << e.contents << " devices." << endl;
            if (e.contents > 0) {
                rescuedDevices += e.contents;
                lastRescueTime = max(lastRescueTime, currentTime + e.workTime);
                e.contents = 0;
            }
        }
        else {
            int rescueDevices = min(e.capacity-e.contents, devices[e.destFloor]);
            e.contents += rescueDevices;
            devices[e.destFloor] -= rescueDevices;
            //cout << "elevator " << iElevator << " got " << rescueDevices << " devices at floor " << e.destFloor << "." << endl;
        }

        e.workUntil = currentTime + e.workTime;

    }

    void elevator_finish(int iElevator) {

        Elevator& e = elevators[iElevator];

        e.workUntil = -1;

        //cout << "elevator " << iElevator << " working finished." << endl;
    }

    void burnout_floor(int iFloor) {

        //cout << "floor " << iFloor << " burnt out, " << devices[iFloor] << " devices lost." << endl;

        devices[iFloor] = 0;
        fired[iFloor] = true;

    }


    void simulation() {
        
        while(true) {

            redetermine_action();

            Event event = determine_next_event();

            //cout << "> Next event: " << event.type << " [" << event.index << "] at " << setprecision(10) << event.time << endl;

            if (event.type == HALT)
                break;

            elapse(event.time);

            if (event.type == ELEVATOR_ARRIVE) {
                elevator_arrive(event.index);
            }
            else if (event.type == ELEVATOR_FINISH) {
                elevator_finish(event.index);
            }
            else if (event.type == BURNOUT_FLOOR) {
                burnout_floor(event.index);
            }

        }

        printf("%d %.6f\n", rescuedDevices, lastRescueTime);

    }

};



int main() {

    for(int nFloors, nElevators; cin >> nFloors >> nElevators && !(nFloors == 0 && nElevators == 0); ) {

        double floorHeight;
        cin >> floorHeight;

        vector<int> devices(nFloors);
        for(int i = 0; i < nFloors; i++)
            cin >> devices[i];

        vector<Elevator> elevators(nElevators);
        for(int i = 0; i < nElevators; i++) {
            Elevator& e = elevators[i];
            int floor;

            e.contents = 0;
            e.workUntil = -1;
            cin >> e.capacity >> e.speed >> e.workTime >> floor;
            e.pos = (floor-1) * floorHeight;
        }

        int iFireCenterFloor;
        double burnoutTime, upFireTime, downFireTime;
        cin >> iFireCenterFloor >> burnoutTime >> upFireTime >> downFireTime;
        iFireCenterFloor--;

        DataCenter dataCenter(nFloors, nElevators, floorHeight,
                              elevators, devices,
                              iFireCenterFloor, burnoutTime, upFireTime, downFireTime);

        dataCenter.simulation();

    }



    return 0;
}

