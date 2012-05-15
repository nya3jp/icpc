/*
 * UVA 136 Ugly Numbers
 * 2005-09-15
 * by nya
 */

#include <queue>
#include <iostream>
#include <vector>
#include <functional>
#include <set>

#define N 1500

typedef long long int integer;

int main() {
    std::priority_queue<integer, std::vector<integer>, std::greater<integer> > q;
    std::set<integer> s;
    q.push(1);
    s.insert(1);
    for(int i=0; i<N-1; i++) {
        integer v = q.top();
        q.pop();
        if (s.insert(v*2).second)
            q.push(v*2);
        if (s.insert(v*3).second)
            q.push(v*3);
        if (s.insert(v*5).second)
            q.push(v*5);
    }
    std::cout << "The 1500'th ugly number is "
              << q.top()
              << "."
              << std::endl;
    return 0;
}
