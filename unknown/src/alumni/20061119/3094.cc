#include <string>
#include <iostream>
#include <vector>

#define REP(i, n) for(int i = 0; i < (int)(n); i++)

using namespace std;

int main()
{
  string s;
  while (getline(cin, s)) {
    if (s == "#")
      break;

    int sum = 0;
    REP(i, s.size()) {
      if (s[i] == ' ')
        continue;
      else {
        sum += (i + 1) * ((int)(s[i] - 'A') + 1);
      }
    }
    cout << sum << endl;
  }
  return 0;
}
