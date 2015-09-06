#include "class.h"

struct chip
{
  int x , y , color ;
} ;
class gameTree
{
public:
  //turn 0 - order 1 -chaos 2- expectation
  int turn ;
  int x1 , y1 , x2 , y2 , color , current ;
  vector<gameTree> children ;
  gameTree(int t )
  { turn = t;current = -1 ; color = -1 ;}
  gameTree(int t , int col )
  { turn = t;current = -1 ; color = col ;}
  gameTree (int x ,int y , int xd , int yd , int co )
  {x1 = x ; x2 = xd ; y1 = y  ; y2 = yd ; color = co ; current = -1 ;}
  gameTree (int t ,gameTree *ch ,int s )
  { turn =t ; current = 0 ;
    for (size_t i = 0; i < s; i++) {
      children.push_back(ch[i]) ;
    }
  }
  void builChildren ()
  {
    current = 0 ;
    switch(turn)
    {
      case 0 :
        for (list<chip>::iterator i = chipOnBoard.begin(); i !=chipOnBoard.end() ; i++) {
          for (size_t j = 0; j < boardSize; j++) {
            if((i->x - j > 0))
            {
              gameTree temp (i->x , i->y , i->x-j , i->y , i->color) ;
              temp.turn = 2 ;
              children.push_back(temp) ;
            }
            if((i->y - j > 0))
            {
              gameTree temp (i->x , i->y , i->x , i->y - j , i->color) ;
              temp.turn = 2 ;
              children.push_back(temp) ;
            }
            if((i->x + j < boardSize))
            {
              gameTree temp (i->x , i->y , i->x+j , i->y , i->color) ;
              temp.turn = 2 ;
              children.push_back(temp) ;
            }
            if((i->y + j <boardSize ))
            {
              gameTree temp (i->x , i->y , i->x , i->y + j , i->color) ;
              temp.turn = 2 ;
              children.push_back(temp) ;
            }
          }
        }
        break ;
        case 1 :
        for (size_t i = 0; i < boardSize; i++) {
          for (size_t j = 0; j < boardSize; j++) {
            if(currentState[i][j] = -1)
            {
              gameTree temp (0) ;
              temp.x1 = i ; temp.y1 = j ;temp.color = color ;
              children.push_back(temp) ;
            }
          }
        }
        break ;
        case 2:
        for (size_t i = 0; i < boardSize; i++) {
          if(chips[i]>0)
          {
            //("here\n");
            gameTree temp (1);
            temp.x1 = chips[i] ;
            temp.y1 = boardSize*boardSize - chipOnBoard.size() ;
            temp.color = i ;
            children.push_back(temp) ;
          }
        }
        break ;

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
// //("4\n" );
//   gameTree game (1);
//   game.color = 3 ;
//   game.builChildren() ;
//   printf("%d\n", game.children.size());
//   return 0 ;
// }
