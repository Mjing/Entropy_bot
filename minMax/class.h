#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>
<<<<<<< HEAD
=======
#define  ALPHA -100000
#define BETA 100000

>>>>>>> ab5e8d0799d3dc79282f00f67d6b34aa9dfb7ffc
using namespace std ;
struct chip ;
class gameTree ;

int ** currentState ;
int*chips ;
int boardSize ;
list <chip> chipOnBoard ; // current list of chip on board
