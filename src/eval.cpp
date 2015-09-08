//attempt on evaluation function using the largest palindrome that the adde chip could use
#include <iostream>
#include <stdlib.h>
using namespace std;

char ** board;
int boardSize;
int * maxPalindromeLength;
int* start, *end;
int chips;

char* preprocess(bool row,int idx){
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

int maxPalin(bool row,int idx,int cno){
  char* temp =  new char [2*boardSize+1];
  temp = preprocess(row,idx);
  int* arr = new int [2*boardSize+1];
  int c=0,r=0;
  for(int i=0;i<2*boardSize;i++){
    int irev = 2*c-i;
    arr[i] = (r>i) ? min(r-i,arr[irev]) : 0;
    while(temp[i+1+arr[i]]==temp[i-1-arr[i]]) arr[i]++;
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
  if (row){
    start[cno] = (cen-1-max)/2;
    end[cno] = (cen-1+max)/2;
  }
  else{
    start[cno+chips] = (cen-1-max)/2;
    end[cno+chips] = (cen-1+max)/2;
  }
  return max;
}

int main(){
  cin>>boardSize;
  //relaxman
  chips = 0;
  srand(time(NULL));
  end = new int [boardSize];
  start = new int [boardSize];
  board = new char * [boardSize];
  for (int i= 0;i<boardSize;i++){
    board[i] = new char [boardSize];
  }
  char color [] = {'A','B','C','D','E','F','G'};
  for(int i=0;i<boardSize;i++){
    for(int j=0;j<boardSize;j++){
      board[i][j] = color[rand()%boardSize];
      cout<<board[i][j];
      if(j!=boardSize-1){
        cout<<" ";
      }
    }
    cout<<'\n';
  }
  cout<<maxPalin(0,2,0)<<endl;
  cout<<start[0]<<' '<<end[0]<<" here\n"<<endl;
  return 0;
}
