#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)


int main(void)
{
  int n;
  cin >> n;

  REP(afdsalkjf, n) {
    int num;
    cin >> num;

    int div = 10;
    while (num % div != num) {
      int mod = num % div;
      if (mod >= div / 2) {
        num = num - num % div + div;
      } else {
        num = num - num % div;
      }
      div *= 10;
    }

    cout << num << endl;
  }
}