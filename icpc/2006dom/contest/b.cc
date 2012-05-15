#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;


int solve(string original) {

    int n = original.size();

    set<string> s;

    for(int i = 1; i <= n-1; i++) {

        string head = original.substr(0, i);
        string tail = original.substr(i);

        for(int headr = 0; headr < 2; headr++) {
            string head2 = head;
            if (headr > 0)
                reverse(head2.begin(), head2.end());
            for(int tailr = 0; tailr < 2; tailr++) {
                string tail2 = tail;
                if (tailr > 0)
                    reverse(tail2.begin(), tail2.end());
                s.insert(head2+tail2);
                s.insert(tail2+head2);
            }
        }

    }

    return s.size();
}


int main() {

    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        cout << solve(s) << endl;
    }

    return 0;
}

