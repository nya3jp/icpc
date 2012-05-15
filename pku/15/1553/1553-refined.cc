/*
 * 
 * 
 */


#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int,int> Region;


struct Solver {

    int w;
    vector<Region> prev, current;
    int pos;
    int colors;
    int skippedcolors;
    vector<int> uf;

    Solver() {
    }

    bool solve() {
        int n;
        scanf("%d%d%*d", &w, &n);
        if (w < 0)
            return false;

        prev.clear();
        prev.push_back(make_pair(0, -1));
        prev.push_back(make_pair(w, -1));
        pos = 0;
        colors = 0;
        skippedcolors = 0;
        uf.assign(1, -1);

        for(int i = 0; i < n; i++) {
            int len;
            scanf("%d", &len);
            process(len, (i%2 != 0));
        }

        assert(pos == 0);
        assert(colors == (int)uf.data.size());

        printf("%d\n", skippedcolors + count(uf.begin()+1, uf.end(), -1));
        return true;
    }

    bool same_type(int a, int b) {
        if (a == -1 && b == -1)
            return true;
        else if (a == -1 || b == -1)
            return false;
        return true;
    }

    int new_color() {
        uf.data.resize(colors+1, -1);
        return colors++;
    }

    int merge_color(int a, int b) {
        if (a == -1 && b == -1)
            return -1;
        else if (a == -1 || b == -1)
            assert(false);
        else if (a == -2 && b == -2)
            return new_color();
        else if (a == -2 || b == -2)
            return max(a, b);
        uf.link(a, b);
        return a;
    }

    void evaluate_line() {
        assert(pos == w);

        vector<Region> next;
        for(int i = 0; i < (int)current.size(); i++) {
            Region& r = current[i];
            if (!next.empty() && same_type(next.back().color, r.color)) {
                next.back().len += r.len;
                next.back().color = merge_color(next.back().color, r.color);
            }
            else {
                next.push_back(r);
            }
        }
        {
            int it = 0;
            for(int i = 0; i < (int)next.size(); i++) {
                Region& r = next[i];
                if (r.color != -1) {
                    while(!(prev[it].pos+prev[it].len > r.pos))
                        it++;
                    for(; it < (int)prev.size() && prev[it].pos < r.pos+r.len; it++) {
                        if (prev[it].color != -1)
                            r.color = merge_color(r.color, prev[it].color);
                    }
                    if (r.color == -2)
                        r.color = new_color();
                }
            }
        }

        /*
        for(int i = 0; i < (int)next.size(); i++) {
            printf("{pos=%d color=%d} ", next[i].pos, next[i].color);
        }
        printf("\n");
        */

        prev = next;
        current.clear();
        pos = 0;
        pit = 0;
    }

    void process_lines(int lines, bool diff) {
        assert(current.empty());

        //printf("-> processing lines %d\n", lines);

        if (lines == 0)
            return;

        if (!diff) {
            // do nothing
        }
        else {
            if (lines%2 == 1) {
                for(int i = 0; i < (int)prev.size(); i++) {
                    if (prev[i].color < 0)
                        prev[i].color = new_color();
                    else
                        prev[i].color = -1;
                }
                process_lines(lines-1, diff);
            }
            else {
                int c = 0;
                for(int i = 0; i < (int)prev.size(); i++) {
                    if (prev[i].color >= 0) {
                        prev[i].color = new_color();
                        c++;
                    }
                }
                addcolors += prev.size()*(lines/2) - c;
            }
        }
    }

    void process(int totallen, bool diff) {

        if (totallen == 0)
            return;

        //printf("process(%d,%d)\n", totallen, diff);

        if (totallen >= w && pos == 0) {
            process_lines(totallen / w, diff);
            process(totallen % w, diff);
            return;
        }

        Region& r = prev[pit];
        int seglen = r.pos+r.len-pos;
        int len = min(totallen, seglen);
        int remain = totallen - len;

        //printf("-> processing %d at %d\n", len, pos);

        if (diff) {
            if (r.color < 0)
                current.push_back((Region){pos, len, -2});
            else
                current.push_back((Region){pos, len, -1});
        }
        else {
            current.push_back((Region){pos, len, r.color});
        }
        pos += len;
        if (len == seglen)
            pit++;

        if (pos == w)
            evaluate_line();
        if (remain > 0)
            process(remain, diff);

    }

};


int main() {
    while(true) {
        Solver s;
        if (!s.solve())
            break;
    }
    return 0;
}

