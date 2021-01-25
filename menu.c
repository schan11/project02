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

//displays the menu of items available for purchase
void print_menu(char * filename){
  FILE * fp;
  char menu;

  fp = fopen(filename, "r");
  menu = fgetc(fp);
  while (menu != EOF){
    printf("%c", menu);
    menu = fgetc(fp);
  }

  fclose(fp);
}

//sets up the main menu
int setup(){
  int choice;
  char setup[] = "./setup";
  print_menu(setup);
  printf("Press a number to begin: ");
  scanf("%d", &choice);
  return choice;
}

//chooses category
void choose_category(int start){
  char teas[] = "./teas";
  char desserts[] = "./desserts";
  char appetizers[] = "./appetizers";

  if (start == 0) print_menu(teas);
  else if (start == 1) print_menu(desserts);
  else if (start == 2) print_menu(appetizers);
}

//allows customer to place their order
void order(){
  int fd1, fd2, i, item_count=0;
  char order[BUFFER_SIZE], line[BUFFER_SIZE];

  //create and open client pipe for writing
  mkfifo("menu_p", 0644);

  fd1 = open("menu_p", O_WRONLY);

  while (1){
    fseek(stdin,0,SEEK_END);

    //prompt user for input to order
    if (item_count == 0) printf("What would you like to order? ");
    else printf("Anything else? ");
    fgets(order, sizeof(order), stdin);

    //go back to main menu if requested by customer (entering 0)
    const char *c = order;

    //remove new line character from end
    for (i=0; order[i]; i++){
      if (order[i]=='\n')order[i]='\0';
    }

    //write the order to the system end
    write(fd1, order, sizeof(order));

    if (strncmp(c, "0",1)==0) {
      int main_menu = setup();
      choose_category(main_menu);
      continue;
    }

    if (strncmp(order, "E",1)==0) {
      printf("Proceeding to checkout...\n");
      break;
    }

    fd2 = open("system_p", O_RDONLY);
    read(fd2, line, sizeof(line));
    printf("[%s]\n", line);

    item_count++;
  }

  read(fd2, line, sizeof(line));
  printf("Your total price is: [%s]\n", line);

  close(fd1);
  close(fd2);
}

void create_account(char* first, char* last, long card, int dining) {
  printf("Before we proceed to checkout, we need some information from you.\n");
  printf("First name: ");
  scanf("%s", first);
  printf("Last name: ");
  scanf("%s", last);
  printf("Credit Card Number: ");
  scanf("%lu", &card);
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
          long card;
          printf("Enter your credit card number: ");
          scanf("%lu", &card);
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

//main
int main(){
  //set up main menu, choose category, and allow customer to order
  int main_menu = setup();
  choose_category(main_menu);
  order();

// create customer account
  char first_name[256];
  char last_name[256];
  long credit_card;
  int dining_option;
  create_account(first_name, last_name, credit_card, dining_option);
  struct customer *cust_1 = new_customer(first_name, last_name, credit_card, dining_option);
  confirm_account(cust_1);

  // possibly include customer name
  printf("Thank you, %s %s, for ordering at Cafe C! See you next time!\n", get_first_name(cust_1), get_last_name(cust_1));

  return 0;
}
