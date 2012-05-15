#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>

template<class T>
struct matrix {
  T* data;
  const int n, m;
  matrix(int n, int m, const T& def = T())
    : data(new T[n*m]), n(n), m(m) {
  }
  virtual ~matrix() {
    delete[] data;
  }
  T* operator[](int i) {
    return data+(i*m);
  }
  const T* operator[](int i) const {
    return data+(i*m);
  }
private:
  matrix(const matrix<T>&) {
  }
  matrix<T>& operator=(const matrix<T>&) {
    return 0;
  }
};

int main() {
  std::ifstream fin("F.txt");

  int nNodes;
  while(fin >> nNodes && nNodes != 0) {

    // Input
    nNodes++;
    std::vector<int> distances(nNodes);
    distances[0] = 0;
    for(int i=1; i<nNodes; i++)
      fin >> distances[i];
    double fPitinCost;
    int iLimitDistance;
    double fConstV, fConstE, fConstF;
    fin >> fPitinCost >> iLimitDistance >> fConstV >> fConstE >> fConstF;
    // Input End


    // Calculate Distance Matrix
    matrix<double> vvDistance(nNodes, nNodes); //(double)0.0 / 0.0); // warning

    for(int iFrom=0; iFrom<nNodes; iFrom++) {
      double fTravelCost = 0.0;
      int iPos = distances[iFrom];
      for(int iTo=iFrom+1; iTo<nNodes; iTo++) {
	while(iPos < distances[iTo]) {
	  int iRelPos = iPos - distances[iFrom];
	  if (iRelPos < iLimitDistance) {
	    fTravelCost += 1.0 / (fConstV - fConstF*(iLimitDistance - iRelPos));
	  }
	  else {
	    fTravelCost += 1.0 / (fConstV - fConstE*(iRelPos - iLimitDistance));
	  }
	  iPos++;
	}
	vvDistance[iFrom][iTo] = fTravelCost;
      }
    }
    // Calculate Distance Matrix End
    
    // Dynamic Programming

    std::vector<double> vBestPitin(nNodes);
    vBestPitin[0] = 0.0;
    for(int i=1; i<nNodes; i++) {
      double fTravelCost = std::numeric_limits<double>::max();
      for(int j=0; j<i; j++) {
	double fCost = vBestPitin[j] + vvDistance[j][i] + fPitinCost;
	fTravelCost = std::min(fTravelCost, fCost);
      }
      vBestPitin[i] = fTravelCost;
    }

    // Dynamic Programming End

    std::printf("%.4lf\n", vBestPitin[nNodes-1] - fPitinCost);

  }

  return 0;
}
