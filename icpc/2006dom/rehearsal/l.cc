#include <iostream>
#include <string>

using namespace std;

int main() {
    string line;
    int n = 0;
    while(getline(cin, line))
        n++;
    cout << n << endl;
    return 0;
}
