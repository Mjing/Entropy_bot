#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <map>

using namespace std;

int boardSize;
char** board;
map <char,int> colors;

void orderAI(){
  //assess board and do stuff
  while(1){
    //apply miniMax
    //cout moves as x1 y1 x2 y2 \n
  }
}

void chaosAI(){
  while(1){
    //miniMax
    //cout move as x y
  }
}

int main(){
  cin>>boardSize;
  board = new char* [boardSize];
  for(int i=0;i<boardSize;i++){
    board[i] = new char [boardSize];
  }
  for(int i=0;i<boardSize;i++){
    for(int j=0;j<boardSize;j++){
      board[i][j] = '-';
    }
  }
  string role;
  cin>>role;
  if(role == "ORDER") orderAI();
  else chaosAI();
  return 1;
}
