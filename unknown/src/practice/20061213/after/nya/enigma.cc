#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

typedef vector<char*> Slot;

int w, h;
vector< vector<char> > field;
vector<string> dict;
vector<bool> used;
vector<Slot> slots;
int nSlots;
int nWords;

void reorder() {
    int n = nWords;
    map<char*, int> col;
    vector< vector<int> > adj(n);
    REP(iSlot, n) {
        Slot& slot = slots[iSlot];
        REP(i, slot.size()) {
            char* p = slot[i];
            if (col.count(p) == 0) {
                col[p] = iSlot;
            }
            else {
                int jSlot = col[p];
                adj[iSlot].push_back(jSlot);
                adj[jSlot].push_back(iSlot);
            }
        }
    }
    vector<Slot> newslots;
    vector<bool> visited(n, false);
    vector<int> stack;
    REP(i, n)
        stack.push_back(i);
    while(!stack.empty()) {
        int iSlot = stack.back();
        stack.pop_back();
        if (visited[iSlot])
            continue;
        visited[iSlot] = true;
        newslots.push_back(slots[iSlot]);
        REP(i, adj[iSlot].size())
            stack.push_back(adj[iSlot][i]);
    }
    assert(newslots.size() == n);
    slots = newslots;
}

bool search(int iSlot) {
    if (iSlot == nSlots) {
        return true;
    }
    Slot& slot = slots[iSlot];
    REP(iWord, nWords) {
        string& word = dict[iWord];
        if (!used[iWord] && word.size() == slot.size()) {
            int len = word.size();
            bool ok = true;
            vector<char> backup;
            REP(i, len) {
                char* p = slot[i];
                backup.push_back(*p);
                if (*p != '#' && *p != word[i])
                    ok = false;
                *p = word[i];
            }
            if (ok) {
                used[iWord] = true;
                if (search(iSlot+1))
                    return true;
                used[iWord] = false;
            }
            REP(i, len)
                *slot[i] = backup[i];
        }
    }
    return false;
}

bool solve() {

    cin >> w >> h;
    field.clear();
    REP(i, h) {
        string row;
        cin >> row;
        field.push_back(vector<char>(ALLOF(row)));
    }

    cin >> nWords;
    dict.resize(nWords);
    REP(i, nWords)
        cin >> dict[i];

    slots.clear();
    REP(i, h) REP(j, w) {
        if (field[i][j] != '.' && (i == 0 || field[i-1][j] == '.') && (i+1 < h && field[i+1][j] != '.')) {
            slots.push_back(Slot());
            Slot& slot = slots.back();
            for(int len = 0; i+len < h && field[i+len][j] != '.'; len++) {
                slot.push_back(&field[i+len][j]);
                field[i+len][j] = '*';
            }
        }
        if (field[i][j] != '.' && (j == 0 || field[i][j-1] == '.') && (j+1 < w && field[i][j+1] != '.')) {
            slots.push_back(Slot());
            Slot& slot = slots.back();
            for(int len = 0; j+len < w && field[i][j+len] != '.'; len++) {
                slot.push_back(&field[i][j+len]);
                field[i][j+len] = '*';
            }
        }
    }
    nSlots = slots.size();

    REP(i, h) {
        if (count(ALLOF(field[i]), '#') > 0) {
            /*
            printf("check1 at row %d\n", i);
            REP(i, h)
                cout << string(ALLOF(field[i])) << endl;
            */
            return false;
        }
        replace(ALLOF(field[i]), '*', '#');
    }

    {
        if (nWords != nSlots) {
            //printf("check2 words=%d slots=%d\n", nWords, nSlots);
            return false;
        }
        vector<int> lens1, lens2;
        REP(i, nWords) {
            lens1.push_back(dict[i].size());
            lens2.push_back(slots[i].size());
        }
        sort(ALLOF(lens1));
        sort(ALLOF(lens2));
        if (lens1 != lens2) {
            //printf("check3\n");
            return false;
        }
    }

    reorder();

    used.assign(nWords, false);
    return search(0);
}


int main() {
    int nCases;
    cin >> nCases;
    REP(iCase, nCases) {
        bool res = solve();
        cout << "Puzzle #" << iCase+1 << endl;
        if (res) {
            REP(i, h)
                cout << string(ALLOF(field[i])) << endl;
        }
        else {
            cout << "I cannot generate this puzzle." << endl;
        }
    }
    return 0;
}
