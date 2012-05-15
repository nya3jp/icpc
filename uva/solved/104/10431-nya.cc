/*
 * UVA 10431 Normal Distribution
 * 2005-09-27
 * by nya
 */

#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cassert>

const double PI = std::acos(0.0)*2;

int main() {
    int iCase=0;
    int nData;
    while(std::scanf("%d", &nData) == 1) {

        double dSum = 0.0;
        double dSqSum = 0.0;
        for(int i=0; i<nData; i++) {
            double data;
            std::scanf("%lf", &data);
            dSum += data;
            dSqSum += data*data;
        }
        double dMean = dSum / nData;
        double dSD = std::sqrt( (dSqSum - nData*dMean*dMean) / (nData - 1) );

        if (iCase > 0)
            std::printf("\n");
        std::printf("Data Set #%d\n"
                    "Mean = %.4lf\n"
                    "Standard Deviation = %.4lf\n",
                    ++iCase, dMean, dSD);

        /*
        // normalize
        for(int i=0; i<nData; i++) {
            data[i] = (data[i] - dMean) / dSD;
        }
        */

        int nQueries;
        std::scanf("%d", &nQueries);

        for(int iQuery=0; iQuery<nQueries; iQuery++) {

            double z;
            std::scanf("%lf", &z);
            const double nz = (z - dMean) / dSD;

            double q = 0.0;

            {
                const double t = 1.0 / (1.0 + 0.2316419*std::abs(nz));
                const double B[] = {0.319381530,
                                    -0.356563782,
                                    1.781477937,
                                    -1.821255978,
                                    1.330274429};
                for(int i=4; i>=0; i--) {
                    q += B[i];
                    q *= t;
                }
            }

            q *= std::exp(-nz*nz/2) / std::sqrt(2 * PI);

            std::printf("P(z) = %.4lf, Q(z) = %.4lf, T = %.4lf\n",
                        1.0 - q, q, nData*q);

        }

    }
    return 0;
}
