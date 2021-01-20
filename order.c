#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"

struct order * new_order(char * i, double p){
  struct order *new_order;

  new_order = malloc(sizeof(struct order));

  strncpy(new_order -> item, i, sizeof(new_order->item)-1);
  new_order -> price = p;

  return new_order;
}

struct order * insert_order(struct order * first, char * i, double p){
    struct order * o = new_order(i, p);
    o -> next = first;
    return o;
}
