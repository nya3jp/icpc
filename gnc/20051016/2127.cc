#include <iostream>
#include <algorithm>
#include <utility>
#include <stack>

using namespace std;

int g_table[501][501];
pair<int, int> g_lastUsed[501][501];
int g_maxLength;
int g_seq1[501];
int g_seq2[501];
int g_length1, g_length2;
pair<int, int> g_maxpos;

void solve(int length, pair<int, int> lastUsed, int pos1, int pos2)
{
    if(pos1 == g_length1 || pos2 == g_length2)
        return;

    // use g_seq1[pos1]
    if(length == 0 || g_seq1[pos1] > g_seq1[lastUsed.first]) {
        for(int current = pos2; current < g_length2; current++) {
            if(g_seq1[pos1] == g_seq2[current]) {
                if(g_table[pos1][current] < length+1) {
                    
                    g_table[pos1][current] = length+1;
                    g_lastUsed[pos1][current] = lastUsed;
                    if(g_maxLength < length+1) {
                        g_maxLength = length+1;
                        g_maxpos = make_pair(pos1, current);
                    }

                    int i;
                    for(i = 0; i < current; i++) {
                        if(g_table[pos1][i] >= length+1 && g_seq2[i] <= g_seq2[current])
                            break;
                    }
                    if(i == current)
                        solve(length+1, make_pair(pos1, current), pos1+1, current+1);
                }
            }
        }
    }

    // don't use seq1[pos1]
    solve(length, lastUsed, pos1+1, pos2);
}

int main()
{
    // initialize
    for(int i = 0; i <= 500; i++) {
        for(int j = 0; j <= 500; j++) {
            g_table[i][j] = 0;
            g_lastUsed[i][j] = make_pair(-1, -1);
        }
    }
    g_maxpos = make_pair(-1, -1);

    // input
    cin >> g_length1;
    for(int i = 0; i < g_length1; i++)
        cin >> g_seq1[i];
    cin >> g_length2;
    for(int i = 0; i < g_length2; i++)
        cin >> g_seq2[i];

    solve(0, make_pair(-1, -1), 0, 0);

    // output
    cout << g_maxLength << endl;

    pair<int, int> pos = g_maxpos;
    stack<int> st;
    while(pos != make_pair(-1, -1)) {
        st.push(g_seq1[pos.first]);
        pos = g_lastUsed[pos.first][pos.second];
    }

    bool first = true;
    while(!st.empty()) {
        if(first) first = false;
        else cout << ' ';

        cout << st.top();
        st.pop();
    }
    cout << endl;

    return 0;
}
