<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <math.h>
#include "class.cpp"
// #include "phu.cpp"
=======
// #include <stdio.h>
// #include <stdlib.h>
#include <stack>
#include <math.h>
#include "class.cpp"
//#include "phu.cpp"
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
#define  ALPHA -100000
#define BETA 100000

using namespace std ;

stack <gameTree*> traversal ;
int depth = 0  ;
bool end = false;
<<<<<<< HEAD
void deleteAll(vector <gameTree*> a)
{
  for (size_t i = 0; i < a.size(); i++) {
    delete a[i] ;
  }
}
float evaluate ()
{
  return float (boardSize*boardSize - chipOnBoard.size() );
}
=======
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
void start(int bs)
{
  boardSize = bs ;
  currentState = new int*  [boardSize] ;
  chips = new int [boardSize];
  for(int i=0;i<boardSize;i++)
  {
    currentState[i] = new int [boardSize] ;
    chips [i] = boardSize;
<<<<<<< HEAD
    for(int j =0;j<boardSize;j++)
    currentState[i][j] = -1 ;
  }
  int l1 = 3 ,
  // rand()%boardSize ,
   l2 = 2 ;
  //  rand()%boardSize ;
  gameTree* init = new gameTree  ;//intialise <<<<<<<----------
  init->x1 = rand() % boardSize;init->y1 = rand() % boardSize ;init->color =rand() % boardSize ;
=======
  }
  int l1 = rand()%boardSize , l2 = rand()%boardSize ;
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
  for(int i=0;i<l1;i++)
    for(int j=0;j<l2;j++)
    {
      int x = rand()%boardSize , y = rand()%boardSize ;
<<<<<<< HEAD
      if(init->x1 != x|| init->y1 != y)
      {
        int col = rand()%boardSize ;
        if(chips[col]>0)
        {currentState[x][y] = col ;
        chip tdash ; tdash.x = x ; tdash.y= y ; tdash.color = currentState[x][y] ;
        chipOnBoard.push_back(tdash) ;
        chips[currentState[x][y]]-- ;}}
    }
  // printf("here\n");
  currentState[init->x1][init->y1] = init->color ;init->turn = 0 ;
  chips[init->color] -- ;
  chip tc ; tc.x = init->x1 ; tc.y = init->y1 ; tc.color= init->color ;
  chipOnBoard.push_back(tc) ;
  init->builChildren() ;
  traversal.push(init) ;
  //printf("end%d\n" , traversal.top()->children.size());
}
void moveOrder(gameTree * a)
{
  currentState[a->x1][a->y1] = -1 ;
  currentState[a->x2][a->y2] = a->color ;
  chipOnBoard.pop_back() ;
  chip temp ;
  temp.x = a->x2 ;
  temp.y = a->y2 ;
  temp.color = a->color ;
  chipOnBoard.push_back(temp) ;
}
void undoOrder (gameTree* a)
{
  currentState[a->x1][a->y1] =-1 ;
  chips[a->color]++ ;
  chipOnBoard.pop_back() ;
}
void moveChaos (gameTree* a)
{
  chip temp;
  temp.x = a->x1 ;
  temp.y = a->y1 ;
  temp.color = a->color ;
  chips[a->color] -- ;
  currentState[a->x1][a->y1] = a->color ;
  chipOnBoard.push_back(temp) ;
}
void undoExp  (gameTree * a)
{
  chip temp ;
  temp.x = a->x1 ;
  temp.y = a->y1 ;
  temp.color = a->color ;
  chipOnBoard.pop_back() ;
  chipOnBoard.push_back(temp) ;
  currentState[a->x2][a->y2] = -1 ;
  currentState[a->x1][a->y1] = a->color ;
}
=======
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

