/*
 * UVA 793 Network Connections
 * 2005-06-20
 * by nya and YAMA(main function)
 */

#include <algorithm>
#include <assert.h>

class UnionFinder {
private:
    int* data;
    int n;

public:
    UnionFinder(int n) : n(n) {
        data = new int[n];
        std::fill(data, data+n, -1);
    }
    ~UnionFinder() {
        delete[] data;
    }

public:
    void link(int a, int b) {
        union_find(a, b, true);
    }
    bool check(int a, int b) {
        return union_find(a, b, false);
    }

private:
    bool union_find(int a, int b, bool link) {
        int ra, rb;
        ra = find_root(a);
        rb = find_root(b);
        if (link && ra != rb) {
            assert(data[ra] < 0 && data[rb] < 0);
            if (data[ra] < data[rb]) { // ra tree is heavier
                data[ra] += data[rb];
                data[rb] = ra;
            }
            else {
                data[rb] += data[ra];
                data[ra] = rb;
            }
            //data[rb] = ra;
        }
        return (ra == rb);
    }

    int find_root(int a) {
        int ra;
        for(ra = a; data[ra] >= 0; ra = data[ra]);
        for(int ta = a; ta != ra; ) {
            int next = data[ta];
            data[ta] = ra;
            ta = next;
        }
        return ra;
    }
};



#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
  int nInputs, nNodes;
  char buf[100];

  fgets(buf, 100, stdin);
  sscanf(buf, "%d", &nInputs);
  fgets(buf, 100, stdin);
  for(int iInput=0; iInput<nInputs; iInput++) {
    // Initialize
    int successful = 0, unsuccessful = 0;

    // Input & Solve
    fgets(buf, 100, stdin);
    sscanf(buf, "%d", &nNodes);
    /*
    g_vParents.reserve(nNodes);
    for(int i=0; i<nNodes; i++)
      g_vParents.push_back(-1);
    */
    UnionFinder u(nNodes);
    
    while(true) {
      if(fgets(buf, 100, stdin) == NULL || strlen(buf) < 3)
	break;

      char command;
      int a, b;
      sscanf(buf, "%c %d %d", &command, &a, &b);
      a--; b--;
      if(command == 'c')
          u.link(a, b);//connect(a, b);
      else if(command == 'q') {
          if(u.check(a, b)/*isConnected(a, b)*/) successful++;
	else unsuccessful++;
      }
    }
    // Output
    if(iInput != 0)
      puts("");
    printf("%d,%d\n", successful, unsuccessful);
   }  
  return 0;
}
/*
int main() {

    bool first = true;

    {
        std::string s;
        std::getline(std::cin, s);
        std::getline(std::cin, s);
    }

    while(true) {
        int nNodes;

        char line[128];
        std::fgets(line, sizeof(line), stdin);
        std::sscanf(line, "%d", &nNodes);
        std::fgets(line, sizeof(line), stdin);
        if (std::feof(stdin))
            break;

        UnionFinder u(nNodes);

        int ans[2] = {0, 0};

        while(true) {
            std::fgets(line, sizeof(line), stdin);
            if (std::feof(stdin))
                break;

            char code;
            int a, b;
            if (std::sscanf(line, "%c %d %d", &code, &a, &b) < 3)
                break;

            a--; b--;

            if (code == 'c') {
                u.link(a, b);
            }
            else {
                ans[ u.check(a, b) ? 0 : 1 ]++;
            }
        }

        if (! first)
            std::cout << std::endl;
        std::cout << ans[0] << ',' << ans[1] << std::endl;
        first = false;
    }

    return 0;
}
*/
