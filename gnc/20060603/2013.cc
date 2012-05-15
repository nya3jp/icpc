#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string line;
    int iCase = 0;
    while(true) {
        getline(cin, line);
        int n;
        sscanf(line.c_str(), "%d", &n);
        if (n == 0)
            break;
        vector<string> v(n);
        for(int i = 0; i < n; i++)
            getline(cin, v[i]);
        vector<string> u(n);
        for(int i = 0; i < n; i++) {
            int j = (i%2 == 0 ? i/2 : n-i/2-1);
            u[j] = v[i];
        }
        cout << "SET " << ++iCase << endl;
        for(int i = 0; i < n; i++)
            cout << u[i] << endl;
    }
    return 0;
}
