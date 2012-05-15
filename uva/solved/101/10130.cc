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

    vector< pair<Value,int> > table(volume+1, make_pair(0, -1));

    for(int i = nItems-1; i >= 0; i--) {
        const Item& item = items[i];
        for(int v = item.volume; v <= volume; v++) {
            if (table[v].first < table[v-item.volume].first + item.value) {
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

void solve() {
    int n;
    cin >> n;
    Items items(n);
    for(int i = 0; i < n; i++) {
        Item& a = items[i];
        cin >> a.value >> a.volume;
    }
    int sum = 0;
    int m;
    cin >> m;
    for(int i = 0; i < m; i++) {
        int c;
        cin >> c;
        sum += knapsack_single(items, c).first;
    }
    cout << sum << endl;
}


int main() {
    int n;
    cin >> n;
    while(n-- > 0)
        solve();
    return 0;
}
