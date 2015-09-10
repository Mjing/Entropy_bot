#include <stdio.h>
#include <stdlib.h>
#include "class.h"
using namespace std ;


class gameTree
{
  public:
    int x1 , y1 , x2 ,y2 , c1 , c2 ,c3,c4 ,color , turn;
    float score ;bool in ;
    gameTree () {in = false ;c1=  0 ;x1 = 0 ; c2 = 0 ;c4 =0 ;c3 = 0 ; }
    gameTree (int t) {in = false ;turn = t ;c1=  0 ;x1 = 0 ; c2 = 0 ;c4 =0 ;c3 = 0 ;
      switch(t)
      {
        case 0 : score = ALPHA ; break ;
        case 1 : score = BETA ; break ;
        case 2 : score = 0 ; break ;
      }
    }
    gameTree (int x , int y , int t) {in = false ;turn = t ;x1 = x ;y1 = y ;c1=  0 ;x1 = 0 ; c2 = 0 ;c4 =0 ;c3 = 0 ;
      switch(t)
      {
        case 0 : score = ALPHA ; break ;
        case 1 : score = BETA ; break ;
        case 2 : score = 0 ; break ;
      }
    }
    gameTree (int x , int y ,int x3 , int y3 , int col, int t) {x2 = x3 ; y2 = y3 ; color = col ;turn = t ;x1 = x ;y1 = y ;c1=  0  ; c2 = 0 ;c4 =0 ;c3 = 0 ;in = false ;
      switch(t)
      {
        case 0 : score = ALPHA ; break ;
        case 1 : score = BETA ; break ;
        case 2 : score = 0 ; break ;
      }
    }

    gameTree* nextState()
    {
      switch (turn)
        {
          case 0 :
          {
            gameTree * temp = new gameTree(2) ;
            int x = boardSize , y= boardSize ;
            for(int i=c1;i<boardSize ; i++)
            {
              for(int j = c2 ; j<boardSize ; j++)
              {
                if(currentState[i][j] != -1)
                {
                  x=i ; y = j ; i = boardSize ; j = boardSize ;
                }
              }
              if(x == boardSize)
              {
                // fprintf(stderr, "fail1\n");
                temp->x1 = -1 ; c1 = boardSize ;
              }
              else if(currentState[x][y] != -1)
              {
                temp->x1 = x ; temp->y1 = y ; temp->color = color ;
                c1 = x ; c2 =y ;
                // fprintf(stderr, "%s %d %d\n", "gotcha" , x ,y);
                if(c3 <= 0)
                {
                  c3-- ;
                  if(c3 + x >=0 && currentState[c3+x][y] == -1)
                  {
                    temp->x2 = c3 + x ; temp->y2 = y ; return temp ;
                  }
                  else c3 = 1;
                }
                if(c3 > 0)
                {
                  if(c3 +x < boardSize && currentState[c3+x] [y] == -1)
                  {
                    temp->x2 = c3+x ; temp->y2 = y ; c3++ ; return temp ;
                  }
                  else c3 = boardSize ;
                }
                if(c3== boardSize && c4 <=0 )
                {
                  c4-- ;
                  if(c4 + y >= 0 && currentState[x][c4+y] == -1)
                  {
                    temp->x2 =x ; temp->y2 = c4+y ;return temp ;
                  }
                  else c4 = 1 ;
                }
                if(c3 == boardSize && c4>0)
                {
                  if(c4 + y < boardSize && currentState[x][c4+y] == -1)
                  {
                    temp->x2 = x ; temp->y2 = c4 + y ;c4++ ; return temp ;
                  }
                  else
                  {c3 = 0 ; c4 = 0 ; c2++ ; return this->nextState() ;}
                }
              }
            }
          }
          case 1 :
            {gameTree * temp = new gameTree(0) ;temp->color = color ;
            for(int i=c1;i<boardSize ;i++)
            {
              for(int j=c2;j<boardSize ;j++)
              {
                if(currentState[i][j] == -1)
                {
                  temp->x1= i ;temp->y1 = j ;c1 =i ; c2 = j+1 ; return temp ;
                }
              }
             c2 = 0 ;
            }
            c1 = boardSize ;
            // fprintf(stderr ,"failChaos\n");
            temp->x1 = -1 ;
            return temp;
            break ;}
          case 2 :
            {gameTree * temp = new gameTree (1);
            for(int i=c1 ; i<boardSize ;i++)
            {
              if(chips[i] > 0 )
              {
                c1 = i+1 ;
                temp->color = i ;temp->x1 = chips[i]  ; temp->x2 = noOfchips ; return temp ;
              }
            }
            c1 = boardSize ;
            // fprintf(stderr, "failex\n");
            temp->x1 = -1 ;
            return temp ;
            break ;}
        }
      }
};
// void start(int bs)
// {
//   boardSize = bs ;
//   currentState = new int*  [boardSize] ;
//   noOfchips = bs*bs ;
//   chips = new int [boardSize];
//   for(int i=0;i<boardSize;i++)
//   {
//     currentState[i] = new int [boardSize] ;
//     chips [i] = boardSize;
//     for(int j =0;j<boardSize;j++)
//     currentState[i][j] = -1 ;
//   }
//   int l1 = 3 ,
//   // rand()%boardSize ,
//    l2 = 2 ;
//   //  rand()%boardSize ;
//   gameTree* init = new gameTree  ;//intialise <<<<<<<----------
//   init->x1 = rand() % boardSize;init->y1 = rand() % boardSize ;init->color =rand() % boardSize ;
//   for(int i=0;i<l1;i++)
//     for(int j=0;j<l2;j++)
//     {
//       int x = rand()%boardSize , y = rand()%boardSize ;
//       if(init->x1 != x|| init->y1 != y)
//       {
//         int col = rand()%boardSize ;
//         if(chips[col]>0)
//         {currentState[x][y] = col ;
//         chips[currentState[x][y]]-- ;}}
//     }
//   currentState[init->x1][init->y1] = init->color ;init->turn = 0 ;
//   chips[init->color] -- ;
//   // traversal.push(init) ;
//   // st=init ;
// }
//
// int main()
// {
//   gameTree a (0) , b (1) , c(2) ;
//   b.color = 3;
//   start(7) ;
//   gameTree * temp = b.nextState() ;
//   while(temp->x1 != -1)
//   {
//     printf("%d %d %d %d %d %d\n",temp->x1 , temp->y1 , b.c1 , b.c2 , b.c3 , b.c4);
//     temp = b.nextState() ;
//   }
// }
