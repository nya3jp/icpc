#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

int main(void)
{
  int n;
  cin >> n;

  while (n--) {
    int numItem, numOps;
    cin >> numItem;
    cin >> numOps;

    vector<string> items;
    REP(i, numItem) {
      string item;
      cin >> item;
      items.push_back(item);
    }

    vector<string> result(items.size(), "");
    REP(iOp, numOps) {
      int from, to;
      cin >> from;
      cin >> to;
      from--;
      to--;

      result[to] = items[from];
      items[from] = "";
    }

    REP(iItem, items.size()) {
      if (items[iItem] != "") {
        REP(iResult, result.size()) {
          if (result[iResult] == "") {
            result[iResult] = items[iItem];
            break;
          }
        }
      }
    }

    REP(i, result.size()) {
      cout << result[i];
      if (i != result.size() - 1)
        cout << " ";
    }
    cout << endl;
  }
  return 0;
}