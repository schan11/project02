#ifndef ORDER_H
#define ORDER_H

struct order{
  char item[];
  double price;
  struct order * next;
}

#endif
