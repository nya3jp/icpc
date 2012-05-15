#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(c) (c).begin(),(c).end()

using namespace std;

int main()
{
  int b, n;
  while (cin >> b >> n) {
    if (b == 0 && n == 0)
      break;

    if (n == 1) {
      cout << b << endl;
      continue;
    }

    int prev_diff = INT_MAX;
    int prev_a = -1;
    for (int i = 1; i <= 1000; i++) {
      int an = 1;
      for (int j = 0; j < n; j++)
        an *= i;

      int diff = abs(b - an);
      if (prev_diff > diff) {
        prev_diff = diff;
        prev_a = i;
      }

      if (an > b)
        break;
    }

    cout << prev_a << endl;
  }
  return 0;
}
