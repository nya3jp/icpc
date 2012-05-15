/*
 * UVA 10511 Councilling
 * 2005-09-27
 * by nya
 */

#define NDEBUG
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <queue>
#include <utility>
#include <exception>
#include <cstdio>
#include <cassert>


#define INF 0x7fffffff

#define nassert(x) if (x); else *(int*)1 = 0

/*
template<class T>
struct Matrix : public std::vector< std::vector<T> > {
    Matrix(int n, const T& def = T())
        : std::vector< std::vector<T> >(n, std::vector<T>(n, def)) {
    }
};
*/

template<class T>
struct Matrix {
    const int n;
    T* data;
    Matrix(int n) : n(n) {
        data = new T[n*n];
    }
    ~Matrix() {
        delete[] data;
    }
    inline T* operator[](int i) {
        return data+i*n;
    }
    inline const T* operator[](int i) const {
        return data+i*n;
    }
    inline int size() const {
        return n;
    }
};

struct Edge {
    int size, flow;
    Edge() : size(0), flow(0) {}
};

struct FF {
    int id, prev, inc, dist;
    FF(int id=-1, int prev=-1, int inc=0, int dist=INF)
        : id(id), prev(prev), inc(inc), dist(dist) {
    }
    friend bool operator<(const FF& a, const FF& b) {
        if (a.dist != b.dist)
            return (a.dist > b.dist);
        return (a.inc < b.inc);
    }
};

typedef Matrix<Edge> Network;

inline int abs(int n) {
    return (n < 0 ? -n : n);
}

struct FordFulkerson_greedy_dfs_search_found {};

void FordFulkerson_greedy_dfs_search_rec(const Network& net, /*std::vector<FF>&*/FF* ff, int iNode, int iSink) {
    int n = net.size();
    ff[iNode].dist = iNode;
    if (iNode == iSink)
        throw FordFulkerson_greedy_dfs_search_found();
    for(int i=iNode+1; i<n; i++) {
        assert(net[iNode][i].size >= 0);
        if (ff[i].dist < 0 && net[iNode][i].flow < net[iNode][i].size) {
            ff[i].prev = iNode;
            FordFulkerson_greedy_dfs_search_rec(net, ff, i, iSink);
        }
    }
}

bool FordFulkerson_greedy_dfs_search(const Network& net, /*std::vector<FF>&*/FF* ff, int iSource, int iSink) {
    int n = net.size();

    for(int i=0; i<n; i++) {
        ff[i].prev = -1;
        ff[i].dist = -1;
    }

    try {
        FordFulkerson_greedy_dfs_search_rec(net, ff, iSource, iSink);
    } catch(...) {}

    ff[iSink].inc = (ff[iSink].dist >= 0 ? 1 : 0);
    return (ff[iSink].inc != 0);
}

bool FordFulkerson_bfs_search(const Network& net, /*std::vector<FF>&*/FF* ff, int iSource, int iSink) {
    int n = net.size();

    for(int i=0; i<n; i++)
        ff[i] = FF(i);

    std::priority_queue<FF> q;
    q.push( FF(iSource, -1, INF, 0) );
    while(! q.empty()) {
        FF f = q.top();
        q.pop();
        int id = f.id;
        if (ff[id].dist == INF) {
            ff[id] = f;
#ifndef NDEBUG
            std::printf("Node %d: dist=%d, prev=%d, inc=%d\n", id, f.dist, f.prev, f.inc);
#endif
            if (id == iSink)
                break;
            for(int i=0; i<n; i++) {
                if (net[id][i].size != 0 && ff[i].dist == INF) {
                    int inc = std::min(f.inc,
                                       (net[id][i].size > 0 ? net[id][i].size : 0)
                                       - net[id][i].flow );
                    if (inc > 0) {
                        q.push( FF(i,
                                   id,
                                   inc,
                                   f.dist+1) );
                    }
                }
            }
        }
    }
    return (ff[iSink].inc != 0);
}

void FordFulkerson(Network& net, int iSource, int iSink) {
    int n = net.size();

    //std::vector<FF> ff(n);
    FF* ff = new FF[n];
    while(true) {
        if (!FordFulkerson_greedy_dfs_search(net, ff, iSource, iSink)
            && !FordFulkerson_bfs_search(net, ff, iSource, iSink))
            break;
        int inc = ff[iSink].inc;
        for(int j = iSink; ff[j].prev >= 0; j = ff[j].prev) {
            int i = ff[j].prev;
#ifndef NDEBUG
            std::printf(" FF: %d -> %d, inc = %d\n", i, j, inc);
#endif
            assert(inc == 1);
            net[i][j].flow += inc;
            net[j][i].flow = -net[i][j].flow;
            assert(abs(net[i][j].flow) <= abs(net[i][j].size));
            assert(net[i][j].flow*net[i][j].size >= 0);
        }
    }
    delete[] ff;
}


template<class T>
T lexical_cast(const std::string& s) {
    std::istringstream is(s);
    T t;
    is >> t;
    /*
    if (! is)
        throw std::bad_cast();
    */
    return t;
}



