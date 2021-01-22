#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

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
    write(fd1, order, sizeof(line));

    if (strncmp(c, "0",1)==0) {
      int main_menu = setup();
      choose_category(main_menu);
    }

    if (strncmp(order, "1",1)==0) {
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

//main
int main(){
  //set up main menu, choose category, and allow customer to order
  int main_menu = setup();
  choose_category(main_menu);
  order();

  printf("checkout here\n");

  return 0;
}
