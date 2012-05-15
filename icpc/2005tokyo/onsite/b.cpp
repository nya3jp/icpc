#define NDEBUG

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <utility>
#include <iterator>



class Librarian {
private:
  std::vector< std::set<int> > desks;
  std::map<int,int> history;
  int iTotalCost;
  int iTime;
  const int nDesks, nCapacity;

public:
  Librarian(int nDesks, int nCapacity)
    : desks(nDesks), history(), iTotalCost(0), iTime(0), nDesks(nDesks), nCapacity(nCapacity) {
  }
  ~Librarian() {
  }
  void removeBook(int id) {
    for(int iDesk=0; iDesk<nDesks; iDesk++) {
      if (desks[iDesk].erase(id) != 0) {
	iTotalCost += (iDesk+1);
	return;
      }
    }
    iTotalCost += (nDesks+1);
  }
  void placeBook(int id) {
    if (nDesks > 0 && (int)desks[0].size() == nCapacity) {

      // find the temporary desk
      int iDeskToTemp;
      for(iDeskToTemp=0; iDeskToTemp<nDesks; iDeskToTemp++) {
	if ((int)desks[iDeskToTemp].size()+1 <= nCapacity)
	  break;
      }

      // place the req book to temp desk
      putBook(iDeskToTemp, id);

      // find the least recently reqed book and pick it
      int idToMove = getLeastRecentBook();
      removeBook(idToMove);

      // place the book to another desk
      int iDeskToMove;
      for(iDeskToMove=1; iDeskToMove<nDesks; iDeskToMove++) {
	if ((int)desks[iDeskToMove].size()+1 <= nCapacity)
	  break;
      }
      putBook(iDeskToMove, idToMove);

      // pick the original book
      removeBook(id);
    }

    // put the book to desk0
    putBook(0, id);

    // update history
    history[id] = iTime;
    iTime++;
  }
  int getTotalCost() {
    return iTotalCost;
  }
private:
  void putBook(int iDesk, int id) {
    assert(0 <= iDesk && iDesk <= nDesks);
    if (iDesk < nDesks) {
      assert((int)desks[iDesk].size()+1 <= nCapacity);
      desks[iDesk].insert(id);
    }
    iTotalCost += iDesk+1; // cost
  }
  int getLeastRecentBook() {
    assert(! desks[0].empty()); // warning: really?
    std::pair<int,int> leastRecentBook(-1, std::numeric_limits<int>::max()); // pair<id, time>
    for(std::set<int>::const_iterator it = desks[0].begin(); it != desks[0].end(); ++it) {
      int id = *it;
      assert(history.find(id) != history.end());
      if (history[id] < leastRecentBook.second)
	leastRecentBook = *history.find(id);
    }
    return leastRecentBook.first;
  }
};


int main() {

  std::ifstream fin("B.txt");

  int nDesks, nCapacity, nStudents;
  while(fin >> nDesks >> nCapacity >> nStudents && !(nDesks == 0 && nCapacity == 0 && nStudents == 0)) {

    // Input

    std::vector<int> requests;

    {
      int nTotalRequests = 0;
      std::vector< std::deque<int> > q(nStudents);
      for(int i=0; i<nStudents; i++) {
	int nRequests;
	fin >> nRequests;
	nTotalRequests += nRequests;
	for(int j=0; j<nRequests; j++) {
	  int id;
	  fin >> id;
	  q[i].push_back(id);
	}
      }
      for(int iRequest=0; iRequest<nTotalRequests; ) {
	for(int i=0; i<nStudents; i++) {
	  if (! q[i].empty()) {
	    requests.push_back(q[i].front());
	    q[i].pop_front();
	    iRequest++;
	  }
	}
      }
    }

    /*
    std::copy(requests.begin(), requests.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    */

    // Input End

    // Start Simulation

    Librarian lib(nDesks, nCapacity);

    for(int iRequest=0; iRequest<(int)requests.size(); iRequest++) {
      int id = requests[iRequest];
      lib.removeBook(id);
      lib.placeBook(id);
    }

    // End Simulation

    std::cout << lib.getTotalCost() << std::endl;

  }


  return 0;
}
