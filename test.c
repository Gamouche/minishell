
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int g_pid;

void sighandler(int signum) {
   printf("Caught signal %d, coming out...\n", signum);

   if (signum == SIGINT)
   {
   		kill(g_pid, signum);
   }
}

int main(void)
{

	signal(SIGINT, sighandler);
	signal(SIGSEGV, sighandler);

	
	pid_t	pid;
	int		status = 0;

	pid = fork();
	g_pid = pid;

	if (pid == 0) // fils
	{
		char	*args[4] = { "ls", "-R", "/", NULL };
		execve("/bin/ls", args, NULL);
		printf("FAIL EXECVE\n");
		exit(42);
	}

	else
	{
		wait(&status);
	}


	printf("status = %d\n", status);
	while (1) {    printf("je sleep\n")   ;   sleep(10);   }

	return 0;
}
