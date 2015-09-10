#include <iostream>
#include <stdlib.h>
#include <random>
#include <chrono>
#include <map>
#include "class1.cpp"
using namespace std;

struct key {
  float score;
  int depth;
};
// -std=c++0x
char color [] = {'A','B','C','D','E','F','G','-'};
map<char,int> key;
// int** board;
long long ** hashvals;

void init_zobrist(){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  mt19937 gen(seed);
  hashvals = new long long* [boardSize*boardSize];
  for(int i=0;i<boardSize*boardSize;i++){
    hashvals[i] = new long long [boardSize];
  }
  for(int i=0;i<boardSize;i++){
    for(int j=0;j<boardSize;j++){
      for(int k=0;k<boardSize;k++){
        hashvals[i*boardSize+j][k] = gen();
      }
    }
  }
}

long long hashval(int** state){
  long long h = 0;
  for(int i=0;i<boardSize;i++){
    for(int j=0;j<boardSize;j++){
      for(int k=0;k<boardSize;k++){
        h ^= hashvals[i*boardSize+j][state[i][j]];
      }
    }
  }
  return h;
}

long long hashChaos(long long val,int x,int y,int chip){
  val^=hashvals[x*boardSize+y][0]^hashvals[x*boardSize+y][chip];
  // board[x][y] = chip;
  return val;
}

long long hashOrd(int** state ,long long val,int x1,int x2,int y1,int y2){
  val^=hashvals[x1*boardSize+y1][state[x1][y1]]^hashvals[x2*boardSize+y2][0]^hashvals[x1*boardSize+y1][0]^hashvals[x2*boardSize+y2][state[x1][y1]];
  // board[x2][y2] = board[x1][y1];
  // board[x1][y2] = -1;
  return val;
}

// int main(){
//   srand(time(NULL));
//   key['-'] = -1;
//   key['A'] = 0;
//   key['B'] = 1;
//   key['C'] = 2;
//   key['D'] = 3;
//   key['E'] = 4;
//   key['F'] = 5;
//   key['G'] = 6;
//   cin>>boardSize;
//   board = new int* [boardSize];
//   for(int i=0;i<boardSize;i++){
//     board[i] = new int [boardSize];
//   }
//   for(int i=0;i<boardSize;i++){
//     for(int j=0;j<boardSize;j++){
//       board[i][j] = key[color[rand()%(boardSize+1)]];
//       cout<<board[i][j]<<' ';
//     }
//     cout<<endl;
//   }
//   init_zobrist();
//   long long h = hashval(board);
//   cout<<h<<endl;
//   int x,y,x1,y1;
//   cin>>x>>y>>x1>>y1;
//   cout<<hashOrd(h,x,y,x1,y1)<<endl;
//   for(int i=0;i<boardSize;i++){
//     for(int j=0;j<boardSize;j++){
//       cout<<board[i][j]<<' ';
//     }
//     cout<<endl;
//   }
// }
