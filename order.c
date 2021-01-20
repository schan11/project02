#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct order * place_order(char * i, double p){
  struct order *new_order;

  new_order = malloc( sizeof( struct order));

  strncpy(new_order -> item, i, sizeof(item)-1);
  new_order -> price = p;

  return new_order;
}
