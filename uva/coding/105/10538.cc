#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <string>
#include <stack>
#include <fstream>

using namespace std;

inline bool in_range(int x, int a, int b) { return (a <= x && x < b); }

struct Solver {

    static const int C = 25;
    static const int S = 20;

    vector<int> cells;
    vector<int> nums;
    vector<int> sums;
    vector<bool> items;

    vector< vector<int> > c2s;
    vector< vector<int> > s2c;

    Solver() : cells(C, 0), nums(S, 0), sums(S, 0), items(C, false), c2s(C), s2c(S) {
        //// make constraints
        // - horz
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                int id = i*5+j;
                c2s[id].push_back(i);
                s2c[i].push_back(id);
            }
        }
        // | vert
        for(int j = 0; j < 5; j++) {
            for(int i = 0; i < 5; i++) {
                int id = i*5+j;
                c2s[id].push_back(5+j);
                s2c[5+j].push_back(id);
            }
        }
        // \ diag
        for(int k = 0; k < 5; k++) {
            for(int i = 0; i < 5; i++) {
                int j = (i+k)%5;
                int id = i*5+j;
                c2s[id].push_back(10+k);
                s2c[10+k].push_back(id);
            }
        }
        // / diag
        for(int k = 0; k < 5; k++) {
            for(int i = 0; i < 5; i++) {
                int j = (5-i+k)%5;
                int id = i*5+j;
                c2s[id].push_back(15+k);
                s2c[15+k].push_back(id);
            }
        }
    }

    struct Bad {const char* s; Bad(const char* s):s(s){}};
    typedef stack< pair<int, int> > Record;

    void fill(int id, int item, Record& r) {
        //printf("Filling (%d,%d) with %d\n", id/5, id%5, item);
        if (!in_range(item, 1, C+1) || items[item-1])
            throw Bad("miss filling");
        {
            vector<int>& ss = c2s[id];
            for(int i = 0; i < (int)ss.size(); i++) {
                nums[ss[i]]++;
                sums[ss[i]]+=item;
            }
        }
        cells[id] = item;
        items[item-1] = true;
        r.push(make_pair(id, item));
        //printf("Filled (%d,%d) with %d\n", id/5, id%5, item);
    }

    void recover(Record& r) {
        bool done = false;
        while(!r.empty()) {
            done = true;
            int id = r.top().first;
            int item = r.top().second;

            {
                vector<int>& ss = c2s[id];
                for(int i = 0; i < (int)ss.size(); i++) {
                    nums[ss[i]]--;
                    sums[ss[i]]-=item;
                }
            }
            cells[id] = 0;
            items[item-1] = false;

            r.pop();
            //printf("Removed (%d,%d) with %d\n", id/5, id%5, item);
        }
        /*
        if (done) {
            char buf[64];
            fgets(buf, sizeof(buf), stdin);
        }
        */
    }

    int search() {
        int res = 0;
        Record r;

        //printf("new depth\n");

        try {
            bool ok;
            do {
                ok = true;
                for(int i = 0; i < S; i++) {
                    if (sums[i] > 65)
                        throw Bad("over sum");
                    if (nums[i] == 5) {
                        if (sums[i] != 65)
                            throw Bad("incorrect sum");
                    }
                    if (nums[i] == 4) {
                        int next = 65 - sums[i];
                        vector<int>& cc = s2c[i];
                        for(int j = 0; j < (int)cc.size(); j++) {
                            if (cells[cc[j]] == 0) {
                                fill(cc[j], next, r);
                                ok = false;
                                break;
                            }
                        }
                    }
                }
            } while(!ok);

            vector< pair<int,int> > cands;
            for(int i = 0; i < C; i++) {
                if (cells[i] == 0) {
                    int prio = 0;
                    vector<int>& ss = c2s[i];
                    for(int j = 0; j < (int)ss.size(); j++) {
                        prio += nums[ss[j]];
                    }
                    cands.push_back(make_pair(prio, i));
                }
            }
            if (cands.empty()) {
                //printf("Found\n");
                res = 1;
            }
            else {
                sort(cands.begin(), cands.end());
                int id = cands.back().second;
                for(int item = 1; item <= C; item++) {
                    if (!items[item-1]) {
                        Record r2;
                        try {
                            fill(id, item, r2);
                            res += search();
                        }
                        catch(Bad e) {
                            //printf("%s\n", e.s);
                        }
                        recover(r2);
                    }
                }
            }
        }
        catch(Bad e) {
            //printf("%s\n", e.s);
        }
        recover(r);
        return res;
    }

    int solve(const vector<int>& _cells) {
        cells = _cells;
        nums.assign(S, 0);
        sums.assign(S, 0);
        items.assign(C, false);
        for(int i = 0; i < C; i++) {
            if (cells[i] != 0) {
                items[cells[i]-1] = true;
                vector<int>& ss = c2s[i];
                for(int j = 0; j < (int)ss.size(); j++) {
                    nums[ss[j]]++;
                    sums[ss[j]]+=cells[i];
                }
            }
        }
        return search();
    }
};


int main() {
    //ifstream fin("10538.in");
    int nCases;
    cin >> nCases;
    for(int iCase = 0; iCase < nCases; iCase++) {
        vector<int> cells(25);
        for(int i = 0; i < 25; i++) {
            string s;
            cin >> s;
            if (s == "--") {
                cells[i] = 0;
            }
            else {
                istringstream is(s);
                is >> cells[i];
            }
        }
        Solver solver;
        cout << "Case " << iCase+1 << ": " << solver.solve(cells) << endl;
    }
    return 0;
}

