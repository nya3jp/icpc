#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;




int main() {
    vector< pair<string, string> > books;
    while(true) {
        char title[1024], author[1024];
        if (scanf(" \"%[^\"]\" by %[^\n]", title, author) == 0)
            break;
        books.push_back(make_pair(string(author), string(title)));
    }
    sort(books.begin(), books.end());
    int n = books.size();
    map<string,int> ids;
    for(int i = 0; i < n; i++) {
        ids.insert(make_pair(books[i].second, i));
    }
    vector<int> states(n, 1);
    scanf(" END");
    {
        char cmd[1024];
        while(true) {
            scanf(" %s", cmd);
            if (strcmp(cmd, "END") == 0)
                break;
            char title[1024];
            int id;
            if (strcmp(cmd, "BORROW") == 0 || strcmp(cmd, "RETURN") == 0) {
                scanf(" \"%[^\"]\"", title);
                id = ids[string(title)];
            }
            if (strcmp(cmd, "BORROW") == 0) {
                states[id] = 0;
            }
            if (strcmp(cmd, "RETURN") == 0) {
                states[id] = -1;
            }
            if (strcmp(cmd, "SHELVE") == 0) {
                int last = -1;
                for(int i = 0; i < n; i++) {
                    if (states[i] == -1) {
                        printf("Put \"%s\" ", books[i].second.c_str());
                        if (last < 0)
                            printf("first\n");
                        else
                            printf("after \"%s\"\n", books[last].second.c_str());
                        states[i] = 1;
                    }
                    if (states[i] == 1) {
                        last = i;
                    }
                }
                printf("END\n");
            }
        }
    }
    return 0;
}

