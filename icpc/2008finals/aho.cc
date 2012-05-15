
struct AM {
    vector<int> acs;
    map<char, AM*> tr;
    int k;
    AM* back;
    AM(int k) : k(k) {}
    AM* descend(char c) {
        if (tr.count(c) == 0)
            tr[c] = new AM(k+1);
        return tr[c];
    }
};

void regist(AM* cur, string s) {
    AM* head = cur;
    REP(i, s.size()) {
        while(head->k > 0 && s[head->k] != s[i])
            head = head->back;
        cur = cur->descend(s[i]);
        cur->back = head;
    }
}


