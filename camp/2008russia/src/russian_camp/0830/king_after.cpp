
#include <iostream>
#include <cstdio>
#include <complex>
#include <cstring>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); i++)

#define PROBLEM_NAME "king"

#define N 500

char field[2*N+10][2*N+10];
int h;
int w;

void draw_outline_even(bool odd) {
  REP(i, 2*h-1) REP(j, 2*w-1)
    field[i][j] = ' ';
  REP(i, h) REP(j, w)
    field[2*i][2*j] = 'o';

  REP(j, w/2){
    field[0][4*j+1] = '-';
    field[2*h-2][2*w-2-(4*j+1)] = '-';
  }

  REP(j, w-2){
    field[1][2*j] = '|';
    field[2*h-3][2*w-2-2*j] = '|';
  }
  field[1][2*w-5] = '/';
  field[2*h-3][3] = '/';

  REP(j, w/2-2){
    field[2][4*j+3] = '-';
    field[2*h-4][2*w-2-(4*j+3)] = '-';
  }
  

  REP(i, h/2){
    field[4*i+1][0] = '|';
    field[4*i+1][2*w-2] = '|';
  }
  
  REP(i, h){
    field[2*i][1] = '-';
    field[2*i][2*w-3] = '-';
  }

  REP(i, h/2-1){
    field[4*i+3][2] = '|';
    field[4*i+3][2*w-4] = '|';
  }
  
  field[3][1] = '\\';
  field[2][1] = ' ';
  field[3][2] = ' ';
  field[2*h-5][2*w-3] = '\\';
  field[2*h-5][2*w-4] = ' ';
  field[2*h-4][2*w-3] = ' ';
  
  if(odd){
    field[0][2*w-2-3] = ' ';
    field[1][2*w-2-5] = '/';
    field[2*h-2][3] = ' ';
    field[2*h-2-1][5] = '/';
  }
}

inline void drawHoge(int i, int j) {
  field[2*i-1][2*j-1] = '\\';
  field[2*i-2][2*j-1] = ' ';
  field[2*i-1][2*j+1] = '\\';
  field[2*i+1][2*j] = '|';
  field[2*i+2][2*j+1] = '-';
  field[2*i+1][2*j+2] = '|';
}

void flip() {
  REP(i, 2*N+5) REP(j, i)
    swap(field[i][j], field[j][i]);
  REP(i, 2*N+5) REP(j, 2*N+5)
    switch(field[i][j]){
    case '-': field[i][j] = '|'; break;
    case '|': field[i][j] = '-'; break;
    default: break;
    }
}

void draw_even() {
  if(h % 2 == 1){
    swap(h, w);
    draw_even();
    flip();
    swap(h, w);
    return;
  }
  
  bool isOdd = (w % 2 == 1);
  draw_outline_even(isOdd);
  
  if(h == 4 || w == 4)
    return;

  // inside
  REP(j, w/2-2)
    drawHoge(2, 2*j+2);
  if(isOdd){
    field[3][2*w-4] = ' ';
    field[3][2*w-5] = '/';
    field[5][2*w-6] = '|';
    field[5][2*w-5] = '/';
  }
  
  for(int i = 4; i < h - 2; i += 2){
    
    field[2*i+3][2] = ' ';
    field[2*i+3][3] = '/';
    field[2*i+1][4] = '|';
    field[2*i+1][3] = '/';

    if(!isOdd){
      field[2*i-1][2*w-4] = ' ';
      field[2*i-1][2*w-5] = '/';
      field[2*i+1][2*w-6] = '|';
      field[2*i+1][2*w-5] = '/';
    }
    for(int j = 3; j + 1 < w - 2; j+= 2)
      drawHoge(i, j);

    i += 2;
    if(i >= h - 2)
      break;
    
    if(isOdd){
      field[2*i-1][2*w-4] = ' ';
      field[2*i-1][2*w-5] = '/';
      field[2*i+1][2*w-6] = '|';
      field[2*i+1][2*w-5] = '/';
    }

    for(int j = 4; j + 1 < w - 2; j+= 2)
      drawHoge(i, j);

    if(w != 5){
      field[2*i+1][3] = '/';
      field[2*i][5]   =  '-';
      field[2*i+1][6] =   '|';
      field[2*i+2][5] =  '-';
      field[2*i+3][3] = '/';
      field[2*i+3][2] = ' ';
    }
    
  }
}

