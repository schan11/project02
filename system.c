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

int main(){
  char order[BUFFER_SIZE], line[BUFFER_SIZE];
  int fd1, fd2, i;
  //printf("got here 1\n");

  mkfifo("system_p", 0644);
  fd1 = open("menu_p", O_RDONLY);

  //printf("opened menu pipe for read\n");
  while (1){
    read(fd1, order, sizeof(order));
    fd2 = open("system_p", O_WRONLY);

    //printf("opened system pipe for writing\n");
    strncpy(line, order,sizeof(line)-1);
    write(fd2, line, sizeof(line));

  }

  close(fd1);
  close(fd2);

  return 0;
}
