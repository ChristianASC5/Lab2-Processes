/* timer.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int flag = 0;
volatile int alarm_calls = 0;

void handler(int signum)
{ // signal handler
    printf("Hello World!\n");
    flag = 1;
}

void time_handler(int signum)
{
    printf("\n%d seconds have passed\n", alarm_calls);
    exit(1);
}

int main(int argc, char *argv[])
{
    signal(SIGALRM, handler); // register handler to handle SIGALRM
    signal(SIGINT, time_handler);

    while (1)
    {
        alarm(1); // Schedule a SIGALRM for 1 second
        while (!flag)
            ;
        printf("Turing was right\n");
        flag = 0;

        alarm_calls++;
    }

    return 0; // never reached
}
