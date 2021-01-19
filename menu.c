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

//allows customer to place their order
void order(){
  int fd1, fd2, i, item_count=0;
  char order[BUFFER_SIZE], line[BUFFER_SIZE];

  mkfifo("menu_p", 0644);
  //printf("made menu pipe\n");

  fd1 = open("menu_p", O_WRONLY);
  //printf("%d\n", fd1);
  //if (fd1==-1)printf("error: %s\n", strerror(errno));

  //printf("opened pipes in menu\n");
  while (1){
    fseek(stdin,0,SEEK_END);
    //printf("%d\n", item_count);
    if (item_count == 0) printf("What would you like to order? ");
    else printf("Anything else? ");
    fgets(order, sizeof(order), stdin);
    //printf("\n");
    //remove new order character from end
    for (i=0; order[i]; i++){
      if (order[i]=='\n')order[i]='\0';
    }
    write(fd1, order, sizeof(line));
    //printf("wrote to menu pipe\n");
    fd2 = open("system_p", O_RDONLY);
    read(fd2, line, sizeof(line));
    printf("[%s]\n", line);

    item_count++;
  }

  close(fd1);
  close(fd2);
}

//main
int main(){
  int start = setup();

  char teas[] = "./teas";
  char desserts[] = "./desserts";
  char appetizers[] = "./appetizers";

  if (start == 0) print_menu(teas);
  else if (start == 1) print_menu(desserts);
  else if (start == 2) print_menu(appetizers);

  order();

  return 0;
}
