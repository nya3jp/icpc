#include <iostream>
#include <queue>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

struct Event {
    enum Type {
        None,
        Green,
        Red,
        Trap,
    } type;
    int id, time;

    Event() : type(None) {}
    Event(Type type, int id, int time) : type(type), id(id), time(time) {}
};

bool operator>(const Event& a, const Event& b) {
    return (a.time > b.time);
}

int main() {
    while(true) {
        int n = 0;
        vector<int> v;
        for(int t; cin >> t && t != 0; n++)
            v.push_back(t);
        if (v.empty())
            break;

        priority_queue<Event, vector<Event>, greater<Event> > q;

        q.push(Event(Event::Trap, -1, 60*60*5+1));
        for(int i = 0; i < n; i++) {
            q.push(Event(Event::Red, i, v[i]-5));
        }

        int nGreens = n;
        int lasttime = -1;
        int synctime = -1;
        while(true) {
            Event e = q.top();
            q.pop();
            //cout << e.type << ", " << e.id << ", " << e.time << endl;
            if (e.time != lasttime) {
                if (lasttime != -1 && nGreens == n) {
                    synctime = lasttime;
                    break;
                }
                lasttime = e.time;
            }
            if (e.type == Event::Trap) {
                synctime = -1;
                break;
            }
            else if (e.type == Event::Green) {
                nGreens++;
                q.push(Event(Event::Red, e.id, e.time+v[e.id]-5));
            }
            else if (e.type == Event::Red) {
                nGreens--;
                q.push(Event(Event::Green, e.id, e.time+v[e.id]+5));
            }
        }

        if (synctime < 0) {
            printf("Signals fail to synchronise in 5 hours\n");
        }
        else {
            printf("%02d:%02d:%02d\n", synctime/60/60, synctime/60%60, synctime%60);
        }

    }

    return 0;
}

