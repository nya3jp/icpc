/*
 * UVA 10587 - Mayor's posters
 * 2006-01-15
 * by nya
 */

#include <cstdio>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <utility>

class LinePainting {
private:
    struct Segment {
        int from, to, color;
        Segment(int from, int to, int color) : from(from), to(to), color(color) {
        }
        friend inline bool operator<(const Segment& a, const Segment& b) {
            return (a.to < b.to);
        }
    };

    typedef std::set<Segment> data_type;
    data_type data;

public:

    /*
     * [from,to)‚Ì—Ìˆæ‚ğFcolor‚Å“h‚é
     * ‚·‚Å‚É“h‚ç‚ê‚Ä‚¢‚é—Ìˆæ‚Íã‘‚«‚·‚é
     * ğŒ: 0 <= from < to
     *       0 <= color
     */
    void paint(int from, int to, int color) {
        assert(0 <= from && from < to);
        assert(0 <= color);
        for(int pos = from; pos < to; ) {
            data_type::iterator it = data.upper_bound(Segment(0, pos, 0));
            if (it == data.end())
                break;
            if (it->from < to) {
                Segment seg = *it;
                data.erase(it);
                if (seg.from < pos)
                    data.insert(Segment(seg.from, pos, seg.color));
                if (to < seg.to)
                    data.insert(Segment(to, seg.to, seg.color));
                pos = seg.to;
            }
            else {
                pos = it->to;
            }
        }
        data.insert(Segment(from, to, color));
    }

    /*
     * [from,to)‚Ì—Ìˆæ‚ğFcolor‚Å“h‚é
     * ‚·‚Å‚É“h‚ç‚ê‚Ä‚¢‚é—Ìˆæ‚ª‚ ‚éê‡‚Í•ÏX‚µ‚È‚¢
     * ğŒ: 0 <= from < to
     *       0 <= color
     */
    void paint2(int from, int to, int color) {
        assert(0 <= from && from < to);
        assert(0 <= color);
        while(from < to) {
            data_type::const_iterator it = data.upper_bound(Segment(0, from, 0));
            if (it == data.end()) {
                data.insert(Segment(from, to, color));
                break;
            }
            if (from < it->from) {
                data.insert(Segment(from, std::min(to, it->from), color));
            }
            from = it->to;
        }
    }

    /*
     * [pos,pos+1)‚ÌF‚ğæ“¾‚·‚é
     * ‰½‚à“h‚Á‚Ä‚È‚¢ê‡‚Í-1‚ğ•Ô‚·
     * ğŒ: 0 <= pos
     */
    int getColor(int pos) const {
        assert(0 <= pos);
        data_type::const_iterator it = data.upper_bound(Segment(0, pos, 0));
        if (it != data.end() && it->from <= pos)
            return it->color;
        return -1;
    }

    /*
     * Œ»İŒ©‚¦‚éF”‚ğæ“¾‚·‚é
     */
    int countColors() const {
        std::set<int> s;
        for(data_type::const_iterator it = data.begin();
            it != data.end();
            ++it)
        {
            s.insert(it->color);
        }
        return (int)s.size();
    }

    /*
     * ˜A‘±‚µ‚½‹æŠÔ‚Ì”‚ğ”‚¦‚é
     */
    int countIntervals() const {
        int n = 0;
        int pos = -1;
        for(data_type::const_iterator it = data.begin();
            it != data.end();
            ++it)
        {
            if (it->from != pos)
                n++;
            pos = it->to;
        }
        return n;
    }
};

int main() {
    int nCases;
    std::scanf("%d", &nCases);
    for(int iCase = 0; iCase < nCases; iCase++) {

        LinePainting lp;

        int nPosters;
        std::scanf("%d", &nPosters);
        for(int i = 0; i < nPosters; i++) {
            int from, to;
            std::scanf("%d%d", &from, &to);
            if (!(from <= to))
                std::swap(from, to);
            lp.paint(from, to+1, i);
        }

        std::printf("%d\n", lp.countColors());
    }
    return 0;
}

