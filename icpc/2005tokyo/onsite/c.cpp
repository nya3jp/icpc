#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <cassert>

// Dice Library

const int DICE_PRIM[24] = {
  1, 2, 4, 5,
  2, 0, 5, 3,
  4, 0, 1, 3,
  1, 5, 4, 2,
  0, 2, 3, 5,
  0, 4, 3, 1,
};

int DICE_ROTATE[24][6];

void init_dice() {
  for(int t=0; t<6; t++) {
    for(int r=0; r<4; r++) {
      int (&v)[6] = DICE_ROTATE[t*4+r];
      v[0] = t;
      v[1] = DICE_PRIM[t*4+r];
      v[2] = DICE_PRIM[t*4+(r+1)%4];
      v[3] = (v[0]+3)%6;
      v[4] = DICE_PRIM[t*4+(r+2)%4];
      v[5] = DICE_PRIM[t*4+(r+3)%4];
    }
  }
}


struct Dice {
  int face[6];
  Dice rotate(int r) const {
    assert(0 <= r && r < 24);
    Dice d;
    for(int i=0; i<6; i++)
      d.face[i] = face[DICE_ROTATE[r][i]];
    return d;
  }
};




int solve(int iDice, int nDices, std::vector<int>& rotate, const Dice* _dices) {
  int nPaints = std::numeric_limits<int>::max();
  if (iDice < nDices) {
    for(int i=0; i<24; i++) {
      rotate[iDice] = i;
      nPaints = std::min(nPaints, solve(iDice+1, nDices, rotate, _dices));
    }
  }
  else {
    // iDice == nDices
    Dice dices[4];
    for(int i=0; i<nDices; i++)
      dices[i] = _dices[i].rotate(rotate[i]);
    nPaints = 0;
    for(int iFace=0; iFace<6; iFace++) {
      std::map<int,int> m;
      for(int i=0; i<nDices; i++)
	m[ dices[i].face[iFace] ]++;
      int nFacePaints = std::numeric_limits<int>::max();
      for(std::map<int,int>::const_iterator it = m.begin(); it != m.end(); ++it) {
	nFacePaints = std::min(nFacePaints, (nDices - it->second));
      }
      nPaints += nFacePaints;
    }
  }
  return nPaints;
}

int main() {
  std::ifstream fin("C.txt");

  init_dice();

  std::map<std::string, int> colorToId;

  int n;
  while(fin >> n && n != 0) {
    assert(0 < n && n <= 4);
    Dice dices[4];
    const int DICE_PLACE_MAP[] = {1, 2, 0, 3, 5, 4};
    for(int i=0; i<n; i++) {
      for(int j=0; j<6; j++) {
	std::string s;
	fin >> s;
	if (colorToId.find(s) == colorToId.end()) {
	  colorToId.insert( std::make_pair(s, (int)colorToId.size()) );
	}
	int colorId = colorToId[s];
	dices[i].face[ DICE_PLACE_MAP[j] ] = colorId;
      }
    }

    std::vector<int> rotate(n, 0);
    std::cout << solve(1, n, rotate, dices) << std::endl;
  }

  return 0;
}