void draw_odd() {
  if(h > w){
    swap(h, w);
    draw_odd();
    flip();
    swap(h, w);
    return;
  }
    
  REP(i, 2*h-1) REP(j, 2*w-1)
    field[i][j] = ' ';
  REP(i, h) REP(j, w)
    field[2*i][2*j] = 'o';
  // side
  REP(i, h/2){
    field[4*i+3][0] = '|';
    field[4*i+1][2*w-2] = '|';
  }
  field[1][1] = '\\';
  field[2*h-3][1] = '/';
  field[2*h-5][1] = '/';
  field[1][2*w-3] = '/';
  field[3][2*w-3] = '/';
  field[2*h-3][2*w-3] = '\\';
  REP(i, h-2){
    field[2*i][1] = '-';
    field[2*h-2-2*i][2*w-3] = '-';
  }
  REP(i, h/2-2){
    field[4*i+5][2] = '|';
    field[2*h-7-4*i][2*w-4] = ' ';
    field[2*h-7-4*i][2*w-5] = '\\';
    field[2*h-7-4*i-2][2*w-6] = '|';
    field[2*h-7-4*i-2][2*w-5] = '\\';
    
  }

  REP(j, w/2){
    field[0][4*j+1] = '-';
    field[2*h-2][4*j+3] = '-';
  }
  REP(j, w-4)
    field[2*h-3][2*j] = '|';
  field[2*h-3][2*w-5] = '\\';
  field[2*h-3][2*w-7] = '\\';
  field[2*h-3][2*w-9] = '\\';
  REP(j, w/2-3)
    field[2*h-4][4*j+5] = '-';
  field[2*h-5][2*w-7] = '/';
  field[2*h-5][2*w-6] = '|';
  
  
  REP(j, w / 2 - 2)
    drawHoge(1, 2*j+2);
  field[0][2*w-9] = '-';
  field[1][2*w-7] = '\\';
  field[1][2*w-6] = '|';
  field[0][2*w-5] = '-';
  field[1][2*w-4] = '|';

  if(h == 5 || w == 5)
    return;
  
  for(int i = 3; i < h - 2; i += 2){
    
    field[2*i-1][2] = ' ';
    field[2*i-1][3] = '\\';
    field[2*i+1][4] = '|';
    field[2*i+1][3] = '\\';

    for(int j = 3; j + 1 < w - 3; j+= 2)
      drawHoge(i, j);

    field[2*i-1][2*w-6] = ' ';
    field[2*i-1][2*w-7] = '/';
    field[2*i+1][2*w-8] = '|';
    field[2*i+1][2*w-7] = '/';

    i += 2;
    if(i >= h - 2)
      break;
    

    for(int j = 4; j + 1 < w - 3; j+= 2)
      drawHoge(i, j);

    field[2*i-1][5] =   '/';
    field[2*i+1][4] = '|';
    field[2*i+2][5] =  '-';
    field[2*i+1][6] =   '|';
    field[2*i][7] =      '-';
    field[2*i-1][7] =   ' ';
    
  }
  
}

bool draw() {
  if(h == 2 && w == 2){
    strcpy(field[0], "o-o");
    strcpy(field[1], "| |");
    strcpy(field[2], "o-o");
    return true;
  }
  if(h == 2 || w == 2)
    return false;
  if(h == 3 || w == 3)
    return false;
  if(h == 5 && w == 5)
    return false;

  if(h % 2 == 0 || w % 2 == 0){
    draw_even();
    return true;
  }
  
  // odd * odd
  draw_odd();

  return true;
}

int main() {

  if (!freopen(PROBLEM_NAME ".in", "r", stdin))
    abort();
  if (!freopen(PROBLEM_NAME ".out", "w", stdout))
    abort();

  cin >> h >> w;
  
  bool res = draw();

  if(!res){
    puts("No");
    return 0;
  }

  puts("Yes");
  REP(i, 2*h-1)
    puts(field[i]);
  
  return 0;
}

