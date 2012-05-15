#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <utility>
#include <cassert>

using namespace std;


const int TRANSITS[8][24] = {
    {2,1,6,3,4,5,11,7,8,9,10,15,12,13,14,20,16,17,18,19,22,21,0,23},
    {0,3,2,8,4,5,6,7,12,9,10,11,17,13,14,15,16,21,18,19,20,23,22,1},
    {0,1,2,3,10,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,19,13,14,15,16,17,18,20,21,22,23},
    {0,23,2,1,4,5,6,7,3,9,10,11,8,13,14,15,16,12,18,19,20,17,22,21},
    {22,1,0,3,4,5,2,7,8,9,10,6,12,13,14,11,16,17,18,19,15,21,20,23},
    {0,1,2,3,4,5,6,7,8,9,10,11,12,14,15,16,17,18,19,13,20,21,22,23},
    {0,1,2,3,5,6,7,8,9,10,4,11,12,13,14,15,16,17,18,19,20,21,22,23},
};
const int INVERT_TRANSITS[8] = {5, 4, 7, 6, 1, 0, 3, 2};

inline int transit(int s, int k) {
    int t = 0;
    for(int i = 0; i < 24; i++) {
        t |= ((s >> TRANSITS[k][i]) & 1) << i;
    }
    t |= s & ~((1<<24)-1);
    return t;
}

bool my_less(const pair<string,int>& a, const pair<string,int>& b) {
    if (a.first.size() != b.first.size())
        return (a.first.size() < b.first.size());
    return (a < b);
}


pair<string,int> solve(int* init_s) {
    const int ACCEPTED = 0x0399c0;
    const int MASK = (1<<24)-1;
    vector<char> trace((1<<24)*3, -1);
    queue<int> q;
    for(int i = 0; i < 3; i++) {
        trace[init_s[i]] = 9;
        q.push(init_s[i]);
    }
    vector<int> accepts;
    while(!q.empty()) {
        int s = q.front();
        q.pop();
        if ((s&MASK) == ACCEPTED) {
            accepts.push_back(s);
        }
        if (accepts.empty()) {
            for(int k = 0; k < 8; k++) {
                int t = transit(s, k);
                if (trace[t] < 0) {
                    trace[t] = k;
                    q.push(t);
                }
            }
        }
    }
    vector<pair<string,int> > routes;
    for(int i = 0; i < (int)accepts.size(); i++) {
        vector<char> route;
        for(int s = accepts[i]; trace[s] != 9; s = transit(s, INVERT_TRANSITS[(int)trace[s]])) {
            assert(trace[s] >= 0);
            route.push_back('A' + trace[s]);
        }
        reverse(route.begin(), route.end());
        routes.push_back(make_pair(string(route.begin(), route.end()), accepts[i]>>24));
    }
    sort(routes.begin(), routes.end(), my_less);
    return routes[0];
}


int main() {

    if (false){
        int s = 0x5ab43b;
        for(int i = 0; i < 8; i++) {
            cout << "i = " << i << endl;
            assert(transit(transit(s, i), INVERT_TRANSITS[i]) == s);
        }
    }


    while(true) {

        int init_state[24];
        for(int i = 0; i < 24; i++) {
            cin >> init_state[i];
        }
        if (init_state[0] == 0)
            break;

        int init_s[3] = {0,0x1000000,0x2000000};
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 24; j++) {
                if (init_state[j] == i+1)
                    init_s[i] |= 1 << j;
            }
        }
        pair<string,int> solution;
        solution = solve(init_s);
        if (solution.first.empty())
            cout << "No moves needed" << endl;
        else
            cout << solution.first << endl;
        cout << solution.second+1 << endl;

    }
    return 0;
}
