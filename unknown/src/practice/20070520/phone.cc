#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

struct operation_t {
    int year;
    int mode;
    string areaname;
    string areacode;
    string param;
};

bool by_year(const operation_t& a,const operation_t& b) {
    return (a.year < b.year);
}



int main() {

    map<string, string> areanameToAreacode;

    int nAreas;
    cin >> nAreas;
    REP(i, nAreas) {
        string areacode, areaname;
        cin >> areacode >> areaname;
        areanameToAreacode[areaname] = areacode;
    }

    int nOperations;
    cin >> nOperations;
    vector<operation_t> operations;
    REP(i, nOperations) {
        operation_t op;
        cin >> op.year >> op.mode >> op.areaname >> op.param;
        operations.push_back(op);
    }
    sort(operations.begin(), operations.end(), by_year);

    REP(i, nOperations) {
        operation_t& op = operations[i];
        op.areacode = areanameToAreacode[op.areaname];
        if (op.mode == 3)
            areanameToAreacode[op.areaname] = op.param;
    }

    map<int, int> shortcut;
    REP(i, nOperations) {
        operation_t& op = operations[i];
        shortcut[op.year] = i;
    }

    for(;;) {

        int yearFrom, yearTo;
        string number;
        cin >> yearFrom >> yearTo >> number;
        if (yearFrom == 0 && yearTo == 0 && number == "0")
            break;

        int iOperation = shortcut.lower_bound(yearFrom+1)->second;
        while(iOperation < nOperations) {
            operation_t& op = operations[iOperation];
            iOperation++;

            if (op.year > yearTo)
                break;

            if (strncmp(op.areacode.c_str(), number.c_str(), op.areacode.size()) != 0)
                continue;

            //cout << "at year " << op.year << " " << number << " -> ";

            switch(op.mode) {
            case 1:
            {
                int ith;
                sscanf(op.param.c_str(), "%d", &ith);
                ith--;
                ith += op.areacode.size();
                assert(ith < number.size());
                number = number.substr(0, ith+1) + number.substr(ith, 1) + number.substr(ith+1);
            }
            break;
            case 2:
            {
                int ith;
                sscanf(op.param.c_str(), "%d", &ith);
                ith--;
                ith += op.areacode.size();
                assert(ith < number.size()-1);
                swap(number[ith], number[ith+1]);
            }
            break;
            case 3:
            {
                number = op.param + number.substr(op.areacode.size());
            }
            break;
            default:
                assert(false);
            }
            
            //cout << number << endl;
        }

        cout << number << endl;

    }


    return 0;
}
