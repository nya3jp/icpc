#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <numeric>
#include <complex>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

//////////////////////////////////////////////////////////////////////////// Library
#define REP(i,n) for(int i = 0; i < (int)(n); i++)
#define FOR(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define ALLOF(c) ((c).begin()), ((c).end())
#define AT(bits,pos) (((bits)>>(pos))&1)
template<class T> inline bool IN(const T& a, const T& low, const T& high) {
    return (low <= a && a < high);
}
//////////////////////////////////////////////////////////////////////////// End


struct $CLASSNAME$ {

    $RC$ $METHODNAME$($METHODPARMS$) {
        $RC$ res;

        // May fate be with you!

        return res;
    }

$WRITERCODE$
};







$BEGINCUT$
//////////////////////////////////////////////////////////////////////////////////////
#define ARRSIZE(x) (sizeof(x)/sizeof((x)[0]))
template<typename T> void print(const T& a) {cerr << a;}
template<> void print<long long>(const long long& a) {cerr << a << "L";}
template<> void print<string>(const string& a) {cerr << '"' << a << '"';}
template<typename T> void print(const vector<T>& a) {
cerr<<"{";for(int i=0;i!=a.size();i++){if(i!=0)cerr<<", ";print(a[i]);}cerr<<"}\n";}
template<typename T> void eq(int n,const T& a,const T& b){
cerr<<"Case "<<n<<" ";if(a==b){cerr<<"passed.\n";}else{cerr<<"failed: expected ";
print(b);cerr<<" received ";print(a);cerr << ".\n";}}
void eq(int n,const string& a,const string& b){
cerr<<"Case "<<n<<" ";if(a==b){cerr<<"passed.\n";}else{cerr<<"failed: expected ";
print(b);cerr<<" received ";print(a);cerr << ".\n";}}
template<class T> void eq(int n,const vector<T>& a,const vector<T>& b){
cerr<<"Case "<<n<<" ";if(a.size()!=b.size()){cerr<<"failed: returned "<<a.size()
<<" elements; expected "<<b.size()<<" elements.\n";print(a);print(b);return;}
for(int i=0;i!=a.size();i++){if(a[i]!=b[i]){cerr<<"failed. Expected and returned "
"array differ in position "<<i<<".\n";print(a);print(b);return;}}cerr<<"passed.\n";}

int main( int argc, char* argv[] ) {
$MAINBODY$
    return 0;
}
$ENDCUT$

// Powered by fate testarossa
