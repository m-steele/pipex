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
	int fd2[2];
	int pid;
	int pid1; /*child 1*/
	int pid2;	/*child 2*/

	if (pipe(fd1) != 0)
		return (1);
	if (pipe(fd2) != 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (4);
	if (pid == 0)
	{
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		execlp("ls", "ls", "-l", NULL);
		// perror("execlp ls failed");
		// exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		dup2(fd1[0], STDIN_FILENO);
		dup2(fd2[1], STDOUT_FILENO);
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		execlp("sort", "sort", NULL);
		// perror("execlp sort failed");
		// exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid2 == 0)
	{
		dup2(fd2[0], STDIN_FILENO);
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		execlp("grep", "grep", "toy", NULL);
		// perror("execlp grep failed");
		// exit(EXIT_FAILURE);
	}
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}