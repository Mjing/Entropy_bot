#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <math.h>
#include "hash.cpp"
// #include "phu.cpp"

using namespace std ;
long long thisState ;
map <long long , float> safe ;
stack <gameTree*> traversal ;
int depth = 0  ;
bool stop = false ;
int nx1 , ny1 , nx2 , ny2 , turn;
float evaluate ()
{
  return float (noOfchips );
}
void start(int bs)
{
  boardSize = bs ;
  currentState = new int*  [boardSize] ;
  noOfchips = bs*bs ;
  chips = new int [boardSize];
  for(int i=0;i<boardSize;i++)
  {
    currentState[i] = new int [boardSize] ;
    chips [i] = boardSize;
    for(int j =0;j<boardSize;j++)
    currentState[i][j] = -1 ;
  }
  int l1 = 3 ,
  // rand()%boardSize ,
   l2 = 2 ;
  //  rand()%boardSize ;
  gameTree* init = new gameTree  ;//intialise <<<<<<<----------
  init->x1 = rand() % boardSize;init->y1 = rand() % boardSize ;init->color =rand() % boardSize ;
  for(int i=0;i<l1;i++)
    for(int j=0;j<l2;j++)
    {
      int x = rand()%boardSize , y = rand()%boardSize ;
      if(init->x1 != x|| init->y1 != y)
      {
        int col = rand()%boardSize ;
        if(chips[col]>0)
        {currentState[x][y] = col ;
        chips[currentState[x][y]]-- ;}}
    }
  currentState[init->x1][init->y1] = init->color ;init->turn = 0 ;init->score = ALPHA ;
  chips[init->color] -- ;
  traversal.push(init) ;
  turn = init->turn ;
}
void moveOrder(gameTree * a)
{
  currentState[a->x1][a->y1] = -1 ;
  currentState[a->x2][a->y2] = a->color ;
}
void undoOrder (gameTree* a)
{
  currentState[a->x1][a->y1] =-1 ;
  chips[a->color]++ ;
  noOfchips ++ ;
}
void moveChaos (gameTree* a)
{
  chips[a->color] -- ;noOfchips-- ;
  currentState[a->x1][a->y1] = a->color ;
}
void undoExp  (gameTree * a)
{
  currentState[a->x2][a->y2] = -1 ;
  currentState[a->x1][a->y1] = a->color ;
}

