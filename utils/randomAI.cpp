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

bool check(){
	cout<<1;
	return 1;
}

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
	cout<<1;
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j] == '-'){
				return false;
				cout<<"done\n";
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
	cerr<<moves->at(idx).x<<' '<<moves->at(idx).y<<' '<<color<<endl;
}

int order(){
	vector <ordMove>* moves = new vector <ordMove>;
	int s =0;
	square pos1,pos2;
	ordMove o;
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			pos1.x = i;
			pos2.x = i+1;
			pos1.y = j-1;
			pos2.y = j;
			o.s1 = pos1;
			while(board[pos2.x][pos2.y] == '-' && pos1.x<boardSize){
				pos2.x+=1;
				o.s2 = pos2;
				moves->push_back(o);
				s+=1;
			}
			pos2.x = i-1;
			while(board[pos2.x][pos2.y] == '-' && pos1.x>=0){
				pos2.x-=1;
				o.s2 = pos2;
				moves->push_back(o);
				s+=1;
			}
			pos2.x =i;
			while(board[pos2.x][pos2.y] == '-'){
				pos2.y-=1;
				o.s2 = pos2;
				moves->push_back(o);
				s+=1;
				if (pos2.y<0) return -10;
			}
			pos2.y=j+1;
			while(board[pos2.x][pos2.y] != '-'){
				pos2.y+=1;
				o.s2 = pos2;
				moves->push_back(o);
				s+=1;
			}
			pos2.y = j;
		}
	}
	if(s!=0){
		int idx = rand()%s;
		cerr<<moves->at(idx).s1.x<<' '<<moves->at(idx).s1.y<<' '<<moves->at(idx).s2.x<<' '<<moves->at(idx).s2.y<<endl;
	}
}

void updateChaos(){
	int x1,y1,x2,y2;
	cin>>x1>>y1>>x2>>y2;
	board[x2][y2] = board[x1][y1];
	board[x1][y1] = '-';
}

int updateOrder(){
	int x1,y1;

	char c;
	cerr<<"Your move:  ";
	cin>>x1>>y1>>c;
	board[x1][y1] = c;
}

void chaosPlayer(){
	bool run = 1;
	while(true){
		if(gameOver()){
			break;
		}
		if(run){
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
		//if (gameOver()) exit(-1);
		updateOrder();
		order();
	}
}

int main(){
	cin>>boardSize;
	//cerr<<"main is go\n"<<boardSize<<"   here\n";
	board = new char* [boardSize];
	for(int i=0;i<boardSize;i++){
		board[i] = new char [boardSize];
	}
	//cerr<<"main is go\n";
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			board[i][j] = '-';
			cout<<board[i][j];
			cerr<<i*j<<"   you\n";
		}
	}
	printBoard();
	//cerr<<"main is go\n";
	string role;
	cin>>role;
	//cerr<<"main is go\n"<<role<<'\n';
	if (role == "ORDER"){
		orderPlayer();
		cout<<time(NULL)<<'\n';

	}
	else chaosPlayer();
	return 0;
}
