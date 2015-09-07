#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>
#define  ALPHA -100000
#define BETA 100000

using namespace std ;
struct chip ;
class gameTree ;

int ** currentState ;
int*chips ;
int boardSize ;
list <chip> chipOnBoard ; // current list of chip on board
