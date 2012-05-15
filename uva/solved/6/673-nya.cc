/*
 * UVA 673 Parentheses Balance
 * 2004-11-07
 * by nya
 */

#include <iostream>
#include <string>
#include <sstream>
#include <deque>

using namespace std;

void chomp(char* p)
{
    int i;
    for(i=0; p[i]; i++);
    for(i--; i>=0&&(p[i]=='\r'||p[i]=='\n'); p[i]='\0');
}

bool check(string& s, int& pos)
{
    while(pos < s.size()) {
        switch(s[pos]) {
        case '(':
            if (! check(s,++pos))
                return false;
            if (s[pos++] != ')')
                return false;
            break;
        case '[':
            if (! check(s,++pos))
                return false;
            if (s[pos++] != ']')
                return false;
            break;
        default:
            return true;
        }
    }
    return true;
}


int main()
{
    char buf[1024];
    istringstream iss;
    int n;
    cin.getline(buf, sizeof(buf));
    iss.str(buf);
    iss >> n;
    while(n-- > 0) {
        string s;
        cin.getline(buf, sizeof(buf));
        chomp(buf);
        s = buf;
        deque<int> q;
        int pos;
        for(pos=0; pos<s.size(); pos++) {
            switch(s[pos]) {
            case '(':
                q.push_back(0);
                break;
            case '[':
                q.push_back(1);
                break;
            case ')':
                if (q.empty() || q.back() != 0)
                    goto err;
                q.pop_back();
                break;
            case ']':
                if (q.empty() || q.back() != 1)
                    goto err;
                q.pop_back();
                break;
            default:
                goto err;
            }
        }
    err:
        if (q.empty() && pos == s.size())
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
