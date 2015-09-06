#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

int boardSize;
char** board;

struct square{
	int x,y;
};

struct ordMove{
	square s1,s2;
};

void printBoard(){
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if (j!=boardSize-1){
				cerr<<board[i][j]<<" ";
			}
		}
		cerr<<'\n';
	}
}

bool gameOver(){
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j] == '-'){
				return false;
				cerr<<"done\n";
			}
		}
	}
	return true;
}

void chaos(){
	vector <square>* moves = new vector <square>;
	int s =0;
	char color;
	cin>>color;
	cerr<<"my color is"<<color<<endl;
	square pos;
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j] == '-'){
				pos.x = i;
				pos.y = j;
				moves->push_back(pos);
				s++;
			}
		}
	}
	int idx = rand()%s;
	cout<<moves->at(idx).x<<' '<<moves->at(idx).y<<endl;
	board[moves->at(idx).x][moves->at(idx).y] = color;
	cerr<<moves->at(idx).x<<' '<<moves->at(idx).y<<' '<<color<<endl;
}

int order(){
	vector <ordMove>* moves = new vector <ordMove>;
	int s =0;
	square pos1,pos2;
	ordMove o;
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j]!='-'){
				pos1.x = i;
				pos2.x = i;
				pos1.y = j;
				pos2.y = j;
				o.s1 = pos1;
				while(pos2.x != boardSize -1){
					pos2.x+=1;
					if(board[pos2.x][pos2.y]!='-') break;
					o.s2 = pos2;
					moves->push_back(o);
					s+=1;
				}
				pos2.x =i;
				while(pos2.x != 0){
					pos2.x-=1;
					if(board[pos2.x][pos2.y]!='-') break;
					o.s2 = pos2;
					moves->push_back(o);
					s+=1;
				}
				pos2.x =i;
				while(pos2.y != 0){
					pos2.y-=1;
					if(board[pos2.x][pos2.y]!='-') break;
					o.s2 = pos2;
					moves->push_back(o);
					s+=1;
					if (pos2.y<0) return -10;
				}
				pos2.y=j;
				while(pos2.y != boardSize){
					pos2.y+=1;
					if(board[pos2.x][pos2.y]!='-') break;
					o.s2 = pos2;
					moves->push_back(o);
					s+=1;
				}
				pos2.y = j;
			}
		}
	}
	if(s!=0){
		int idx = rand()%s;
		cout<<moves->at(idx).s1.x<<' '<<moves->at(idx).s1.y<<' '<<moves->at(idx).s2.x<<' '<<moves->at(idx).s2.y<<endl;
		board[moves->at(idx).s2.x][moves->at(idx).s2.y] = board[moves->at(idx).s1.x][moves->at(idx).s1.y];
		board[moves->at(idx).s1.x][moves->at(idx).s1.y] = '-';
	}
}

void updateChaos(){
	int x1,y1,x2,y2;
	cin>>x1>>y1>>x2>>y2;
	board[x2][y2] = board[x1][y1];
	board[x1][y1] = '-';
	printBoard();
}

void chaosPlayer(){
	bool run = 1;
	while(true){
		if(gameOver()){
			break;
		}
		if(run){
			cerr<<"im here\n";
			chaos();
			run=0;
		}
		if(!run){
			updateChaos();
			chaos();
		}
	}
}

void orderPlayer(){
	while(1){
		if (gameOver()){
			break;
		}
		int x1,y1;
		char c;
		cin>>x1>>y1>>c;
		board[x1][y1] = c;
		order();
	}
}

int main(){
	srand(time(NULL));
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
	if (role == "ORDER"){
		orderPlayer();
	}
	else chaosPlayer();
	return 0;
}
