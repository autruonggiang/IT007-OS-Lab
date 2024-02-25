/*########################################
#University of Information Technology 	 #
#IT007 Operating System		      	 	 #
#Au Truong Giang, 21522019		 		 #
#File: bt1.c				 			 #
########################################*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int loop = 1;

void on_sigint() 
{
	printf("\nYou are pressed CTRL+C! Goodbye!\n");
	loop = 0;
}

int main()
{
	loop = 1;
	printf("Welcome to IT007, I am 21522019\n");
	pid_t pid;
	pid = fork();

	if (pid == 0)
	{
		system("gedit abcd.txt");
	}

	else 
	{
		signal(SIGINT, on_sigint);
	}
		while(loop){}

	return 0;
}
