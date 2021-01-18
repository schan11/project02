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

int start_up(){
  int choice;
  char start[] = "./start";
  print_menu(start);
  printf("Press a number to begin: ");
  scanf("%d", &choice);
  return choice;
}

//main
int main(){
  int setup = start_up();

  char items[] = "./items";
  if (setup == 0) print_menu(items);

  int fd1, fd2, i;
  char order[BUFFER_SIZE], line[BUFFER_SIZE];

  mkfifo("menu_p", 0644);
  //printf("made menu pipe\n");

  fd1 = open("menu_p", O_WRONLY);
  //printf("%d\n", fd1);
  //if (fd1==-1)printf("error: %s\n", strerror(errno));

  //printf("opened pipes in menu\n");
  while (1){
    fseek(stdin,0,SEEK_END);
    printf("What would you like to order? ");
    fgets(order, sizeof(order), stdin);
    //printf("\n");
    //remove new order character from end
    for (i=0; order[i]; i++){
      if (order[i]=='\n')order[i]='\0';
    }
    write(fd1, order, sizeof(line));
    //printf("wrote to menu pipe\n");
    close(fd1);

    fd2 = open("system_p", O_RDONLY);

    read(fd2, line, sizeof(line));
    printf("[%s]\n", line);

    close(fd2);

  }

  return 0;
}
