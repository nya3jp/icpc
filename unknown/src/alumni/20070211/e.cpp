#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <complex>
#include <queue>
#include <deque>
#include <fstream>

#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define ALL(v)    (v).begin(), (v).end()

using namespace std;

ifstream fin("exchange.in");

#define cin fin

struct EntryBuy {
public:
    int id;
    unsigned int num;
    unsigned int price;
};

struct EntrySell {
public:
    int id;
    unsigned int num;
    unsigned int price;
};

bool operator<(const EntryBuy& a, const EntryBuy& b)
{
    if (a.price == b.price) {
        return a.id < b.id;
    }
    return a.price > b.price;
}

bool operator<(const EntrySell& a, const EntrySell& b)
{
    if (a.price == b.price) {
        return a.id < b.id;
    }
    return a.price < b.price;
}


int idCounter = 1;
int buy_num = 0;
int buy_price = 0;
int sell_num = 0;
int sell_price = 99999;

set<EntryBuy> pendingBuy;
set<EntrySell> pendingSell;

void quote(void)
{
    {
        int top_num = 0;
        int top_price = 0;

        if (!pendingBuy.empty()) {
            top_price = pendingBuy.begin()->price;

            set<EntryBuy>::iterator it  = pendingBuy.begin();
            set<EntryBuy>::iterator end = pendingBuy.end();
//            cout << " PENDING BUY!" << endl;

            for (; it != end; ++it) {
                /*
                cout << it->id << " ";
                cout << it->num << " ";
                cout << it->price << " ";
                cout << endl;
                */
                int iPrice = (*it).price;
                if (iPrice == top_price) {
                    top_num += (*it).num;
                }
            }
        }

        buy_num = top_num;
        buy_price = top_price;
    }

    {
        int top_num = 0;
        int top_price = 99999;

        if (!pendingSell.empty()) {
            top_price = pendingSell.begin()->price;
            set<EntrySell>::const_iterator it  = pendingSell.begin();
            set<EntrySell>::const_iterator end = pendingSell.end();
//            cout << " PENDING SELL! " << endl;
            for (; it != end; ++it) {
                /*
                cout << it->id << " ";
                cout << it->num << " ";
                cout << it->price << " ";
                cout << endl;
                */
                int iPrice = (*it).price;
                if (iPrice == top_price) {
                    top_num += (*it).num;
                }
            }
        }

        sell_num = top_num;
        sell_price = top_price;
    }
}

void buy(int num, int price)
{
//    cout << "BUY!" << num << ":" << price << endl;
    EntryBuy e;
    e.id = idCounter++;
    e.num = num;
    e.price = price;

    {
        set<EntrySell>::const_iterator it  = pendingSell.begin();
        set<EntrySell>::const_iterator end = pendingSell.end();
        for (; it != end;) {
            if (it->price <= e.price) {
                if (it->num > e.num) {
                    EntrySell e2;
                    e2.id = it->id;
                    e2.num = it->num - e.num;
                    e2.price = it->price;
                    cout << "TRADE " << e.num << " " << it->price << endl;
                    pendingSell.erase(it);
                    pendingSell.insert(e2);
                    e.num = 0;
                    quote();
                    return;
                } else {
                    cout << "TRADE " << it->num << " " << it->price << endl;
                    e.num -= it->num;
                    pendingSell.erase(it++);
                    if (e.num == 0)
                        break;
                }
            } else {
                ++it;
            }
        }
    }

    if (e.num > 0)
        pendingBuy.insert(e);

    quote();
}

void cancel(int id)
{
//    cout << "CANCEL!" << id << endl;
    idCounter++;

    set<EntryBuy>::const_iterator it  = pendingBuy.begin();
    set<EntryBuy>::const_iterator end = pendingBuy.end();
    for (; it != end; ++it) {
        if (it->id == id) {
            pendingBuy.erase(it);
            quote();
            return;
        }
    }

    set<EntrySell>::const_iterator it2  = pendingSell.begin();
    set<EntrySell>::const_iterator end2 = pendingSell.end();
    for (; it2 != end2; ++it2) {
        if (it2->id == id) {
            pendingSell.erase(it2);
            quote();
            return;
        }
    }
}

void sell(int num, int price)
{
//    cout << "SELL!" << num << ":" << price << endl;
    EntrySell e;
    e.id = idCounter++;
    e.num = num;
    e.price = price;

    {
        set<EntryBuy>::const_iterator it  = pendingBuy.begin();
        set<EntryBuy>::const_iterator end = pendingBuy.end();
        for (; it != end;) {
            if (it->price >= e.price) {
                if (it->num > e.num) {
                    EntryBuy e2;
                    e2.id = it->id;
                    e2.num = it->num - e.num;
                    e2.price = it->price;
                    cout << "TRADE " << e.num << " " << it->price << endl;
                    pendingBuy.erase(it);
                    pendingBuy.insert(e2);
                    e.num = 0;
                    quote();
                    return;
                } else {
                    cout << "TRADE " << it->num << " " << it->price << endl;
                    e.num -= it->num;
                    pendingBuy.erase(it++);
                    if (e.num == 0)
                        break;
                }
            } else {
                ++it;
            }
        }
    }

    if (e.num > 0)
        pendingSell.insert(e);

    quote();
}

int
main(void)
{
    int nCases;
    cin >> nCases;
    while (nCases--) {
        idCounter = 1;
        buy_num = 0;
        buy_price = 0;
        sell_num = 0;
        sell_price = 99999;
        pendingBuy.clear();
        pendingSell.clear();

        int nOps;
        cin >> nOps;
        while (nOps--) {
            string op_str;
            cin >> op_str;

            if (op_str == "BUY") {
                int num, price;
                cin >> num;
                cin >> price;
                buy(num, price);
            } else if (op_str == "CANCEL") {
                int id;
                cin >> id;
                cancel(id);
            } else if (op_str == "SELL") {
                int num, price;
                cin >> num;
                cin >> price;
                sell(num, price);
            }

            cout << "QUOTE " << buy_num << " " << buy_price << " - "
                 << sell_num << " " << sell_price << endl;
        }
    }
}