/*
 * UVA 10423 - Peter Takes a Tramway
 * 2005-07-16
 * by nya
 */

#include <cstdio>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

int main() {

    int iCase = 0;
    int nTrams;
    while(std::scanf("%d", &nTrams) == 1 && nTrams != 0) {

        std::vector< std::pair<int, std::string> > schedule;

        for(int i=0; i<nTrams; i++) {

            char buf[64];
            std::scanf(" %[^:]:", buf);
            std::string name(buf);

            int time;
            while(std::scanf("%d", &time), time >= 0) {
                schedule.push_back( std::make_pair(time, name) );
            }
        }

        std::sort(schedule.begin(), schedule.end());

        int inittime, n;
        std::scanf("%d%d", &inittime, &n);
        
        std::vector< std::pair<int, std::string> >::iterator it = std::upper_bound(schedule.begin(), schedule.end(), std::make_pair(inittime, std::string()));
        if (it == schedule.end())
            it = schedule.begin();

        int initid = it - schedule.begin();
        int lastid = (initid + n-1)%schedule.size();

        std::printf("Case %d: Peter arrives at stop %d by tram %s.\n",
                    ++iCase,
                    n,
                    schedule[lastid].second.c_str());

    }

    return 0;
}
