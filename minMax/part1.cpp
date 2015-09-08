// #include <stdio.h>
// #include <stdlib.h>
#include <stack>
#include <math.h>
#include "class.cpp"
//#include "phu.cpp"
#define  ALPHA -100000
#define BETA 100000

using namespace std ;

stack <gameTree*> traversal ;
int depth = 0  ;
bool end = false;
void start(int bs)
{
  boardSize = bs ;
  currentState = new int*  [boardSize] ;
  chips = new int [boardSize];
  for(int i=0;i<boardSize;i++)
  {
    currentState[i] = new int [boardSize] ;
    chips [i] = boardSize;
  }
  int l1 = rand()%boardSize , l2 = rand()%boardSize ;
  for(int i=0;i<l1;i++)
    for(int j=0;j<l2;j++)
    {
      int x = rand()%boardSize , y = rand()%boardSize ;
      currentState[x] [y] = rand()%boardSize;
      chip tdash ; tdash.x = x ; tdash.y= y ; tdash.color = currentState[x][y] ;
      chipOnBoard.push_back(tdash) ;
      chips[currentState[x][y]]-- ;
    }
  gameTree* init = new gameTree  ;//intialise <<<<<<<----------
  init->x1 = rand() % boardSize ;init->y1 = rand() % boardSize ;init->color =rand() % boardSize ;
  if(currentState[init->x1][init->y1] !=  -1) chips[currentState[init->x1][init->y1]] ++ ;
  currentState[init->x1][init->y1] = init->color ;init->turn = 2 ;
  init->builChildren() ;
  traversal.push(init) ;
}

//depth function
//todo setscore & update globals
//inv => for all (order) traversal.top-> score max(children) | traversal[1] min(all(traversal.top->score)) ;
void order()
{
  if (depth >= 9 )
  {
    //traversal.top()->current ++ ;
    (traversal.top())->score = evaluate() ;
    gameTree * temp = traversal.top() ;
    depth -- ;
    currentState[temp->x1][temp->y1] = -1 ;
    // currentState[temp->x1][temp->y1]= temp->color ;
    chipOnBoard.pop_back() ;
    traversal.pop() ;
    if(temp->score  < traversal.top()->score)
    {
      traversal.top()->score = temp->score ;
    }
    delete temp ;
  }
  else if(depth >0 && traversal.top()->current != -1 ){
    gameTree * temp =traversal.top() ;
    temp->current++ ;
    traversal.pop() ;depth-- ;
    temp->color = currentState[temp->x1][temp->y1] ;
    currentState[temp->x1][temp->y1] = -1 ;
    chipOnBoard.pop_back() ;
    if(temp->score < traversal.top()->score)
    {
      traversal.top()->score = temp->score ;
      if(temp->current == temp->children.size())
      {
        delete temp ;
      }
      else
      {
        traversal.push(temp) ;depth++ ;
        currentState[temp->x1][temp->y1] = temp->color
        temp->children[temp->current]->builChildren() ;
        currentState[traversal.top()->x1][traversal.top()->y1] = -1 ;
        currentState[traversal.top()->x2][traversal.top()->y2] = temp.color ;
        traversal.push(temp->children[temp->current]) ;depth++ ;
        chip p ; p.x = traversal.top()->x2 ;p.y = traversal.top()->y2 ;
        p.color = temp.color ;
        chipOnBoard.push_back(p) ;
      }
    }
    else
    {
      delete temp ;
    }
  }
  else
  {
    traversal.top()->current++ ;
    int col = traversal.top()->color ;
    traversal.push(traversal.top()->children[traversal.top()->current]) ;
    currentState[traversal.top()->x1][traversal.top()->y1] = -1 ;
    currentState[traversal.top()->x2][traversal.top()->y2] =col ;
    depth++ ;
    traversal.top()->builChildren() ;
  }
}
//inv => for all (chaos) traversal.top-> score min(children) | traversal[1] exp(all(traversal.top->score)) ;
void chaos()
{
  if(depth>= 9)
  {
    gameTree * temp = traversal.top() ;
    temp->score = evaluate() ;
    traversal.pop() ; depth-- ;
    currentState[temp->x1][temp->y1] = -1 ;
    chipOnBoard.pop_back() ;
    chips[temp->color]++ ;
    traversal.top()->score += float(color[temp->color])/float(boardSize*boardSize - chipOnBoard.size()) * (temp->score) ;
    delete temp ;
  }
  else if(depth>0 && traversal.top()->current != -1)
  {
    gameTree * temp = traversal.top() ;
    temp->current++ ;
    traversal.pop() ; depth-- ;
    currentState[temp->x1][temp->y1] = -1 ;
    chipOnBoard.push_back() ;
    chips[temp->color]--;

    int dd = boardSize * boardSize - chipOnBoard.size();
    traversal.top() ->score += (float (color[temp->color]) / float(dd))* (temp->score) ;
    if(temp->current == temp->children.size())
      delete temp ;
    else
    {
      traversal.push(temp) ;depth++ ;
      currentState[temp->x1][temp->y1] = temp->color ;
      chip tc ;tc.x = temp->x1 ;tc.y=temp->y1;tc.color = temp->color ;
      chipOnBoard.push_back(tc) ;
      chips[tc.color] -- ;
      temp->children[temp->current]->builChildren() ;
      currentState[traversal.top()->x1][traversal.top()->y1] = traversal.top()->color ;
      chips[tc.color] -- ;
      tc.x = traversal.top()->x1 ; tc.y = traversal.top().y1;tc.color = traversal.top()->color ;
      chipOnBoard.push_back(tc) ;
      traversal.push(temp->children[temp->current]) ;depth++ ;
    }
  }
  else
  {
    traversal.top()->current++ ;
    traversal.push(traversal.top()->children[traversal.top()->current]) ;
    depth++ ;
    chip temp ; temp.x = traversal.top()->x1 ; temp.y = traversal.top()->y1 ;
    temp.color = traversal.top()->color ;
    currentState [temp.x][temp.y] = temp.color ;
    chips[temp.color] -- ;
    chipOnBoard.push_back(temp) ;
    traversal.top()->builChildren() ;
  }
}
//inv => for all (expi) traversal.top-> score exp(children) | traversal[1] max(all(traversal.top->score)) ;
void exp()
{
  if(depth>0 && traversal.top()->current != -1)
  {
    gameTree *temp = traversal.top();
    traversal.pop() ;depth-- ;
    temp->current ++ ;
    if(temp->score > traversal.top())
    {
      traversal.top()->score =temp->score  ;
      if(temp->current = temp->children.size())
        delete temp ;
      else
      {
        traversal.push(temp) ;depth += 2;
        temp->children[temp->current]->builChildren() ;
        traversal.push(temp->children[temp->current]) ;
      }
    }
    else
      delete temp ;
    }
  else
    {
      traversal.top()->current++ ;
      traversal.push(traversal.top()->children[traversal.top()->current]) ;
      depth++ ;
      traversal.top()->builChildren() ;
    }
}
void dfs ()
{
  while (!end)
  {
    if((depth == 0)&&(traversal.top()->current== ((traversal.top())->children).size())) break ;
    switch (traversal.top()->turn)
    {
      case 0 :
        order() ; break ;
      case 1 :
        chaos() ; break ;
      case 2 :
        exp() ;break ;
    };
  }
}

int main()
{
  start(5) ;
  dfs() ;
}
