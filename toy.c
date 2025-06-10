#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "libft/libft.h"

void	ft_free_split(char **split)
{
	char **temp = split;
	while (*split)
		free(*split++);
	free(temp);
}

char	*cmd_path(char **path_split, char *cmd)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	while (path_split[i])
	{
		full_path = ft_strjoin(path_split[i], "/");
		if (!full_path)
		{
			ft_free_split(path_split);
			return (NULL);			
		}
		temp = full_path;
		full_path = ft_strjoin(full_path, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(path_split);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(path_split);
	return (NULL);	
}

char	*pathfinder(char *cmd, char **env)
{
	char	*path;
	char	*cmd_pt;
	char	**path_split;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	path = env[i] + 5;
	path_split = ft_split(path, ':');
	if (!path_split)
		return (NULL);
	cmd_pt = cmd_path(path_split, cmd);
	return (cmd_pt);
}

int main(int ac, char **av, char **env)
{
	char	cmd_input[1024];
	char	*cmd_full;
	size_t	len;

	printf("Enter command: ");
	if (fgets(cmd_input, sizeof(cmd_input), stdin) != NULL)
	{
		len = strlen(cmd_input);
		if (len > 0 && cmd_input[len - 1] == '\n')
			cmd_input[len - 1] = '\0';
		if (strlen(cmd_input) > 0)
			cmd_full = pathfinder(cmd_input, env);
			if (cmd_full)
			{
				printf("cmd path = %s\n", cmd_full);
				free(cmd_full);
			}
	}
	else
		printf("Failed to read command from stdin.\n");
	return (0);
}

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
// int main()
// {
// 	int fd[2];
// 	pid_t pid;
// 	char buff[13];

// 	if (pipe(fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	// printf("fd0: %d;\nfd1: %d\n", fd[0], fd[1]);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		write(fd[1], "Hello parent!", 13);
// 		close(fd[1]);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		read(fd[0], buff, 13);
// 		close(fd[0]);
// 		printf("message from the child: '%s'\n", buff);
// 		exit(EXIT_SUCCESS);
// 	}
// 	printf("fd0: %d;\nfd1: %d\n", fd[0], fd[1]);
// 	// close(fd[0]);
// 	// close(fd[1]);
// 	// waipid(pid == 0)
// 	// return (0);
// }

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

