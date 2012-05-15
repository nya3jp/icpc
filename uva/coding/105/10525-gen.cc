#include <cstdio>
#include <vector>
#include <complex>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv) {
    int n = 10;
    double pc = 1.0;

    if (argc >= 2)
        sscanf(argv[1], "%d", &n);
    if (argc >= 3)
        sscanf(argv[2], "%lf", &pc);

    std::srand(std::time(0));

    std::vector< std::complex<double> > v(n);
    for(int i = 0; i < n; i++)
    {
        v[i] = std::complex<double>((double)rand()/RAND_MAX,
                                    (double)rand()/RAND_MAX);
    }

    int m = 0;

    std::vector< std::vector<bool> > b(n, std::vector<bool>(n, false));
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            b[i][j] = (((double)rand()/RAND_MAX) <= pc);
            if (b[i][j])
                m++;
        }
    }

    std::printf("1\n\n%d %d\n", n, m);
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if (b[i][j])
            {
                std::printf("%3d %3d %3.8lf 1\n",
                            (i+1), (j+1),
                            700*std::abs(v[i]-v[j]));
            }
        }
    }

    std::printf("\n\n1\n1 %d\n", n);
    return 0;
}
