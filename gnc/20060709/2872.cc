#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int nDic;
    cin >> nDic;
    vector<string> dic(nDic);
    for(int i = 0; i < nDic; i++)
        cin >> dic[i];
    sort(dic.begin(), dic.end());

    int nMails;
    cin >> nMails;

    for(int iMail = 0; iMail < nMails; iMail++) {
        bool rejected = false;
        for(string s; cin >> s && s != "-1"; ) {
            if (!binary_search(dic.begin(), dic.end(), s)) {
                if (!rejected)
                    cout << "Email " << iMail+1 << " is not spelled correctly." << endl;
                rejected = true;
                cout << s << endl;
            }
        }
        if (!rejected) {
            cout << "Email " << iMail+1 << " is spelled correctly." << endl;
        }
    }
    cout << "End of Output" << endl;

    return 0;
}
