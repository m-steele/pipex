#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int fd1[2];
	int pid;

	if (pipe(fd1) != 0)
		return (1);
	if (pipe(fd1) != 0)
		return (1);
	pid = fork();

	if (pid > 0)
	{
		dup2(fd1[1], STDOUT_FILENO); /*parent creates OUTPUT for child*/
		close(fd1[0]);
		close(fd1[1]);
		execlp("ls", "ls", "-l", NULL);
		waitpid(pid, NULL, 0);
	}
	if (pid == 0)
	{
		dup2(fd1[0], STDIN_FILENO); /*child INPUTS the product of the parent*/
		close(fd1[0]);
		close(fd1[1]);
		execlp("sort", "sort", "-r", NULL);
	}
	close(fd1[0]);
	close(fd1[1]);
	return (0);
}