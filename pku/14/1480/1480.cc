#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Program {

    int n;
    vector< vector<int> > st;
    vector<int> ref;
    vector<const char*> hist;

    Program(int n, vector<int>& init, vector<int>& ref) : n(n), ref(ref) {
        for(int i = 0; i < n; i++) {
            st.push_back(vector<int>(1, init[i]));
        }
    }

    int abs(int n) {
        return (n < 0 ? -n : n);
    }

    bool search(vector<string>& opr) {
        hist.clear();
        for(int limit = 0; limit <= 10; limit++) {
            if (search(0, limit)) {
                opr.clear();
                for(int i = 0; i < (int)hist.size(); i++)
                    opr.push_back(hist[i]);
                return true;
            }
        }
        return false;
    }

    bool add(int step, int limit) {
        if ((int)st[0].size() < 2)
            return false;
        vector<int> as(n), bs(n);
        for(int i = 0; i < n; i++) {
            as[i] = st[i].back(); st[i].pop_back();
            bs[i] = st[i].back(); st[i].pop_back();
            st[i].push_back(bs[i] + as[i]);
        }
        hist.push_back("ADD");
        if (search(step+1, limit))
            return true;
        hist.pop_back();
        for(int i = 0; i < n; i++) {
            st[i].pop_back();
            st[i].push_back(bs[i]);
            st[i].push_back(as[i]);
        }
        return false;
    }

    bool sub(int step, int limit) {
        if ((int)st[0].size() < 2)
            return false;
        vector<int> as(n), bs(n);
        for(int i = 0; i < n; i++) {
            as[i] = st[i].back(); st[i].pop_back();
            bs[i] = st[i].back(); st[i].pop_back();
            st[i].push_back(bs[i] - as[i]);
        }
        hist.push_back("SUB");
        if (search(step+1, limit))
            return true;
        hist.pop_back();
        for(int i = 0; i < n; i++) {
            st[i].pop_back();
            st[i].push_back(bs[i]);
            st[i].push_back(as[i]);
        }
        return false;
    }

    bool mul(int step, int limit) {
        if ((int)st[0].size() < 2)
            return false;
        vector<int> as(n), bs(n);
        for(int i = 0; i < n; i++) {
            as[i] = st[i].back(); st[i].pop_back();
            bs[i] = st[i].back(); st[i].pop_back();
            st[i].push_back(bs[i] * as[i]);
        }
        hist.push_back("MUL");
        if (search(step+1, limit))
            return true;
        hist.pop_back();
        for(int i = 0; i < n; i++) {
            st[i].pop_back();
            st[i].push_back(bs[i]);
            st[i].push_back(as[i]);
        }
        return false;
    }

    bool div(int step, int limit) {
        if ((int)st[0].size() < 2)
            return false;
        vector<int> as(n), bs(n);
        bool err = false;
        for(int i = 0; i < n; i++) {
            as[i] = st[i].back(); st[i].pop_back();
            bs[i] = st[i].back(); st[i].pop_back();
            if (as[i] == 0) {
                st[i].push_back(0);
                err = true;
            }
            else {
                st[i].push_back(bs[i] / as[i]);
            }
        }
        hist.push_back("DIV");
        if (!err && search(step+1, limit))
            return true;
        hist.pop_back();
        for(int i = 0; i < n; i++) {
            st[i].pop_back();
            st[i].push_back(bs[i]);
            st[i].push_back(as[i]);
        }
        return false;
    }

    bool dup(int step, int limit) {
        for(int i = 0; i < n; i++) {
            int a = st[i].back();
            st[i].push_back(a);
        }
        hist.push_back("DUP");
        if (search(step+1, limit))
            return true;
        hist.pop_back();
        for(int i = 0; i < n; i++) {
            st[i].pop_back();
        }
        return false;
    }

    bool search(int step, int limit) {

        int size = st[0].size();

        for(int i = 0; i < n; i++)
            if (st[i].back() > 30000)
                return false;

        if (size-1 > limit-step)
            return false;

        if (size == 1) {
            bool ok = true;
            for(int i = 0; i < n; i++)
                if (st[i][0] != ref[i])
                    ok = false;
            if (ok)
                return true;
        }

        if (limit == step)
            return false;

        if (add(step, limit))
            return true;
        if (div(step, limit))
            return true;
        if (dup(step, limit))
            return true;
        if (mul(step, limit))
            return true;
        if (sub(step, limit))
            return true;

        return false;
    }
};

int main() {

    int iCase = 0;
    int n;
    while(cin >> n && n > 0) {

        cout << "Program " << ++iCase << endl;

        vector<int> init(n), ref(n);
        for(int i = 0; i < n; i++)
            cin >> init[i];
        for(int i = 0; i < n; i++)
            cin >> ref[i];

        Program solver(n, init, ref);
        vector<string> opr;
        if (solver.search(opr)) {
            if (opr.empty()) {
                cout << "Empty sequence" << endl;
            }
            else {
                cout << opr[0];
                for(int i = 1; i < (int)opr.size(); i++) {
                    cout << ' ' << opr[i];
                }
                cout << endl;
            }
        }
        else {
            cout << "Impossible" << endl;
        }
        cout << endl;

    }

    return 0;
}