struct Resident {
    std::string name;
    int iParty;
    std::vector<int> clubs;
};

int main() {
    std::string line;

    std::getline(std::cin, line);
    int nCases = lexical_cast<int>(line);
    std::getline(std::cin, line);

    for(int iCase=0; iCase<nCases; iCase++) {

        std::vector<Resident> residents;
        std::vector<std::string> clubs;
        std::vector<std::string> parties;

#ifndef NDEBUG
        std::printf("Reading input...\n");
#endif

        {
            std::map<std::string, int> clubids;
            std::map<std::string, int> partyids;

            while(std::getline(std::cin, line) && !line.empty()) {
                std::istringstream is(line);
                std::string resident, party;
                is >> resident >> party;
                residents.push_back(Resident());
                partyids.insert( std::make_pair(party, partyids.size()) );
                int iResident = residents.size() - 1;
                int iParty = partyids[party];
                residents[iResident].name = resident;
                residents[iResident].iParty = iParty;
                for(std::string s; is >> s; ) {
                    clubids.insert( std::make_pair(s, clubids.size()) );
                    int iClub = clubids[s];
                    residents[iResident].clubs.push_back(iClub);
                }
            }

            clubs.resize(clubids.size());
            parties.resize(partyids.size());
            for(std::map<std::string,int>::const_iterator it = clubids.begin(); it != clubids.end(); ++it) {
                clubs[it->second] = it->first;
            }
            for(std::map<std::string,int>::const_iterator it = partyids.begin(); it != partyids.end(); ++it) {
                parties[it->second] = it->first;
            }
        }

        int nResidents = residents.size();
        int nClubs = clubs.size();
        int nParties = parties.size();

        std::vector< std::vector<int> > clubmembers(nClubs);
        for(int i=0; i<nResidents; i++) {
            const Resident& r = residents[i];
            for(int j=0; j<(int)r.clubs.size(); j++) {
                clubmembers[r.clubs[j]].push_back(i);
            }
        }

#ifndef NDEBUG
        std::printf("Constructing a graph...\n");
#endif

        Network net(1 + nClubs + nResidents + nParties + 1);

        // source to clubs, clubs to residents
        for(int iClub=0; iClub<nClubs; iClub++) {
            int i = 1+iClub;
            net[0][i].size = 1;
            net[i][0].size = -1;
            const std::vector<int>& members = clubmembers[iClub];
            for(int iMember=0; iMember<(int)members.size(); iMember++) {
                int iResident = members[iMember];
                int j = 1+nClubs+iResident;
                net[i][j].size = 1;
                net[j][i].size = -1;
            }
        }

        // residents to party
        for(int iResident=0; iResident<nResidents; iResident++) {
            int i = 1+nClubs+iResident;
            int iParty = residents[iResident].iParty;
            int j = 1+nClubs+nResidents+iParty;
            net[i][j].size = 1;
            net[j][i].size = -1;
        }

        // party to sink
        {
            int iSink = 1+nClubs+nResidents+nParties;
            int iCouncilLimit = (nClubs-1)/2;
            for(int iParty=0; iParty<nParties; iParty++) {
                int i = 1+nClubs+nResidents+iParty;
                net[i][iSink].size = iCouncilLimit;
                net[iSink][i].size = -iCouncilLimit;
            }
        }

#ifndef NDEBUG
        std::printf("Executing Ford-Fulkerson method...\n");
#endif

        FordFulkerson(net, 0, 1+nClubs+nResidents+nParties);

        if (iCase > 0)
            std::cout << std::endl;

        std::vector<int> representives(nClubs);

        for(int iClub=0; iClub<nClubs; iClub++) {

#ifndef NDEBUG
            std::printf("Club %s:\n", clubs[iClub].c_str());
#endif

            int iResident;
            for(iResident=nResidents-1; iResident>=0; iResident--) {
                int i = 1+iClub;
                int j = 1+nClubs+iResident;
                if (net[i][j].flow > 0)
                    break;
            }
            representives[iClub] = iResident;

#ifndef NDEBUG
            if (iResident < 0) {
                std::printf(" No representive.\n");
            }
            else {
                int iParty = residents[iResident].iParty;
                std::printf(" Representive: %s, belongs to %s\n",
                            residents[iResident].name.c_str(), parties[iParty].c_str());
                assert(net[1+nClubs+iResident][1+nClubs+nResidents+iParty].flow > 0);
            }
#endif
        }


        if (*std::min_element(representives.begin(), representives.end()) < 0) {
            std::printf("Impossible.\n");
        }
        else {
#ifndef NDEBUG
            {
                std::vector<int> v(nParties);
                for(int i=0; i<nClubs; i++) {
                    v[ residents[ representives[i] ].iParty ]++;
                }
                assert(*std::max_element(v.begin(), v.end())*2 < nClubs);
            }
#endif
            for(int iClub=0; iClub<nClubs; iClub++) {
                std::printf("%s %s\n",
                            residents[representives[iClub]].name.c_str(),
                            clubs[iClub].c_str());
            }
        }

    }

    return 0;
}




