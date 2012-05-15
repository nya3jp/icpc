#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

// this is additional comment 2

int main() {
    string line;
    getline(cin, line);
    int n;
    sscanf(line.c_str(), "%d", &n);
    while(n-- > 0) {
        getline(cin, line);
        cout << "Hello, " << line << "." << endl;
    }
    return 0;
}

