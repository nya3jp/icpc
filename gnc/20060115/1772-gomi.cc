#include <cstdio>
#include <vector>

typedef std::vector<int> vec;

vec operator+(const vec& a, const vec& b) {
    int n = (int)a.size();
    assert(a.size() == b.size());
    vec v(n);
    for(int i=0; i<n; i++)
        v[i] = a[i] + b[i];
    return v;
}
vec operator*(const vec& a, int m) {
    int n = (int)a.size();
    vec v(a);
    for(int i=0; i<n; i++)
        v[i] *= m;
    return v;
}

int main() {

    int n = 4;

    std::vector<vec> vectors;

    for(int i=0; i<n; i++) {
        vec v(n*n, 0);
        for(int j=0; j<n; j++)
            v[i*n+j] = 1;
        vectors.push_back(v);
    }
    for(int i=0; i<n; i++) {
        vec v(n*n, 0);
        for(int j=0; j<n; j++)
            v[j*n+i] = 1;
        vectors.push_back(v);
    }
    for(int i=0; i<2*n-1; i++) {
        vec v(n*n, 0);
        for(int j=0; j<n; j++) {
            //x+y = i
            //x = j;
            // -> x = j, y = i-j
            int x = j;
            int y = i - j;
            if (0 <= x && x < n && 0 <= y && y < n)
                v[y*n+x] = 1;
        }
        vectors.push_back(v);
    }
    for(int i=-n+1; i<n; i++) {
        vec v(n*n, 0);
        for(int j=0; j<n; j++) {
            //x-y = i
            //x = j;
            // -> x = j, y = i+j
            int x = j;
            int y = i + j;
            if (0 <= x && x < n && 0 <= y && y < n)
                v[y*n+x] = 1;
        }
        vectors.push_back(v);
    }

    /*
    for(int k=0; k<(int)vectors.size(); k++) {
        const vec& u = vectors[k];
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                std::printf("%s",u[j*n+i]?"X":".");
            }
            std::printf("\n");
        }
        std::printf("\n");
    }
    */

    vec v(n*n, 0);
    search(

    return 0;
}
