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
    if (s == "*")
      break;

    bool flag = true;
    for (int d = 1; d < s.size(); d++) {
      vector<pair<char, char> > pairs;
      for (int i = 0; (i + d) < s.size(); i++) {
        pairs.push_back(make_pair(s[i], s[i + d]));
      }

      int origsize = pairs.size();
      sort(ALL(pairs));
      pairs.erase(unique(ALL(pairs)), pairs.end());
      int aftersize = pairs.size();

      if (origsize != aftersize)
        flag = false;
    }

    if (flag)
      cout << s << " is surprising." << endl;
    else
      cout << s << " is NOT surprising." << endl;
  }
}
