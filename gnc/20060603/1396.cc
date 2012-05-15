#include <iostream>
#include <string>
#include <vector>

using namespace std;

string fix(string s) {
    int n = s.size();
    int i = 0;
    while(i < n && s[i] == '0')
        i++;
    if (i == n)
        return "0";
    return s.substr(i);
}

string splus(string s1, string s2) {
    int n = max(s1.length(), s2.length());
    s1 = string(n - (int)s1.length(), '0') + s1;
    s2 = string(n - (int)s2.length(), '0') + s2;
    string s(n, '0');
    int c = 0;
    for(int i = n-1; i >= 0; i--) {
        int t = (int)(s1[i] - '0') + (int)(s2[i] - '0') + c;
        c = t/10;
        t = t%10;
        s[i] = (char)('0' + t);
    }
    if (c > 0)
        s = string(1, (char)('0' + c)) + s;
    return fix(s);
}

string sminus(string s1, string s2) {
    int n = max(s1.length(), s2.length());
    s1 = string(n - (int)s1.length(), '0') + s1;
    s2 = string(n - (int)s2.length(), '0') + s2;
    string s(n, '0');
    int c = 0;
    for(int i = n-1; i >= 0; i--) {
        int t = (int)(s1[i] - '0') - (int)(s2[i] - '0') - c;
        c = (t < 0 ? 1 : 0);
        t += c*10;
        s[i] = (char)('0' + t);
    }
    return fix(s);
}

string smulti(string s1, int m) {
    string s = "0";
    for(int i = 0; i < m; i++)
        s = splus(s, s1);
    return s;
}

int max(vector<string>& v) {
    int s = 0;
    for(int i = 0; i < (int)v.size(); i++)
        s = max(s, (int)v[i].size());
    return s;
}

void insert_hr(vector<string>& v, int index) {
    string& s1 = v[index-1];
    string& s2 = v[index];
    int n1 = s1.size();
    int n2 = s2.size();
    int left = max(n1, n2);
    int right = 0;
    while(s1[n1-1-right] == ' ' && s2[n2-1-right] == ' ')
        right++;
    string hr = string(left-right, '-') + string(right, ' ');
    v.insert(v.begin()+index, hr);
}

string trunc_space(const string& s) {
    int n = (int)s.size();
    while(n > 0 && s[n-1] == ' ')
        n--;
    return s.substr(0, n);
}


int main() {
    char line[2048], ss1[1024], ss2[1024], op;
    int nCases;
    scanf("%d", &nCases);
    for(int iCase = 0; iCase < nCases; iCase++) {
        //scanf(" %[^+-*\r\n ]%c%[^+-*\r\n ]", ss1, &op, ss2);
        scanf("%s", line);
        sscanf(line, "%[^+-*]%c%s", ss1, &op, ss2);
        string s1(ss1), s2(ss2);
        //cout << "> " << s1 << op << s2 << endl;
        vector<string> result;
        switch(op) {
        case '+':
        {
            result.push_back(s1);
            result.push_back(string(1, '+') + s2);
            result.push_back(splus(s1, s2));
            insert_hr(result, 2);
        }
            break;
        case '-':
        {
            result.push_back(s1);
            result.push_back(string(1, '-') + s2);
            result.push_back(sminus(s1, s2));
            insert_hr(result, 2);
        }
            break;
        case '*':
        {
            result.push_back(s1);
            result.push_back(string(1, '*') + s2);
            string s = "0";
            for(int i = 0; i < (int)s2.size(); i++) {
                //cout << "> " << s1 << " * " << (int)(s2[(int)s2.size() - 1 - i] - '0') << endl;
                string t = smulti(s1, (int)(s2[(int)s2.size() - 1 - i] - '0'));
                result.push_back(t + string(i, ' '));
                s = splus(s, t + string(i, '0'));
            }
            insert_hr(result, 2);
            if ((int)s2.size() > 1) {
                result.push_back(s);
                insert_hr(result, (int)result.size()-1);
            }
        }
            break;
        }
        int n = max(result);
        for(int i = 0; i < (int)result.size(); i++)
            cout << trunc_space(string(n-(int)result[i].size(), ' ') + result[i]) << endl;
        cout << endl;
    }
    return 0;
}
