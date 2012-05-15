#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const long double EP = 1.0e-10;
inline bool LS(long double a, long double b) {
  return (a < b-EP);
}

const int STONE_MAX = 6;
int nStones;
//int gd_nTrees;

int weight[STONE_MAX];
int weightSum;
//int nFilled;

//double stonePos[STONE_MAX];
//double widthLimit;
//double result;

typedef pair<long double, long double> doublepair;

int sumWeight(const vector<int> &v)
{
  int sum = 0;
  for(int i = 0; i < (int)v.size(); i++)
    sum += weight[v[i]];
  return sum;
}

/*
void calculateWidth()
{
  double minimum = 0.0, maximum = 0.0;
  for(int i = 0; i < nStones; i++) {
    minimum = min(minimum, stonePos[i]);
    maximum = max(maximum, stonePos[i]);
  }
  double width = maximum - minimum;
  if(width < widthLimit)
    result = max(result, width);
}
*/

std::vector<doublepair> makeTree2(const vector<int>& usableStones, long double center) {
  std::vector<doublepair> ranges;
  if(usableStones.size() == 1) {
    ranges.push_back( std::make_pair(center, center) );
    return ranges;
  }

  for(int i = 1; i <= (int)usableStones.size()-1; i++) {

    vector<int> vLeft;
    vector<int> vRight;

    vLeft.resize(i);
    vRight.resize(usableStones.size() - i);

    copy(usableStones.begin(), usableStones.begin() + i, vLeft.begin());
    copy(usableStones.begin() + i, usableStones.end(), vRight.begin());

    int leftSum = sumWeight(vLeft);
    int rightSum = sumWeight(vRight);

    long double massCenter = (long double)rightSum / (leftSum + rightSum);

    std::vector<doublepair> tleft = makeTree2(vLeft, center - massCenter);
    std::vector<doublepair> tright = makeTree2(vRight, center + 1.0 - massCenter);
    for(int i=0; i<(int)tleft.size(); i++) {
      for(int j=0; j<(int)tright.size(); j++) {
	ranges.push_back( std::make_pair(std::min(tleft[i].first, tright[j].first),
					 std::max(tleft[i].second, tright[j].second) ) );
      }
    }
  }
  return ranges;
}

/*
void makeTree(const vector<int> &usableStones, double pos)
{
  const int nFilled_backup = nFilled;

  if(usableStones.size() == 1) {
    stonePos[usableStones[0]] = pos;
    nFilled++;
    if(nFilled == nStones) {
      gd_nTrees++;
      calculateWidth();
    }
    return;
  }

  for(int i = 1; i <= usableStones.size()-1; i++) {

    nFilled = nFilled_backup;

    vector<int> vLeft;
    vector<int> vRight;

    vLeft.resize(i);
    vRight.resize(usableStones.size() - i);

    copy(usableStones.begin(), usableStones.begin() + i, vLeft.begin());
    copy(usableStones.begin() + i, usableStones.end(), vRight.begin());

    int leftSum = sumWeight(vLeft);
    int rightSum = sumWeight(vRight);

    double massCenter = (double)rightSum / (leftSum + rightSum);

    makeTree(vLeft, pos - massCenter);
    makeTree(vRight, pos + 1.0 - massCenter);
  }
}
*/

int main()
{
  ifstream fin("E.txt");

  int nCases;
  fin >> nCases;

  for(int iCase = 0; iCase < nCases; iCase++) {

    //gd_nTrees = 0; // for debug

    long double widthLimit;
    fin >> widthLimit;

    fin >> nStones;
    weightSum = 0;
    for(int i = 0; i < nStones; i++) {
      fin >> weight[i];
      weightSum += weight[i];
    }

    vector<int> usable;
    for(int i = 0; i < nStones; i++)
      usable.push_back(i);

    int dnTrees = 0;
    long double maximum = -100.0;
    do {
      //nFilled = 0;
      //result = -100.0;
      std::vector<doublepair> ranges = makeTree2(usable, 0.0);
      //std::cout << (int)ranges.size() << std::endl;
      dnTrees += ranges.size();
      for(int i=0; i<(int)ranges.size(); i++) {
	long double wid = ranges[i].second - ranges[i].first;
	//std::cout << "(" << ranges[i].first << "," << ranges[i].second << ")" << std::endl;
	if (LS(wid, widthLimit))
	  maximum = std::max(maximum, wid);
      }
      //maximum = max(maximum, result);
    } while(next_permutation(usable.begin(), usable.end()));

    //std::cout << dnTrees << ": "; // for debug

    if(LS(maximum, 0.0))
      cout << "-1" << endl;
    else
      printf("%.16Lf\n", maximum);
  }
  

  return 0;
}
