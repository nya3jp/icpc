#include <iostream>
#include <vector>

struct Segment {
    int color, length;
    Segment() {}
    Segment(int color, int length) : color(color), length(length) {}
};

struct Data {
    short score, length;
};

inline int index(int i, int j, int k, int n) {
    return (((i*n)+j)*n+k);
}

int main() {
    int nCases;
    std::cin >> nCases;

    for(int iCase = 0; iCase < nCases; iCase++) {

        int length;
        std::cin >> length;

        std::vector<Segment> field;

        std::vector<int> colors;

        {
            Segment seg(-1, 0);
            for(int i = 0; i < length; i++) {
                int color;
                std::cin >> color;
                colors.push_back(color);
                if (color != seg.color) {
                    if (seg.length > 0)
                        field.push_back(seg);
                    seg.color = color;
                    seg.length = 1;
                }
                else {
                    seg.length++;
                }
            }
            field.push_back(seg);
        }
        const int n = field.size();

        std::sort(colors.begin(), colors.end());
        colors.erase(std::unique(colors.begin(), colors.end()), colors.end());

        const int m = colors.size();

        std::map<int,int> recoloring;
        for(int i = 0; i < m; i++) {
            recoloring[colors[i]] = i+1;
        }

        for(int i = 0; i < n; i++) {
            field[i].color = recoloring[field[i].color];
        }

        Data* table = new Data[n*n*(m+1)];

        for(int i = 0; i < n; i++) {
            for(int color = 0; color <= m; color++) {
                int idx = index(color, i, i, n);
                if (color == field[i].color) {
                    table[idx].score = 0;
                    table[idx].length = field[i].length;
                }
                else {
                    table[idx].score = field[i].length * field[i].length;
                    table[idx].length = 0;
                }
            }
        }

        for(int from = 0; from < n; from++) {
            for(int to = from+1; to < n; to++) {
                for(int color = 1; color <= m; color++) {
                    
                }
            }
        }
    }

    return 0;
}

