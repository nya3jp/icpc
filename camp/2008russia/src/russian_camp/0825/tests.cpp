#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <complex>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define ALLOF(c) (c).begin(), (c).end()

#define PROBLEM_NAME "tests"


int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  int nFaculties, nSubjects;
  cin >> nFaculties >> nSubjects;

  vector<int> scores(nSubjects);
  REP(i, nSubjects)
    cin >> scores[i];

  bool army = true;

  REP(iFaculty, nFaculties) {
    string facultyName;
    cin >> ws;
    getline(cin, facultyName);

    int nTests;
    cin >> nTests;

    vector<int> tests(nTests);
    REP(i, nTests) {
      cin >> tests[i];
      tests[i]--;
    }

    int grade = 0;
    REP(i, nTests) {
      int c, b, a;
      cin >> c >> b >> a;
      int s = scores[tests[i]];
      if (s >= a)
	grade += 5;
      else if (s >= b)
	grade += 4;
      else if (s >= c)
	grade += 3;
      else
	grade += 2;
    }

    int nSpecialities;
    cin >> nSpecialities;
    REP(i, nSpecialities) {
      string specialityName;
      cin >> ws;
      getline(cin, specialityName);

      int needGrade;
      cin >> needGrade;
      if (grade >= needGrade) {
	cout << facultyName << " " << specialityName << endl;
	army = false;
      }
    }
  }

  if (army)
    cout << "Army" << endl;

  return 0;
}
