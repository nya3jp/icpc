/*
 * UVA 10440 Ferry Loading II
 * 2005-08-19
 * by nya
 */

#define NDEBUG

#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <queue>
#include <cassert>

template<class T>
struct reverse_priority_queue : public std::priority_queue<T, std::vector<T>, std::greater<T> > {
};

struct Event {
    int iTime;
    int nFinishes;
    int nTravels;

    Event(int iTime=0, int nFinishes=0, int nTravels=0)
        : iTime(iTime), nFinishes(nFinishes), nTravels(nTravels) {
    }
};

bool operator>(const Event& a, const Event& b) {
    if (a.iTime != b.iTime)
        return (a.iTime > b.iTime);
    return (a.nTravels > b.nTravels);
}

int main() {

    int nCases;
    std::cin >> nCases;
    for(int iCase=0; iCase<nCases; iCase++) {

        int nCapacity, nCost, nCars;
        std::cin >> nCapacity >> nCost >> nCars;

        std::vector<int> schedule(nCars);
        for(int i=0; i<nCars; i++)
            std::cin >> schedule[i];

        Event answer;
        {
            std::vector<Event> costs(nCars+1, Event(-1, -1, -1));
            reverse_priority_queue<Event> q;
            q.push(Event(0, 0, 0));

            while(! q.empty()) {
                const Event e = q.top();
                q.pop();

                int nFinishes = e.nFinishes;
                if (costs[nFinishes].nFinishes < 0) {
#ifndef NDEBUG
                    std::fprintf(stderr,
                                 "Event: fin=%d tim=%d trv=%d\n", e.nFinishes, e.iTime, e.nTravels);
#endif
                    costs[nFinishes] = e;
                    for(int n=1; n<=nCapacity && nFinishes+n <= nCars; n++) {
                        int departure = std::max(e.iTime, schedule[nFinishes+n-1]);
                        q.push( Event(departure+nCost*2, nFinishes+n, e.nTravels+1) );
                    }
                    if (nFinishes == nCars)
                        break;
                }
            }
            assert(costs[nCars].nFinishes == nCars);
            answer = costs[nCars];
        }

        std::cout << (answer.iTime - nCost) << ' ' << answer.nTravels << std::endl;
    }
    return 0;
}
