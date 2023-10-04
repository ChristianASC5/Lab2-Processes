#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUF_SIZE 100

void ChildProcess(void);  /* child process prototype  */
void ParentProcess(void); /* parent process prototype */

int main(void)
{
     srand(time(NULL));

     pid_t child_a, child_b;

     child_a = fork();
     if (child_a == 0)
     {
          ChildProcess();
     }
     else
     {
          child_b = fork();

          if (child_b == 0)
          {
               ChildProcess();
          }
          else
          {
               ParentProcess();
          }
     }
}

void ChildProcess(void)
{
     int num = (rand() % 30) + 1;
     char buf[BUF_SIZE];

     for (int i = 0; i < num; i++)
     {
          sprintf(buf, "Child Pid: %d is going to sleep!\n", getpid());
          write(1, buf, strlen(buf));

          sleep((rand() % 10) + 1);

          sprintf(buf, "Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
          write(1, buf, strlen(buf));
     }

     exit(0);
}

void ParentProcess(void)
{
     int child_pid;
     char buf[BUF_SIZE];

     for (int i = 0; i < 2; i++)
     {
          child_pid = wait(NULL);
          sprintf(buf, "Child Pid: %d has completed\n", child_pid);
          write(1, buf, strlen(buf));
     }
}