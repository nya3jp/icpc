#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int tableCol[1000];
int tableRow[1000];
int table2D[1000][1000];

int main(void)
{
  ifstream cin("i.in");

  int nCases;
  cin >> nCases;
  REP(iCases, nCases) {
    REP(i, 1000) {
      tableCol[i] = 0;
      tableRow[i] = 0;
    }
    REP(i, 1000) REP(j, 1000) {
      table2D[i][j] = 0;
    }

    int dist, nBuildings;
    cin >> dist;
    cin >> nBuildings;
    REP(i, nBuildings) {
      int x, y;
      cin >> x >> y;
      x += 1000000000;
      y += 1000000000;

      int xMod, yMod;
      xMod = x % dist;
      yMod = y % dist;
      tableCol[xMod]++;
      tableRow[yMod]++;
      table2D[yMod][xMod]++;
    }

    int ret = INT_MAX;
    REP(i, dist) REP(j, dist) {
      ret <?= tableCol[i] + tableRow[j] - table2D[j][i];
    }

    cout << ret << endl;
  }
}
