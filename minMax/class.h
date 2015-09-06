#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>
using namespace std ;
struct chip ;
class gameTree ;

int ** currentState ;
int*chips ;
int boardSize ;
list <chip> chipOnBoard ; // current list of chip on board
