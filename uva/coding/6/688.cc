#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdio>

using namespace std;

typedef pair<double,double> Pt;
typedef pair<double,double> Range;
typedef pair<double,int> Event;


struct Antenna {
    double x, y, r;
};

double calc_area(vector<Range>& ranges) {
    double sum = 0.0;
    int n = ranges.size();
    double right = -1.0e10;
    for(int i = 0; i < n; i++) {
        Range& r = ranges[i];
        if (r.second > right) {
            sum += r.second - max(right, r.first);
            right = r.second;
        }
    }
    return sum;
}


int main() {
    int n;
    int iCase = 0;
    while(cin >> n && n > 0) {

        vector<Antenna> antennas(n);
        vector<Range> aranges(n);
        for(int i = 0; i < n; i++) {
            Antenna& a = antennas[i];
            cin >> a.x >> a.y >> a.r;
            aranges[i] = Range(a.y-a.r, a.y+a.r);
        }

        vector<Event> events;
        for(int i = 0; i < n; i++) {
            Antenna& a = antennas[i];
            events.push_back(Event(a.x-a.r, i));
            events.push_back(Event(a.x+a.r, i));
        }

        sort(events.begin(), events.end());

        vector<Range> ranges;
        vector<bool> scanning(n, false);
        double area = 0.0;
        for(int i = 0; i < 2*n; i++) {
            Event& e = events[i];
            int id = e.second;
            if (i > 0) {
                double dx = events[i].first - events[i-1].first;
                double dy = calc_area(ranges);
                //printf("%d: %.2f * %.2f = %.2f\n", i, dx, dy, dx*dy);
                area += dx*dy;
            }
            if (scanning[id]) {
                //printf("removing id=%d\n", id);
                ranges.erase(
                    lower_bound(ranges.begin(),
                                ranges.end(),
                                aranges[id]));
                scanning[id] = false;
            }
            else {
                //printf("adding id=%d\n", id);
                ranges.insert(
                    lower_bound(ranges.begin(),
                                ranges.end(),
                                aranges[id]),
                    aranges[id]);
                scanning[id] = true;
            }
        }

        printf("%d %.2f\n", ++iCase, area);

    }
    return 0;
}
