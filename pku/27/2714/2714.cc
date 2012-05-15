#include <cstdio>
#include <vector>
#include <complex>
#include <algorithm>
#include <limits>

using namespace std;

#define PRUN 1

typedef complex<int> P;

const P INFTY(numeric_limits<int>::max(), numeric_limits<int>::max());

int main() {
    while(true) {
        int n;
        scanf("%d", &n);
        if (n == 0)
            break;
        vector<P> v(n);
        for(int i = 0; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            v[i] = P(x, y);
        }
        double result = 0;



        // 1
        {
            vector<P> u0, u1;
            u0.push_back(P(0, 0));
            for(int i = 0; i < n; i++) {
                u1.clear();
                for(int j = 0; j < (int)u0.size(); j++) {
                    u1.push_back(u0[j]-v[i]);
                    u1.push_back(u0[j]+v[i]);
                }
#if PRUN
                for(int j = 0; j < (int)u1.size(); j++) {
                    if (u1[j] != INFTY) {
                        for(int k = 0; k < (int)u1.size(); k++) {
                            if (k != j && u1[k] != INFTY && u1[k].real() <= u1[j].real() && u1[k].imag() <= u1[j].imag()) {
                                u1[k] = INFTY;
                            }
                        }
                    }
                }
#endif
                u0.clear();
                remove_copy(u1.begin(), u1.end(), back_inserter(u0), INFTY);
            }
            for(int i = 0; i < (int)u0.size(); i++) {
                complex<double> p(u0[i].real(), u0[i].imag());
                result = max(result, abs(p));
            }
        }



        // 2
        {
            vector<P> u0, u1;
            u0.push_back(P(0, 0));
            for(int i = 0; i < n; i++) {
                u1.clear();
                for(int j = 0; j < (int)u0.size(); j++) {
                    u1.push_back(u0[j]-v[i]);
                    u1.push_back(u0[j]+v[i]);
                }
#if PRUN
                for(int j = 0; j < (int)u1.size(); j++) {
                    if (u1[j] != INFTY) {
                        for(int k = 0; k < (int)u1.size(); k++) {
                            if (k != j && u1[k] != INFTY && u1[k].real() >= u1[j].real() && u1[k].imag() <= u1[j].imag()) {
                                u1[k] = INFTY;
                            }
                        }
                    }
                }
#endif
                u0.clear();
                remove_copy(u1.begin(), u1.end(), back_inserter(u0), INFTY);
            }
            for(int i = 0; i < (int)u0.size(); i++) {
                complex<double> p(u0[i].real(), u0[i].imag());
                result = max(result, abs(p));
            }
        }



        // 3
        {
            vector<P> u0, u1;
            u0.push_back(P(0, 0));
            for(int i = 0; i < n; i++) {
                u1.clear();
                for(int j = 0; j < (int)u0.size(); j++) {
                    u1.push_back(u0[j]-v[i]);
                    u1.push_back(u0[j]+v[i]);
                }
#if PRUN
                for(int j = 0; j < (int)u1.size(); j++) {
                    if (u1[j] != INFTY) {
                        for(int k = 0; k < (int)u1.size(); k++) {
                            if (k != j && u1[k] != INFTY && u1[k].real() >= u1[j].real() && u1[k].imag() >= u1[j].imag()) {
                                u1[k] = INFTY;
                            }
                        }
                    }
                }
#endif
                u0.clear();
                remove_copy(u1.begin(), u1.end(), back_inserter(u0), INFTY);
            }
            for(int i = 0; i < (int)u0.size(); i++) {
                complex<double> p(u0[i].real(), u0[i].imag());
                result = max(result, abs(p));
            }
        }



        // 4
        {
            vector<P> u0, u1;
            u0.push_back(P(0, 0));
            for(int i = 0; i < n; i++) {
                u1.clear();
                for(int j = 0; j < (int)u0.size(); j++) {
                    u1.push_back(u0[j]-v[i]);
                    u1.push_back(u0[j]+v[i]);
                }
#if PRUN
                for(int j = 0; j < (int)u1.size(); j++) {
                    if (u1[j] != INFTY) {
                        for(int k = 0; k < (int)u1.size(); k++) {
                            if (k != j && u1[k] != INFTY && u1[k].real() <= u1[j].real() && u1[k].imag() >= u1[j].imag()) {
                                u1[k] = INFTY;
                            }
                        }
                    }
                }
#endif
                u0.clear();
                remove_copy(u1.begin(), u1.end(), back_inserter(u0), INFTY);
            }
            for(int i = 0; i < (int)u0.size(); i++) {
                complex<double> p(u0[i].real(), u0[i].imag());
                result = max(result, abs(p));
            }
        }



        printf("Maximum distance = %.03f meters.\n", result);
    }
    return 0;
}
