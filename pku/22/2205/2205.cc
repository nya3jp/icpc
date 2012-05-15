#include <iostream>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define N 2010

const char* REPR = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct state_t {
    int v[N];
    int c;
};

state_t* u = new state_t[1000];
state_t* v = new state_t[1000];
int un = 0, vn = 0;

int main() {

    int base, n;
    cin >> base >> n;

    /*
    vector<state_t> v, u;
    v.push_back((state_t){{}, 0});
    */
    v[0] = (state_t){{}, 0};
    vn = 1;

    REP(m, n) {
        //u.clear();
        un = 0;
        //const int vn = v.size();
        REP(i, vn) {
            u[un] = v[i];
            int part_sum = 0;
            for(int j = 1; j <= m-1; j++)
                part_sum += v[i].v[j] * v[i].v[m-j];
            REP(d, base) {
                //state_t s = v[i];
                state_t& s = u[un];
                s.v[m] = d;
                int sum = s.c + part_sum;
                /*
                REP(j, m+1)
                    sum += s.v[j] * s.v[m-j];
                */
                if (m == 0)
                    sum += s.v[0] * s.v[0];
                else
                    sum += 2 * s.v[0] * s.v[m];
                int c = sum / base;
                int r = sum % base;
                if (r == d) {
                    s.c = c;
                    //u.push_back(s);
                    un++;
                    u[un] = v[i];
                }
            }
        }
        //v.swap(u);
        swap(u, v);
        swap(un, vn);
    }

    vector<state_t> res;
    //const int vn = v.size();
    REP(i, vn) {
        state_t s = v[i];
        if (n == 1 || s.v[n-1] > 0)
            res.push_back(s);
    }

    cout << (int)res.size() << endl;
    REP(i, res.size()) {
        state_t s = res[i];
        REP(j, n)
            cout << REPR[s.v[n-1-j]];
        cout << endl;
    }

    return 0;
}
