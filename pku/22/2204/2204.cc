#include <iostream>
#include <vector>
#include <limits>
#include <cstdio>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

const int INF = numeric_limits<int>::max();



int main() {

    int len;
    cin >> len;

    int nPassengers;
    cin >> nPassengers;
    vector<int> passengers(nPassengers);
    REP(i, nPassengers)
        cin >> passengers[i];

    int nDoors;
    cin >> nDoors;
    vector<int> doors(nDoors, 0);
    REP(i, nDoors-1)
        cin >> doors[i+1];

    len *= 2;
    REP(i, nPassengers)
        passengers[i] *= 2;
    REP(i, nDoors)
        doors[i] *= 2;

    vector<int> nearestDoors(nPassengers);
    REP(i, nPassengers) {
        int dist = INF;
        int iDoor;
        REP(j, nDoors) {
            int d = abs(passengers[i] - doors[j]);
            if (d < dist) {
                dist = d;
                iDoor = j;
            }
        }
        nearestDoors[i] = iDoor;
    }

    int res_sum = -1;
    int res_pos = -1;
    while(doors.back() <= len) {

        int sum = 0;
        REP(i, nPassengers)
            sum += abs(doors[nearestDoors[i]] - passengers[i]);
        if (sum > res_sum) {
            res_sum = sum;
            res_pos = doors.front();
        }

        REP(i, nDoors)
            doors[i]++;
        REP(i, nPassengers) {
            int& k = nearestDoors[i];
            while(k > 0 && abs(doors[k-1] - passengers[i]) <= abs(doors[k] - passengers[i]))
                k--;
        }
    }

    printf("%.1f %.1f\n", res_pos / 2.0, res_sum / 2.0);

    return 0;
}
