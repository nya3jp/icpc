#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

typedef vector<const char*> SA;


bool comp(const char* a, const char* b) {
    return (strncmp(a, b, 1000) < 0);
}


int main() {
    ifstream fin("english.in");
    string line;

    int iCase = 0;
    while(getline(fin, line) && line == "%%%%%") {
        ostringstream os;
        while(getline(fin, line) && line != "%%%%%")
            os << line << ' ';
        string body_str = os.str();
        const char* body = body_str.c_str();
        const int len = strlen(body);
        SA sa(len);
        for(int i = 0; i < len; i++)
            sa[i] = body + i;
        sort(sa.begin(), sa.end(), comp);

        if (iCase > 0)
            cout << endl;
        cout << "Case " << ++iCase << ":" << endl;
        while(getline(fin, line) && line != "%%%%%") {
            string query = line;
            string query_next = line;
            query_next[query_next.size()-1]++;
            int n = lower_bound(sa.begin(), sa.end(), query_next.c_str(), comp)
                  - lower_bound(sa.begin(), sa.end(), query.c_str(), comp);
            cout << n << endl;
        }
        getline(fin, line);
    }


    return 0;
}




