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

int BUFFER_SIZE = 256;

int main(){
  char order[BUFFER_SIZE], line[BUFFER_SIZE];
  int fd1, fd2, i;
  //printf("got here 1\n");

  mkfifo("system_p", 0644);
  fd1 = open("menu_p", O_RDONLY);

  //linked list
    struct order * order_list = NULL;
    //struct order * order1 = insert_order(order_list, "Milk Tea", 4.00);
    //struct order * order2 = insert_order(order1, "Green Milk Tea", 4.00);
    //struct order * order3 = insert_order(order2, "Mango Mochi", 3.00);
    //struct order * order4 = insert_order(order3, "Tiramisu", 5.00);

  //printf("opened menu pipe for read\n");
  while (1){
    read(fd1, order, sizeof(order));
    fd2 = open("system_p", O_WRONLY);

    if (strncmp(order, "1",1)==0) {
      break;
    }

    //printf("opened system pipe for writing\n");
    strncpy(line, order,sizeof(line)-1);
    write(fd2, line, sizeof(line));

    struct order * order_item = insert_order(order_list, line, 4.00);
  }

  //go through linked list, calculate price, print out entire order,

  close(fd1);
  close(fd2);

  return 0;
}
