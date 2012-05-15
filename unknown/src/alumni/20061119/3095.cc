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
  string s;
  while (getline(cin, s)) {
    if (s == "#")
      break;

    vector<int> falls;
    int orign = s.size();
    s = '.' + s + '.';
    int n = s.size();
    REP(i, n) {
      if ((s[i] == '.'))
        falls.push_back(100);
      else
        falls.push_back(0);
    }

    for (int i = 1; i < falls.size(); i++) {
      if (s[i] == '_' && falls[i - 1])
        falls[i] = 100;
    }
    for (int i = falls.size() - 2; i >= 0; i--) {
      if (s[i] == '_' && falls[i + 1])
        falls[i] = 100;
    }

    int sum = 0;
    REP(i, orign) {
      switch (s[i + 1]) {
      case '/':
        sum += falls[i];
        break;

      case '\\':
        sum += falls[i + 2];
        break;

      case '_':
        sum += 0;
        break;

      case '|':
        sum += (falls[i] + falls[i + 2]) / 2;
        break;

      case '.':
        sum += 100;
        break;

      default:
        assert(false);
        break;
      }
    }

    cout << (sum / orign) << endl;
  }
  return 0;
}
