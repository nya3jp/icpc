

#include <iostream>
#include <cmath>
#include <fstream>

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

using namespace std;


fstream fin("graveyard.in");
#define cin fin

int main(void)
{
  int nCases;
  cin >> nCases;
  REP(iCase, nCases){
    int n, m;
    cin >> n >> m;
    
    m += n;
    double sum = 0;
    REP(i, n){
      double old = (double)i * m / n;
      sum += fabs(round(old) - old);
    }
    
//     double sum2 = 0;
//     REP(i, n){
//       double old = (double)(i+0.5) * m / n;
//       sum2 += fabs(round(old) - old);
//     }
//     printf("%.4f\n", 10000. / m * (sum2 <? sum));
    printf("%.4f\n", 10000. / m * sum);
  }
  return 0;
}
