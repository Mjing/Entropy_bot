//attempt on evaluation function using the largest palindrome that the adde chip could use
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

char ** board;
int boardSize;
int* start, *end;
int chips;
struct change{
  int x , y;
};

char* preprocess(bool row,int idx,char** board,int boardSize){
  char * temp = new char [2*boardSize+1];
  if (row){
    for(int i=0;i<boardSize;i++){
      temp[2*i] = '#';
      temp[2*i+1] = board[idx][i];
    }
    temp[2*boardSize] = '#';
  }
  else{
    for(int i=0;i<boardSize;i++){
      temp[2*i] = '#';
      temp[2*i+1] = board[i][idx];
    }
    temp[2*boardSize] = '#';
  }
  return temp;
}

change maxPalin(bool row,int idx,char** board,int boardSize){
  char* temp =  new char [2*boardSize+1];
  temp = preprocess(row,idx,board,boardSize);
  int* arr = new int [2*boardSize+1];
  int c=0,r=0;
  for(int i=0;i<2*boardSize;i++){
    int irev = 2*c-i;
    arr[i] = (r>i) ? min(r-i,arr[irev]) : 0;
    while(temp[i+1+arr[i]]==temp[i-1-arr[i]]){
      arr[i]++;
    }
    if(i+arr[i]>r){
      c=i;
      r=i+arr[i];
    }
  }
  int max=0;
  int cen=0;
  for(int i=0;i<2*boardSize;i++){
    if(arr[i]>max){
      max = arr[i];
      cen = i;
    }
  }
  delete [] arr;
  delete [] temp;
  change ch;
  ch.x = (cen+1-max)/2;
  ch.y = max;
  //if (row) cout<<max<<"  "<<ch.y<<"here\n";
  //if (row) cout<<(cen+1-max)/2<<' '<<idx<<" "<<max<<"here\n";
  return ch;
}

vector<change>* possibleMoves(char** board,int boardSize){
  vector<change>* ans = new vector<change>;
  change c;
  for(int i=0;i<boardSize;i++){
    for(int j=0;j<boardSize;j++){
      if (board[i][j] == '-'){
        c.x = i;
        c.y = j;
        ans->push_back(c);
      }
    }
  }
  return ans;
}

float evalfn1(char** board,int boardSize){
  vector<change>* a = new vector<change>;
  a = possibleMoves(board,boardSize);
  int n = a->size();
  float * possible = new float [2*n];
  change c,d;
  float score;
  for(int i=0;i<2*n;i++){
    c = a->at(i/2);
    if(i%2 == 0){
      cout<<i/2<<endl<<endl;
      d.x = maxPalin(1,c.x,board,boardSize).x;
      d.y = maxPalin(1,c.x,board,boardSize).y;
      int count = 0;
      for(int i=0;i<d.y;i++){
        if(board[c.x][i+d.x] == '-') count++;
      }
      score = (d.y)*pow(.142857,count);
      cout<<d.y<<' '<<count<<endl;
    }
    else{
      d = maxPalin(0,c.y,board,boardSize);
      int count = 0;
      for(int i=0;i<d.y;i++){
        if(board[i+d.x][c.y] == '-') count++;
      }
      score = (d.y)*pow(.142857,count);
      cout<<d.y<<' '<<count<<endl;
    }
    possible[i] = score;
  }
  sort(possible,possible+2*n);
  float ans = 0;
  if(n>4){
    for(int i=0;i<8;i++){
      ans+=possible[2*n-i-1];
    }
  }
  else{
    for(int i=0;i<2*n;i++){
      ans+=possible[i];
    }
  }
  return ans;
}

int main(){
  int boardSize;
  cin>>boardSize;
  //relaxman
  chips = 0;
  srand(time(NULL));
  end = new int [boardSize];
  start = new int [boardSize];
  char ** board = new char * [boardSize];
  for (int i= 0;i<boardSize;i++){
    board[i] = new char [boardSize];
  }
  char color [] = {'A','B','C','D','E','F','G','-'};
  for(int i=0;i<boardSize;i++){
    for(int j=0;j<boardSize;j++){
      board[i][j] = color[rand()%(boardSize+1)];
      //board[i][j] = '-';
      cout<<board[i][j];
      if(j!=boardSize-1){
        cout<<" ";
      }
    }
    cout<<'\n';
  }
  cout<< evalfn1(board,boardSize);
  return 0;
}
