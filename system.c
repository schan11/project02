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
#include "customer.h"

int BUFFER_SIZE = 256;
#define NUM_ITEMS 19

int main(){
  char order[BUFFER_SIZE], line[BUFFER_SIZE];
  int fd1, fd2, i;
  double cost, price;
  char * item_prices[NUM_ITEMS][2] = {
      {"1", "4.00"}, {"2", "3.50"}, {"3", "4:00"},
      {"4", "4.00"}, {"5", "5.00"}, {"6", "4.00"},
      {"7", "5.50"}, {"8", "6.00"}, {"9", "5.00"},
      {"10", "3.00"}, {"11", "4.00"}, {"12", "6.00"},
      {"13", "6.00"}, {"14", "5.00"}, {"15", "5.50"},
      {"16", "5.50"}, {"17", "3.00"}, {"18", "4.00"},
      {"19", "4.00"}
  };
  //printf("got here 1\n");


  mkfifo("system_p", 0644);
  fd1 = open("menu_p", O_RDONLY);

  //linked list
    struct order * order_list = NULL;
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
          //printf("Sorry, we don't have this item available.\n"); // base case if customer inputs random characters not on menu
        continue;
      }
      else{
        cost = atof(item_prices[i][1]); //convert cost (char *) to double
      }
    }

    fd2 = open("system_p", O_WRONLY);
    //printf("opened system pipe for writing\n");
    strncpy(line, order,sizeof(line)-1);
    write(fd2, line, sizeof(line));

    struct order * order_item = insert_order(cur_order, line, cost);
    cur_order = order_item;
  }

  print_list(cur_order);

  //go through linked list, calculate price, print out entire order
  price = get_price(cur_order);
  printf("Total Price: %0.2lf\n", price);

  snprintf(line, BUFFER_SIZE, "%0.2lf", price);
  write(fd2, line, sizeof(line));

  close(fd1);
  close(fd2);

  return 0;
}
