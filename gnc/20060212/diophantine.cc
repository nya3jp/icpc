/**
 * @file
 * ”—:Œİœ–@‚È‚Ç
 */

#include <utility>

using namespace std;

typedef long long int integer;

/// Šg’£EuclidŒİœ–@
/**
 * @return a*pair.first + b*pair.second == gcd(a, b)
 */
pair<integer,integer> xgcd(integer a, integer b) {
    if (b == 0)
        return make_pair(1, 0);
    pair<integer,integer> p = xgcd(b, a%b);
    return make_pair(p.second, p.first - (a/b)*p.second);
}

/// Å‘åŒö–ñ”
integer gcd(integer a, integer b) {
    while(b != 0) {
        integer r = a%b;
        a = b;
        b = r;
    }
    return a;
}



struct no_solution {};

/// a*n = b (mod m) ‚Æ‚È‚éA”ñ•‰‚Å‚©‚ÂÅ¬‚Ìn‚ğ‹‚ß‚é
/**
 * @note
 * ‰ğ‚ª‚È‚¢ê‡‚Ístruct no_solution‚ğthrow‚·‚é
 */
integer divide(integer a, integer b, integer m) {
    integer g = gcd(a, m);
    if (b%g != 0)
        throw no_solution();
    pair<integer,integer> p = xgcd(a, m);
    assert(p.first*a+p.second*m == gcd(a,m));
    integer n = p.first*b/g;
    integer dn = m/g;
    n -= n/dn*dn;
    if (n < 0)
        n += dn;
    return n;
}
