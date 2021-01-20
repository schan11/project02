#ifndef ORDER_H
#define ORDER_H

struct order{
  double price;
  struct order * next;
  char item[256];
};

struct order * place_order(char * i, double p);
struct order * insert_order(struct order * first, char * i, double p);

#endif
