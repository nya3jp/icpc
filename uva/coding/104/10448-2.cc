/*
 * UVA 10448 Unique World
 * 2005-07-09
 * by nya
 */
const int INF = 100000000;


/*
 * ナップサック問題
 */

#include <vector>
#include <utility>

using namespace std;

typedef int Value;
struct Item {
    int volume;
    Value value;
};
typedef vector<Item> Items;

/*
 * アイテムが無限にあるナップサック問題を解く
 * 価値の合計と入れるアイテムのリストを返す
 */
pair<Value, vector<int> > knapsack(const Items& items, const int volume) {
    const int nItems = items.size();

    /*
    printf("knapsack(%d)\n", volume);
    for(int i = 0 ; i <nItems; i++)
        printf("item%d %d,%d\n", i, items[i].volume, items[i].value);
    */

    vector< pair<Value,int> > table(volume+1, make_pair(INF, -1));
    table[0] = make_pair(0, -1);

    for(int i = nItems-1; i >= 0; i--) {
        const Item& item = items[i];
        for(int v = item.volume; v <= volume; v++) {
            if (table[v].first > table[v-item.volume].first + item.value) {
                table[v].first = table[v-item.volume].first + item.value;
                table[v].second = i;
            }
        }
    }

    Value best_value = table[volume].first;
    vector<int> knapsack;
    for(int v = volume; table[v].second >= 0; v -= items[table[v].second].volume) {
        knapsack.push_back(table[v].second);
    }

    return make_pair(best_value, knapsack);
}

/*
 * アイテムが一個ずつあるナップサック問題を解く
 * 価値の合計と入れるアイテムのリストを返す
 */
pair<Value, vector<int> > knapsack_single(const Items& items, const int volume) {
    const int nItems = items.size();

    vector< pair<Value,int> > table0, table(volume+1, make_pair(0, -1));

    for(int i = nItems-1; i >= 0; i--) {
        table0 = table;
        const Item& item = items[i];
        for(int v = item.volume; v <= volume; v++) {
            if (table[v].first < table0[v-item.volume].first + item.value) {
                table[v].first = table0[v-item.volume].first + item.value;
                table[v].second = i;
            }
        }
    }

    Value best_value = table[volume].first;
    vector<int> knapsack;
    for(int v = volume; table[v].second >= 0; v -= items[table[v].second].volume) {
        knapsack.push_back(table[v].second);
    }

    return make_pair(best_value, knapsack);
}


#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector< std::vector<int> > links_type;

bool find_path(const links_type& links, std::vector<int>& route, int goal) {
    int pos = route.back();
    int prev = (route.size() >= 2 ? route[route.size()-2] : -1);
    if (pos == goal)
        return true;
    for(int i=0; i<links[pos].size(); i++) {
        if (i == prev) continue;
        if (links[pos][i] != INF) {
            route.push_back(i);
            if (find_path(links, route, goal))
                return true;
            route.pop_back();
        }
    }
    return false;
}


int main() {

    int nCases;
    std::cin >> nCases;

    for(int iCase=0; iCase<nCases; iCase++) {

        int nNodes, nLinks;
        std::cin >> nNodes >> nLinks;

        links_type links(nNodes, std::vector<int>(nNodes, INF));

        for(int i=0; i<nLinks; i++) {
            int a, b, d;
            std::cin >> a >> b >> d;
            a--; b--;
            links[a][b] = d;
            links[b][a] = d;
        }

        int nTests;
        std::cin >> nTests;

        if (iCase > 0)
            std::cout << std::endl;

        for(int iTest=0; iTest<nTests; iTest++) {

            int start, goal, total;
            std::cin >> start >> goal >> total;
            start--; goal--;

            std::vector<int> route;
            route.push_back(start);
            find_path(links, route, goal);

            std::vector<int> loops;
            for(int i=0; i+2<route.size(); i++) {
                loops.push_back( links[route[i]][route[i+1]] * 2 );
            }

            int min_dist = 0;
            for(int i=0; i+1<route.size(); i++) {
                min_dist += links[route[i]][route[i+1]];
            }

            int dist_limit = total - min_dist;
            if (dist_limit < 0 || dist_limit%2 != 0) {
                std::cout << "No" << std::endl;
            }
            else if (dist_limit == 0) {
                std::cout << "Yes " << (route.size()-1) << std::endl;
            }
            else {
                Items items(loops.size());
                for(int i = 0; i < (int)items.size(); i++) {
                    items[i].volume = loops[i];
                    items[i].value = 1;
                }
                pair<Value, vector<int> > result = knapsack(items, dist_limit);
                if (!result.second.empty()) {
                    std::cout << "Yes " << (route.size()-1+result.first*2) << std::endl;
                }
                else {
                    std::cout << "No" << std::endl;
                }
            }

        }

    }

    return 0;
}
