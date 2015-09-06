//attempt on evaluation function using the largest palindrom that the adde chip could use
#include <iostream>
using namespace std;

char ** board;
int boardSize;
int * maxPalindromeLength;
int* start,end;
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
  else){
    start[cno+chips] = (cen-1-max)/2;
    end[cno+chips] = (cen-1+max)/2;
  }
  return max;
}
