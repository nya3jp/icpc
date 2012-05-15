#include <iostream>
#include <string>

using namespace std;

int pow(int e, int n) {
    int t = 1;
    while(n-- > 0)
        t *= e;
    return t;
}

void cantor(int order) {
    if (order == 0) {
        cout << '-';
    }
    else {
        cantor(order-1);
        cout << string(pow(3, order-1), ' ');
        cantor(order-1);
    }
}

int main() {
    for(int order; cin >> order; ) {
        cantor(order);
        cout << endl;
    }
    return 0;
}
