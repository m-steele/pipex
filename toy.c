#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

/*dup2()*/
// int main()
// {
// 	int fd;

// 	fd = open("YOU", O_WRONLY | O_CREAT, 0644); /*create fd*/
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	printf("YOU SUCK\nYOU SUCK\nYOU SUCK\n"); /*creates content for fd*/

// 	return (0);
// }

/*access()*/
// int main()
// {
// 	if (access("YOU", R_OK) != -1)
// 		printf("I have access to YOU\n");
// 	else
// 		printf("I do not have access to YOU\n");
// 	return (0);
// }

/*execve90 --> for executing a command, but need to know path in environment!*/
// int main()
// {
// 	char *arg[3];

// 	arg[0] = "ls";
// 	arg[1] = "-l";
// 	arg[2] = NULL;

// 	execve("/bin/ls", arg, NULL);
// 	printf("This line will not be executed,\nunless something fucked up\n");
// 	return (0);
// }

/*using fort() and pipe() to make the child parent process*/
int main()
{
	int fd[2];
	pid_t pid;
	char buff[13];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		write(fd[1], "Hello parent!", 13);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		read(fd[0], buff, 13);
		close(fd[0]);
		printf("message from the child: '%s'\n", buff);
		exit(EXIT_SUCCESS);
	}
	// waipid(pid == 0)

	// return (0);
}

/*unlink()*/
// int main()
// {
// 	if (unlink("YOU") == 0)
// 		printf("You are deleted\n");
// 	else
// 		printf("why is YOU still here?\n");
// 	return(0);
// }

/*wait()*/
// 

// int create_fd()
// {
// 	int fd;

// 	// Open file, create if not exists, "truncate" if exists (clear its contents)
// 	// Use O_APEND if you want to append to the contents that already exist
// 	fd = open("YOU", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1) {
// 		perror("open in create_fd failed");
// 		return (-1); // Indicate failure
// 	}
// 	// Redirect STDOUT_FILENO to the file descriptor 'fd'
// 	if (dup2(fd, STDOUT_FILENO) == -1) {
// 		perror("dup2 (to redirect stdout to file) failed");
// 		close(fd);
// 		return (-1);
// 	}
// 	// This printf now writes to the file "YOU"
// 	printf("YOU SUCK!.\nYOU SUCK!.\nYOU SUCK!.\n");
// 	close(fd);
// 	return (0); // Indicate success
// }

// int main()
// {
// 	// Call create_fd() to create and populate the file "YOU"
// 	// if (create_fd() == 0)
// 	if (create_fd() != 0)
// 		return (printf("Failed to create or write to file 'YOU'.\n"));
// 	if (access("YOU", R_OK) != -1)
// 		printf("I have read access to YOU.\n");
// 	else
// 	{
// 		perror("access check for R_OK on 'YOU' failed");
// 		printf("I do not have read access to YOU.\n");
// 	}
// 	return (0);
// }

