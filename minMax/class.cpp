#include "class.h"
#include <vector>

struct chip
{
  int x , y , color ;
} ;
class gameTree
{
<<<<<<< HEAD
  public:
=======
public:
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
  //turn 0 - order 1 -chaos 2- expectation
  int turn ;
  int x1 , y1 , x2 , y2 , color , current ; float  score ;
  vector<gameTree*> children ;
  gameTree()
  {
    current = -1 ;color = -1 ;
  }
  gameTree(int t )
  { turn = t;current = -1 ; color = -1 ;
  switch(turn)
    {
      case 0 : score = (float)ALPHA ; break ;
      case 1 : score = (float)BETA ; break ;
      case 2 : score = (float)0 ;  break ;
    } ;
  }
  gameTree(int t , int col )
  { turn = t;current = -1 ; color = col ;
    switch(turn)
      {
        case 0 : score = (float)ALPHA ; break ;
        case 1 : score = (float)BETA ; break ;
        case 2 : score = (float)0 ;  break ;
      } ;
  }
  gameTree (int x ,int y , int xd , int yd , int co )
  {
    x1 = x ; x2 = xd ; y1 = y  ; y2 = yd ; color = co ; current = -1 ;
    switch(turn)
      {
        case 0 : score = (float)ALPHA ; break ;
        case 1 : score = (float)BETA ; break ;
        case 2 : score =(float) 0 ;  break ;
      } ;
  }
  gameTree (int t ,gameTree *ch ,int s )
  {
    turn =t ; current = -1;
    for (size_t i = 0; i < s; i++) {
      children.push_back(&ch[i]) ;
    }
    switch(turn)
      {
        case 0 : score =(float) ALPHA ; break ;
        case 1 : score =(float) BETA ; break ;
        case 2 : score =(float) 0 ;  break ;
      } ;
  }
  void builChildren ()
  {
    current = -1 ;
    switch(turn)
    {
      case 0 :
<<<<<<< HEAD
=======

>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
        for (list<chip>::iterator i = chipOnBoard.begin(); i !=chipOnBoard.end() ; i++)
        {
        bool left = true , right = true, up = true , down = true ;
        // printf("here\n");
          int ind =1 ;
          while(right||up||down|| left)
          {
            // printf("h2\n");
            if(i->x - ind < 0) left = false  ;
            if(i->x + ind >= boardSize) right = false ;
            if(i->y - ind < 0 ) up = false ;
            if(i->y+ind >= boardSize)down =false ;
            if(left)
            {
              if(currentState[i->x- ind][i->y] ==-1 )
              {
                // chip temp ; temp.x = i->x - ind ; temp.y = i->y ;temp.color = currentState[temp.x][temp.y] ;
                // chipOnBoard.push_back(temp ) ;
                gameTree *temp = new gameTree (i->x , i->y , i->x-ind , i->y , currentState[i->x ][ i->y]) ;
<<<<<<< HEAD
                temp->turn =2 ;
=======
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
                children.push_back(temp) ;
              }
              else left = false ;
            }
            if(right)
            {
              if(currentState[i->x+ ind][i->y] ==-1 )
              {
                gameTree *temp = new gameTree (i->x , i->y , i->x+ind , i->y , currentState[i->x ][ i->y]) ;
<<<<<<< HEAD
                temp->turn =2 ;
=======
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
                children.push_back(temp) ;
              }
              else right = false ;
            }
            if(up)
            {
              if(currentState[i->x][i->y- ind] ==-1 )
              {
                gameTree *temp = new gameTree (i->x , i->y , i->x , i->y-ind , currentState[i->x ][ i->y]) ;
<<<<<<< HEAD
                temp->turn =2 ;
=======
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
                children.push_back(temp) ;
              }
              else up = false ;
            }
            if(down)
            {
              if(currentState[i->x][i->y+ ind] ==-1 )
              {
                gameTree *temp = new gameTree (i->x , i->y , i->x , i->y+ind , currentState[i->x ][ i->y]) ;
<<<<<<< HEAD
                temp->turn =2 ;
=======
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
                children.push_back(temp) ;
              }
              else down = false ;
            }
            ind++ ;
          }
        }
<<<<<<< HEAD
        break ;

      case 1 :
        for (size_t i = 0; i < boardSize; i++) {
          for (size_t j = 0; j < boardSize; j++) {
            if(currentState[i][j] == -1)
            {
              gameTree* temp = new gameTree (0) ;
              temp->x1 = i ; temp->y1 = j ;temp->color = color ;
              children.push_back(temp) ;
=======

        break ;
      case 1 :
        for (size_t i = 0; i < boardSize; i++) {
          for (size_t j = 0; j < boardSize; j++) {
            if(currentState[i][j] = -1)
            {
              gameTree temp (0) ;
              temp.x1 = i ; temp.y1 = j ;temp.color = color ;
              children.push_back(&temp) ;
>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
            }
          }
        }
        break ;
<<<<<<< HEAD

      case 2:
        for(int i=0;i<boardSize;i++)
        {
          gameTree* temp = new gameTree (1);
          temp->x1 = chips[i];
          temp->y1 = boardSize*boardSize - chipOnBoard.size() ;
          temp->color = i ;
          children.push_back(temp) ;
        }
        break ;
=======
      case 2:
        for(int i=0;i<boardSize;i++)
        {
          gameTree temp (1);
          temp.x1 = chips[i];
          temp.y1 = boardSize*boardSize - chipOnBoard.size() ;
          temp.color = i ;
          children.push_back(&temp) ;
        }
        break ;

>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
    };
  }
};
// int main()
// {
//   boardSize = 7 ;
//   //("1\n");
//   chips = new int [boardSize] ;
//   //("2\n" );
//   currentState = new int* [boardSize] ;
//   for (size_t i = 0; i < boardSize; i++) {
//     chips[i] = boardSize ;
//     //("3\n" );
//     currentState[i] = new int [boardSize] ;
//     for(int j=0;j<boardSize;j++)
//     currentState[i][j]= -1 ;
//   }
//   currentState[3][3] = 3;
//   chip temp ; temp.x = 3 ;temp.y=3 ;temp.color = 3;
//   chipOnBoard.push_back(temp) ;
// //("4\n" );
//   gameTree game (2);
//   game.color = 3 ;
//   game.builChildren() ;
//   printf("%d\n", game.children.size());
//   return 0 ;
// }