>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
//depth function
//todo setscore & update globals
//inv => for all (order) traversal.top-> score max(children) | traversal[1] min(all(traversal.top->score)) ;
void order()
{
<<<<<<< HEAD
  if (depth >= 5 )
  {
    //traversal.top()->current ++ ;
    gameTree * temp = traversal.top() ;
    traversal.pop() ;
    temp->score = evaluate() ;
    undoOrder(temp) ;depth-- ;
    if(traversal.top()->score > temp->score)
    {
      traversal.top()->score = temp->score ;
    }
    deleteAll(temp->children) ;
    temp->children.clear() ;
=======
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
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
    delete temp ;
  }
  else if(depth >0 && traversal.top()->current != -1 ){
    gameTree * temp =traversal.top() ;
    temp->current++ ;
    traversal.pop() ;depth-- ;
<<<<<<< HEAD
    undoOrder(temp) ;
=======
    temp->color = currentState[temp->x1][temp->y1] ;
    currentState[temp->x1][temp->y1] = -1 ;
    chipOnBoard.pop_back() ;
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
    if(temp->score < traversal.top()->score)
    {
      traversal.top()->score = temp->score ;
      if(temp->current == temp->children.size())
      {
<<<<<<< HEAD
        temp->children.clear() ;
=======
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
        delete temp ;
      }
      else
      {
<<<<<<< HEAD
        moveChaos(temp) ;
        traversal.push(temp) ;depth++ ;
        moveOrder(temp->children[temp->current]) ;
        if(depth < 5-1)
          temp->children[temp->current]->builChildren() ;
        traversal.push(temp->children[temp->current]) ;
        depth++ ;
=======
        traversal.push(temp) ;depth++ ;
        currentState[temp->x1][temp->y1] = temp->color
        temp->children[temp->current]->builChildren() ;
        currentState[traversal.top()->x1][traversal.top()->y1] = -1 ;
        currentState[traversal.top()->x2][traversal.top()->y2] = temp.color ;
        traversal.push(temp->children[temp->current]) ;depth++ ;
        chip p ; p.x = traversal.top()->x2 ;p.y = traversal.top()->y2 ;
        p.color = temp.color ;
        chipOnBoard.push_back(p) ;
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
      }
    }
    else
    {
<<<<<<< HEAD
      fprintf(stderr, "prune\n" );
      temp->children.clear() ;
=======
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
      delete temp ;
    }
  }
  else
  {
    traversal.top()->current++ ;
<<<<<<< HEAD
    gameTree * temp = traversal.top()->children[traversal.top()->current] ;
    moveOrder (temp) ;
    depth++ ;
    if(depth < 5) temp->builChildren() ;
    traversal.push(temp) ;
=======
    int col = traversal.top()->color ;
    traversal.push(traversal.top()->children[traversal.top()->current]) ;
    currentState[traversal.top()->x1][traversal.top()->y1] = -1 ;
    currentState[traversal.top()->x2][traversal.top()->y2] =col ;
    depth++ ;
    traversal.top()->builChildren() ;
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
  }
}
//inv => for all (chaos) traversal.top-> score min(children) | traversal[1] exp(all(traversal.top->score)) ;
void chaos()
{
<<<<<<< HEAD
  //printf("chaos\n");
  if(depth>= 5)
  {
    gameTree *temp = traversal.top() ; traversal.pop() ;
    depth-- ;
    traversal.top()->score += temp->score * (float(temp->x1) / float(temp->y1)) ;
    deleteAll(temp->children) ;
    temp->children.clear() ;
=======
  if(depth>= 9)
  {
    gameTree * temp = traversal.top() ;
    temp->score = evaluate() ;
    traversal.pop() ; depth-- ;
    currentState[temp->x1][temp->y1] = -1 ;
    chipOnBoard.pop_back() ;
    chips[temp->color]++ ;
    traversal.top()->score += float(color[temp->color])/float(boardSize*boardSize - chipOnBoard.size()) * (temp->score) ;
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
    delete temp ;
  }
  else if(depth>0 && traversal.top()->current != -1)
  {
    gameTree * temp = traversal.top() ;
    temp->current++ ;
    traversal.pop() ; depth-- ;
<<<<<<< HEAD
    //printf("%d %d \n",temp->x1 , temp->y1);
    traversal.top()->score += (float (temp->x1) / float(temp->y1))* (temp->score) ;
    if(temp->current == temp->children.size())
      {temp->children.clear() ;delete temp ;}
    else
    {
      //printf("chaos\n");
      traversal.push(temp) ;depth++ ;
      if(depth < 5)
      temp->children[temp->current]->builChildren() ;
      moveChaos(temp->children[temp->current]) ;
=======
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
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
      traversal.push(temp->children[temp->current]) ;depth++ ;
    }
  }
  else
  {
    traversal.top()->current++ ;
    traversal.push(traversal.top()->children[traversal.top()->current]) ;
    depth++ ;
<<<<<<< HEAD
    if(depth < 5)
    traversal.top()->builChildren() ;
    moveChaos(traversal.top()) ;
  }
  //printf("here1\n");
=======
    chip temp ; temp.x = traversal.top()->x1 ; temp.y = traversal.top()->y1 ;
    temp.color = traversal.top()->color ;
    currentState [temp.x][temp.y] = temp.color ;
    chips[temp.color] -- ;
    chipOnBoard.push_back(temp) ;
    traversal.top()->builChildren() ;
  }
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
}
//inv => for all (expi) traversal.top-> score exp(children) | traversal[1] max(all(traversal.top->score)) ;
void exp()
{
<<<<<<< HEAD
  if(depth >= 5)
  {
    gameTree * temp = traversal.top() ;    depth -- ;
    traversal.pop() ;
    undoExp(temp) ;
    if(traversal.top()->score < temp->score)
    traversal.top()->score < temp->score ;
    deleteAll(temp->children) ;
    temp->children.clear() ;
    delete temp ;
  }
  else if(depth>0 && traversal.top()->current != -1)
  {
    gameTree *temp = traversal.top();
    traversal.pop() ;depth-- ;
    undoExp(temp) ;
    temp->current ++ ;
    if(temp->current ==  temp->children.size())
    {
      if(temp->score > traversal.top()->score)
      {
        traversal.top()->score =temp->score  ;
      }
      temp->children.clear() ;
      delete temp ;
    }
    else
    {
      traversal.push(temp) ;depth += 2;
      if(depth < 5)
      temp->children[temp->current]->builChildren() ;
      traversal.push(temp->children[temp->current]) ;
    }
  }
=======
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
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
  else
    {
      traversal.top()->current++ ;
      traversal.push(traversal.top()->children[traversal.top()->current]) ;
      depth++ ;
<<<<<<< HEAD
      if(depth < 5)
=======
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
      traversal.top()->builChildren() ;
    }
}
void dfs ()
{
<<<<<<< HEAD
  while (1)
  {
    fprintf(stderr, "depth %d\n" , traversal.size() );
    // printf("end1 %d\n" , traversal.top()->children.size());
    // printf("inWhile %d\n",traversal.size() );
    if((depth == 0)&&(traversal.top()->current== ((traversal.top())->children).size() - 1)) break ;
    switch (traversal.top()->turn)
    {

      case 0 :
        //fprintf(stderr, "order\n" );
        order() ; break ;
      case 1 :
        //fprintf(stderr, "chaos\n" );
        chaos() ; break ;
      case 2 :
        //fprintf(stderr, "exp\n");
=======
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
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
        exp() ;break ;
    };
  }
}

int main()
{
<<<<<<< HEAD
  start(7) ;
=======
  start(5) ;
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
  dfs() ;
}
