#include <string>
#include <iostream>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

bool is_friend(string dict, string query)
{
  vector<bool> dict_vec(10, false);
  REP(i, dict.size())
    dict_vec[dict[i] - '0'] = true;

  vector<bool> query_vec(10, false);
  REP(i, query.size())
    query_vec[query[i] - '0'] = true;

  /*
  if (dict_vec == query_vec) {
    cout << "friend " << dict << ":" << query << endl;
  }
  */

  return (dict_vec == query_vec);
}


bool is_almost_friend1(string dict, string query)
{
  for (int nth = 0; nth < query.size() - 1; nth++) {
    string query1, query2;
    char n1, n2;

    // -1, +1
    n1 = query[nth];
    n2 = query[nth + 1];
    n1--;
    n2++;
    if ((!(nth == 0 && n1 == '0')) && isdigit(n1) && isdigit(n2)) {
      query1 = query;
      query1[nth] = n1;
      query1[nth + 1] = n2;
      if (is_friend(dict, query1)) {
        return true;
      }
    }

    // +1, -1
    n1 = query[nth];
    n2 = query[nth + 1];
    n1++;
    n2--;
    if ((!(nth == 0 && n1 == '0')) && isdigit(n1) && isdigit(n2)) {
      query2 = query;
      query2[nth] = n1;
      query2[nth + 1] = n2;
      if (is_friend(dict, query2)) {
        return true;
      }
    }
  }

  return false;
}

bool is_almost_friend(string dict, string query)
{
  return (is_almost_friend1(dict, query) || is_almost_friend1(query, dict));
}

int main(void)
{
  int n;
  cin >> n;
  REP(i, n) {
    string dict, query;
    cin >> dict;
    cin >> query;

    if (is_friend(dict, query)) {
      cout << "friends" << endl;
      continue;
    }

    if (is_almost_friend(dict, query)) {
      cout << "almost firends" << endl;
      continue;
    }

    cout << "nothing" << endl;
  }
}