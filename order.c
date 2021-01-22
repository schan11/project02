#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"

//new order
struct order * new_order(char * i, double p){
  struct order *new_order;

  new_order = malloc(sizeof(struct order));

  strncpy(new_order -> item, i, sizeof(new_order->item)-1);
  new_order -> price = p;

  return new_order;
}

//insert order to linked list
struct order * insert_order(struct order * first, char * i, double p){
    struct order * o = new_order(i, p);
    o -> next = first;
    return o;
}

//get total price
double get_price(struct order * order){
  double total_price;
  while (order){
    total_price += order -> price;
    order = order -> next;
  }
  return total_price;
}

//prints entire list
void print_list(struct order * order){
	while (order){
		display(order);
		order = order -> next;
	}
}

//prints item and price
void display(struct order * order){
	printf("Item: %s\tPrice: %0.2lf\n", order->item, order->price);
}
