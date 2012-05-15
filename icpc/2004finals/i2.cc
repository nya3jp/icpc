/*
 * 2004-2005 ICPC Finals Problem I "Workshops"
 *
 * by nya@qoo
 */


#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;


struct Node {
    int population, duration;
};
        
inline bool sortByPopulation(const Node& a, const Node& b) {
    return (a.population < b.population);
}
inline bool sortByDuration(const Node& a, const Node& b) {
    return (a.duration < b.duration);
}

int main() {

    int iCase = 0;
    while(true) {

        // Read a trial

        int nWorkshops;
        scanf("%d", &nWorkshops);
        if (nWorkshops == 0)
            break;

        vector<Node> workshops(nWorkshops);
        for(int i = 0; i < nWorkshops; i++)
            scanf("%d%d", &workshops[i].population, &workshops[i].duration);

        int nRooms;
        scanf("%d", &nRooms);

        vector<Node> rooms(nRooms);
        for(int i = 0; i < nRooms; i++) {
            int hh, mm;
            scanf("%d%d:%d", &rooms[i].population, &hh, &mm);
            rooms[i].duration = (hh-14)*60 + mm;
        }


        // sort workshops by population order,
        //      rooms     by duation    order.

        sort(workshops.begin(), workshops.end(), sortByPopulation);
        reverse(workshops.begin(), workshops.end());
        sort(rooms.begin(), rooms.end(), sortByDuration);


        // match workshops with rooms greedily

        const int UNMATCHED = -1;
        vector<int> workshop_matchings(nWorkshops, UNMATCHED);
        vector<int> room_matchings(nRooms, UNMATCHED);
        for(int i = 0; i < nWorkshops; i++) {
            const Node& workshop = workshops[i];
            for(int j = 0; j < nRooms; j++) {
                if (room_matchings[j] == UNMATCHED &&
                    workshop.population <= rooms[j].population &&
                    workshop.duration <= rooms[j].duration)
                {
                    workshop_matchings[i] = j;
                    room_matchings[j] = i;
                    break;
                }
            }
        }


        // accumulate results and output

        int nTentWorkshops = 0;
        int nTentParticipants = 0;
        for(int i = 0; i < nWorkshops; i++) {
            if (workshop_matchings[i] == UNMATCHED) {
                nTentWorkshops++;
                nTentParticipants += workshops[i].population;
            }
        }

        if (iCase > 0)
            printf("\n");
        printf("Trial %d:  %d %d\n", iCase+1, nTentWorkshops, nTentParticipants);

        iCase++;
    }
    return 0;
}

