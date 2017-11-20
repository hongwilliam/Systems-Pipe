#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
  int f;
  int fds1[2]; //parent
  int fds2[2]; //child
  pipe(fds1);
  pipe(fds2);
  f = fork();

  //when the pipe is created and opened, both ends are opened for reading and writing
  //it's up to you to decide which the direction the data flows and which end is used for which

  int READ = 0;
  int WRITE = 1;

  //if child process
  if (f == 0){
    close(fds1[WRITE]); //we don't want parent to write
    int n;
    read(fds1[READ], &n, sizeof(n)); //rather, let's read
    printf("[child] doing quick maths on: %d \n", n);
    n += 2;
    sleep(2);
    close(fds2[READ]); //we don't want child to write
    write(fds2[WRITE], &n, sizeof(n)); //let's have child write to parent
  }

  //if parent process
  else{
    close(fds1[READ]); //we don't want parent to read
    int n = 12;
    write(fds1[WRITE], &n, sizeof(n)); //rather, we want parent to write
    printf("[parent] sending: %d \n", n);
    close(fds2[WRITE]); //we don't want child to write
    int j;
    read(fds2[READ], &j, sizeof(j)); //rather, the child should recieve data
    printf("[parent] recieved: %d \n", j); }

  return 0;
}
