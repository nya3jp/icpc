#include <iostream>

using namespace std;

inline bool isLeapYear(int year) {
    return (year%4 == 0 && (year%100 != 0 || year/100%4 == 0));
}

int main() {
    int year, month, day;

    cin >> year >> month >> day;

    int n = 0;
    for(int y = 1; y < year; y++)
        n += 365 + (isLeapYear(y) ? 1 : 0);

    int MONTHDAYS[2][12+1] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    };
    for(int m = 1; m < month; m++)
        n += MONTHDAYS[isLeapYear(year) ? 1 : 0][m];

    n += day-1;

    cout << ((const char*[]){"monday","tuesday","wednesday","thursday","friday","saturday","sunday"})[(n+0)%7] << endl;


    return 0;
}
