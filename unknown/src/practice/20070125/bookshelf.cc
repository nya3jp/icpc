#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <deque>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

struct Book {
    int id;
    int w;
};

int main() {
    int width;

    int iCase = 0;
    while(cin >> width && width >= 0) {

        deque<Book> shelf;
        int cur = 0;

        for(;;) {
            string cmd;
            cin >> cmd;
            if (cmd == "E")
                break;
            if (cmd == "R") {
                int id;
                cin >> id;
                REP(i, shelf.size()) {
                    if (shelf[i].id == id) {
                        cur -= shelf[i].w;
                        shelf.erase(shelf.begin()+i);
                        break;
                    }
                }
            }
            if (cmd == "A") {
                Book book;
                cin >> book.id >> book.w;
                cur += book.w;
                shelf.push_front(book);

                while(cur > width) {
                    cur -= shelf.back().w;
                    shelf.pop_back();
                }

            }
        }

        printf("PROBLEM %d:", ++iCase);
        REP(i, shelf.size())
            printf(" %d", shelf[i].id);
        printf("\n");

    }


    return 0;
}
