#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>

using namespace std;

struct Alignment {
    int importance;
    int time;
};

inline int abs(int n) {
    return (n < 0 ? -n : n);
}

int main() {

    int iCase = 0;

    int nPrograms;
    while(cin >> nPrograms && nPrograms != 0) {

        //vector<int> programs(nPrograms);
        int programs[8];
        for(int i = 0; i < nPrograms; i++) {
            cin >> programs[i];
        }

        int nAlignments;
        cin >> nAlignments;
        //vector<Alignment> alignments(nAlignments);
        Alignment alignments[8];

        for(int i = 0; i < nAlignments; i++) {
            Alignment& a = alignments[i];
            cin >> a.importance >> a.time;
            a.importance--;
        }

        //vector<int> order(nPrograms);
        int order[8];
        for(int i = 0; i < nPrograms; i++)
            order[i] = i;

        //vector<int> best_order;
        int best_order[8];
        //vector<int> best_error(5, numeric_limits<int>::max());
        int best_error[5];
        fill(best_error, best_error+5, numeric_limits<int>::max());

        do {

            //vector<int> error(5, 0);
            int error[5];
            fill(error, error+5, 0);

            //vector<int> schedule(nPrograms+1, 0);
            int schedule[8+1];
            fill(schedule, schedule+8+1, 0);

            for(int i = 0; i < nPrograms; i++)
                schedule[i+1] = schedule[i] + programs[order[i]];

            for(int i = 0; i < nAlignments; i++) {
                int nearest = numeric_limits<int>::max();
                for(int j = 0; j < nPrograms+1; j++) {
                    int e = abs(schedule[j] - alignments[i].time);
                    if (e < nearest) {
                        nearest = e;
                    }
                }
                error[alignments[i].importance] += nearest;
            }

            //if (lexicographical_compare(error.begin(), error.end(), best_error.begin(), best_error.end())) {
            if (lexicographical_compare(error, error+5, best_error, best_error+5)) {
                //best_order = order;
                copy(order, order+nPrograms, best_order);
                //best_error = error;
                copy(error, error+5, best_error);
            }
        //} while(next_permutation(order.begin(), order.end()));
        } while(next_permutation(order, order+nPrograms));

        cout << "Data set " << ++iCase << endl
             << "Order:";
        for(int i = 0; i < nPrograms; i++)
            cout << ' ' << programs[best_order[i]];
        cout << endl
             //<< "Error: " << accumulate(best_error.begin(), best_error.end(), (int)0) << endl;
             << "Error: " << accumulate(best_error, best_error+5, (int)0) << endl;

    }

    return 0;
}

