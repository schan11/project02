#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "order.h"

// what we need to do:
// add customer info here
// hard code the array
// any other stuff we feel like doing over the weekend

int BUFFER_SIZE = 256;
int NUM_ITEMS = 19;

int main(){
  char order[BUFFER_SIZE], line[BUFFER_SIZE];
  int fd1, fd2, i;
  double cost, price;
  char item_prices[NUM_ITEMS][2] = {
      {"1", "4.00"}, {"2", "3.50"}, {"3", "4:00"},
      {"4", "4.00"}, 
  }
  //printf("got here 1\n");


  mkfifo("system_p", 0644);
  fd1 = open("menu_p", O_RDONLY);

  //linked list
    struct order * order_list = NULL;
    //struct order * order1 = insert_order(order_list, "Milk Tea", 4.00);
    //struct order * order2 = insert_order(order1, "Green Milk Tea", 4.00);
    //struct order * order3 = insert_order(order2, "Mango Mochi", 3.00);
    //struct order * order4 = insert_order(order3, "Tiramisu", 5.00);
    //print_list(order4);
    struct order * cur_order = order_list;
  //printf("opened menu pipe for read\n");
  while (1){
    read(fd1, order, sizeof(order));
    if (strncmp(order, "0",1)==0) {
       continue;
    }

    if (strncmp(order, "E",1)==0) {
      break;
    }

    for (i=0; i<NUM_ITEMS; i++){
      if (strncmp(order, item_prices[i][0], sizeof(order)-1)!=0){
        printf("Sorry, we don't have this item available.\n")
        continue;
      }
      else{
        cost = item_prices[i][1];
      }
    }

    fd2 = open("system_p", O_WRONLY);
    //printf("opened system pipe for writing\n");
    strncpy(line, order,sizeof(line)-1);
    write(fd2, line, sizeof(line));

    //convert cost to double

    struct order * order_item = insert_order(cur_order, line, cost);
    cur_order = order_item;
  }
  print_list(cur_order);
  //go through linked list, calculate price, print out entire order,
  price = get_price(cur_order);
  printf("Total Price: %0.2lf\n", price);

  snprintf(line, BUFFER_SIZE, "%0.2lf", price);
  write(fd2, line, sizeof(line));

  printf("Thanks for ordering at Cafe C! See you next time!\n");

  close(fd1);
  close(fd2);

  return 0;
}