//depth functionh
//todo setscore & update globals
//inv => for all (order) traversal.top-> score max(children) | traversal[1] min(all(traversal.top->score)) ;
void order()
{
  // fprintf(stderr, "state %d %d %d %d\n",temps ->x1 , temps->y1 , temps->x2 , temps->y2 );
  gameTree * temp  = traversal.top() ;
  gameTree * temps = temp->nextState() ;
  // printf("%d\n", temps->x1);
  if(temps->x1 == -1)
  {
    // if(depth == 0) fprintf(stderr, "yyyyyyyyy %d\n" , traversal.size());
    undoOrder(temp) ;
    traversal.pop() ;depth-- ;
    if(depth >= 0)
    {
      if(temp->score < traversal.top()->score)
      {
        // fprintf(stderr, "qwe\n");
        traversal.top()->score = temp->score ;
        if( depth <2 && turn == 0 )
        {
          nx1  =temp->x1 ; ny1= temp->y1 ; nx2 = temp->color ;
          printf("here\n" );
        }
      }
      if(depth >=2 && depth <= 5)
      {
        //----------------------------------------------
        safe.insert(std::pair<long long , float> (thisState  , temp->score)) ;
      }

    }
    else stop = true ;
    thisState= hashChaos (thisState,temp->x1 , temp->y1 , -1) ;
    delete temp ; delete temps ;
  }
  else if(depth >= 8)
  {
    // if(depth == -) fprintf(stderr, "%s\n", "aaaaaaaaaaa");
    traversal.pop() ;depth -- ;
    // fprintf(stderr, "aa %d\n" , temps->x1);
    moveOrder(temps) ;
    temps->score = evaluate() ;
    if(temps->score > temp->score) temp->score = temps->score ;
    undoExp(temps) ;
    if(temp->score < traversal.top()->score ) traversal.top()->score = temp->score ;
    thisState= hashChaos(thisState , temp->x1 , temp->y1 , -1) ;
    undoOrder(temp) ;
    delete temp ; delete temps ;
  }
  else if (depth > 0 && temp->in)
  {
    // fprintf(stderr, "ad" );
    // if(depth==0)fprintf(stderr, "xxxxxxxxxxxxxxxxxxxxxxxx %d\n" ,  traversal.size());
    traversal.pop() ;depth-- ;
    undoOrder(temp) ;
    if(temp->score < traversal.top()->score)
    {
      traversal.top()->score = temp->score ;
      moveChaos(temp) ;
      traversal.push(temp) ;
      depth ++ ;
      bool prune = true ; long long sss = hashOrd(currentState , thisState , temps->x1 , temps->x2 , temps->y1 , temps->y2) ;
      try {
        temps->score = safe.at(sss) ;
      }
      catch(const std::out_of_range &error)
      {
        prune = false ;
      }
      if(prune)
      {
        if(temps->score > temp->score) temp->score = temps->score ;
        delete temps ;
      }
      else
      {
        fprintf(stderr, "pruneD\n");
        thisState = sss ;
        moveOrder(temps) ;
        traversal.push(temps) ;depth ++ ;
      }
    }
    else {thisState = hashChaos(thisState , temp->x1 , temp->y1 , -1) ;
      delete temp ; delete temps ;}
  }
  else
  {
    // if(depth == 0) fprintf(stderr, "%s %d\n", "zzzzzzzzzzzzzzz" , traversal.size());
    // fprintf(stderr, "ae" );
    temp->in = true ;
    // fprintf(stderr, "ac\n");
    bool prune = true ;
    long long sss = hashOrd(currentState , thisState , temps->x1, temps->x2 , temp->y1 , temps->y2) ;
    try{
      temps->score =  (safe.at(sss)) ;
    }
    catch(const std::out_of_range &error){
      prune = false ;
    }
    if(prune)
    {
      delete temps ;
      fprintf(stderr, "pruneA\n");
    }
    else {
      moveOrder(temps) ;
      thisState = sss ;
      traversal.push(temps) ; depth++ ;
    }
  }
}
//inv => for all (chaos) traversal.top-> score min(children) | traversal[1] exp(all(traversal.top->score)) ;
void chaos()
{
  gameTree * temp = traversal.top();
  gameTree* temps = temp->nextState() ;
  // printf("%d\n", temps->x1);
  if(temps->x1 == -1 )
  {
    // fprintf(stderr, "ca\n");
    traversal.pop() ;
    if(depth > 0)
    {
      // printf("scoore %d\n", temp->x2);
      traversal.top()->score += temp->score * (float (temp->x1) / float(temp->x2)) ;
      if(depth>= 2 && depth <= 5)
      {
        safe.insert(std::pair<long,long> (thisState , temp->score ) ) ;
      }
    }
    depth-- ;
    delete temp ;delete temps ;
  }
  else if(depth >=8 )
  {
    temp->score = evaluate() ;
    traversal.pop() ; depth-- ;
    moveChaos (temps) ;
    //thisState = hashChaos(thisState , temps->x1 , temp->y1 , temps->color) ;
    temps->score = evaluate() ;
    if(temps->score < temp->score) temp->score = temps->score ;
    undoOrder(temps) ;
    traversal.top()->score += temp->score * (float(temp->x1) / float(temp->x2)) ;
    delete temp ; delete temps ;
  }
  else if(depth > 0 && traversal.top()->in)
  {
    // fprintf(stderr, "cc\n" );
    bool prune = true ; long long sss = hashChaos(thisState , temps->x1 , temps->y1 , temps->color) ;
    try
    {
      temps->score = safe.at(sss) ;
    }
    catch(const std::out_of_range &error)
    {
      prune = false ;
    }
    if(prune) delete temps ;
    else
    {
      fprintf(stderr, "pruneC\n");
      moveChaos(temps) ;thisState = sss ;
      traversal.push(temps) ;depth++ ;
    }
  }
  else
  {
    // fprintf(stderr, "cd\n");
    temp->in = true ;
    bool prune = true ; long long sss = hashChaos(thisState , temps->x1 , temps->y1 , temps->color) ;
    try
    {
      temps->score = safe.at(sss) ;
    }
    catch(const std::out_of_range &error)
    {
      prune = false ;
    }
    if(prune) delete temps ;
    else {
      fprintf(stderr, "pruneB\n");
      thisState = sss ;
      moveChaos(temps) ;
      traversal.push(temps) ;depth++  ;
    }
  }
  //printf("here1\n");
}
//inv => for all (expi) traversal.top-> score exp(children) | traversal[1] max(all(traversal.top->score)) ;
void exp()
{
  gameTree * temp = traversal.top() ;
  gameTree *temps = temp->nextState() ;
  // printf("%d\n", temps->x1);
  if(temps->x1 == -1)
  {
    traversal.pop() ; depth -- ;
    if(depth>= 0)
      {
        //fprintf(stderr, "wer\n");
        if(traversal.top()->score < temp->score)
        {
          traversal.top()->score = temp->score ;
          // fprintf(stderr, "bbbbbbbbb \n" );
          if(turn == 0 && depth <2)
          {
            fprintf(stderr, "qwe1\n");
            nx1 = temp->x1 ; nx2 = temp->x2 ; ny1 = temp->y1 ; ny2 = temp->y2 ;
          }
        }
      }
    delete temps ; delete temp ;
  }
  else if (depth >=8 )
  {
    // traversal.pop() ; depth-- ;
    traversal.pop() ;depth-- ;
    undoExp(temp) ;
    delete temp ;delete temps ;
  }
  else if (temp-> in && depth>0)
  {
    traversal.push(temps) ; depth++ ;
  }
  else {
    temp->in = true ;
    traversal.push(temps) ; depth++ ;
  }
}
void dfs ()
{
  while (!stop)
  {
    // fprintf(stderr, "depth %d\n" ,depth );
    // printf("end1 %d\n" , traversal.top()->children.size());
    // printf("inWhile %d\n",traversal.size() );
    switch (traversal.top()->turn)
    {
      case 0 :
        // fprintf(stderr, "order\n" );
        order() ; break ;
      case 1 :
        // fprintf(stderr, "chaos\n" );
        chaos() ; break ;
      case 2 :
        // fprintf(stderr, "exp\n");
        exp() ;break ;
    };
  }
}

int main()
{
  start(7);
  init_zobrist() ;
  thisState = hashval(currentState) ;
  dfs() ;
  fprintf(stderr, "move %d %d %d %d\n", nx1 , ny1 , nx2 , ny2);
}
