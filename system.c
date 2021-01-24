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

// what we need to do:
// add customer info here
// hard code the array
// any other stuff we feel like doing over the weekend

int BUFFER_SIZE = 256;
#define NUM_ITEMS 19

void create_account(char* first, char* last, int card, int dining) {
  printf("Before we proceed to checkout, we need some information from you.\n");
  printf("First name: ");
  scanf("%s", first);
  printf("Last name: ");
  scanf("%s", last);
  printf("Credit Card Number: ");
  scanf("%d", &card);
  printf("Next, choose your dining option by entering the corresponding number:\n");
  printf("\t1. Delivery\n");
  printf("\t2. Dine In\n");
  printf("\t3. Pick Up\n");
  printf("Dining Option: ");
  scanf("%d", &dining);
  printf("Thank you! Your information has been safely recorded!\n");
}

void confirm_account(struct customer *cust) {
  int input;
  printf("Here's what we got from you!\n");
  while (1) {
    print_customer(cust);
    printf("If there are no mistakes with the information above, enter \"0\" to check out.\n");
    printf("If there is something you want to modify, enter \"1\" to edit your account.\n");
    scanf("%d", &input);
    if (input == 0)
      break;
    else if (input == 1) {
      while (1) {
        printf("Select what you want to modify by entering the corresponding number:\n");
        printf("\t1. First Name\n");
        printf("\t2. Last Name\n");
        printf("\t3. Credit Card Number\n");
        printf("\t4. Dining Option\n");
        printf("If you want to stop modifying, enter \"0\" to exit.\n");
        scanf("%d", &input);
        if (input == 0)
          break;
        if (input == 1) {
          char first[256];
          printf("Enter your first name: ");
          scanf("%s", first);
          modify_first_name(cust, first);
          printf("Successfully modified first name...\n");
          break;
        }
        if (input == 2) {
          char last[256];
          printf("Enter your last name: ");
          scanf("%s", last);
          modify_last_name(cust, last);
          printf("Successfully modified last name...\n");
          break;
        }
        if (input == 3) {
          int card;
          printf("Enter your credit card number: ");
          scanf("%d", &card);
          modify_card(cust, card);
          printf("Successfully modified credit card number...\n");
          break;
        }
        if (input == 4) {
          int dining;
          printf("Modify your dining option by entering the corresponding number:\n");
          printf("\t1. Delivery\n");
          printf("\t2. Dine In\n");
          printf("\t3. Pick Up\n");
          printf("Dining Option: ");
          scanf("%d", &dining);
          modify_dining(cust, dining);
          printf("Successfully modified dining option...\n");
          break;
        }
        else
          printf("That's not a valid option.\n");
      }
    }
    else
      printf("That's not a valid option.\n");
  }
}

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
          printf("Sorry, we don't have this item available.\n"); // base case if customer inputs random characters not on menu
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

    //convert cost to double

    struct order * order_item = insert_order(cur_order, line, cost);
    cur_order = order_item;
  }
  print_list(cur_order);
  //go through linked list, calculate price, print out entire order
  price = get_price(cur_order);
  printf("Total Price: %0.2lf\n", price);

  // create customer account
  char* first_name;
  char* last_name;
  int credit_card;
  int dining_option;
  create_account(first_name, last_name, credit_card, dining_option);
  struct customer *cust_1 = new_customer(first_name, last_name, credit_card, dining_option);
  confirm_account(cust_1);

  // 
  snprintf(line, BUFFER_SIZE, "%0.2lf", price);
  write(fd2, line, sizeof(line));

  // possibly include customer name
  printf("Thank you, %s %s, for ordering at Cafe C! See you next time!\n", get_first_name(cust_1), get_last_name(cust_1));

  close(fd1);
  close(fd2);

  return 0;
}
