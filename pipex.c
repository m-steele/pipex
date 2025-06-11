/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:17:10 by ekosnick          #+#    #+#             */
/*   Updated: 2025/06/11 11:03:58 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

// int	openfd(char *file_path, int in_out) /*consider adding this to libft*/
// {
// 	int	fd;

// 	if (in_out == 0)
// 	{
// 		fd = open(file_path, O_RDONLY);
// 		if (fd == -1)
// 			perror("Infile open error");
// 		return(fd);
// 	}
// 	if (in_out == 1)
// 	{
// 		fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC,
// 				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH); // Mode 0664 (rw-rw-r--)
// 		if (fd == -1)
// 		{
// 			perror("Outfile open error");
// 			return(-1);
// 		}
// 		return(fd);
// 	}
// }

int	openfd(char *fd, int in_out) /*consider adding this to libft*/
{
	if (in_out == 0)
		return(open(fd, O_RDONLY));
	if (in_out == 1)
		return(open(fd, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | /*S_IWGRP |*/ S_IROTH));
	else
		return (-1);
}

void	ft_free_split(char **split) /*add this to libft*/
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
		return (NULL);/* cmd ***** */
	path = env[i] + 5;
	path_split = ft_split(path, ':');
	if (!path_split)
		return (NULL);
	cmd_pt = cmd_path(path_split, cmd);
	return (cmd_pt);
}

void	laypipe(char *cmd_full, char **cmd_args, char **env)
{
	int		fd[2];
	int		pid;

	pipe(fd);
	pid = fork();
	if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], 0); /*STDIN_FILENO*/
		waitpid(pid, NULL, 0);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1); /*STDOUT_FILENO*/
		execve(cmd_full, cmd_args, env);
		perror("Child Error:");
		exit(EXIT_FAILURE);
	}
}

void	dig_ditch(char *av, char **env)
{
	char	*cmd_full;
	char	**cmd_args;
	
	cmd_args = ft_split(av, ' ');
	if (!cmd_args)
		perror("split failed");
	cmd_full = pathfinder(cmd_args[0], env);
	if (!cmd_full)
	{
		printf("Command not found\n");
		ft_free_split(cmd_args);
	}
	laypipe(cmd_full, cmd_args, env);
	free(cmd_full);
	ft_free_split(cmd_args);
}


int	main(int ac, char **av, char **env)
{
	// char	**cmd_args;
	// char	*cmd_full;
	int		fdin;
	int		fdout;
	int		i;

	printf("ac = %d\n", ac);
	if (ac > 4)
	{
		fdin = openfd(av[1], 0);
		dup2(fdin, 0);
		close(fdin);
		i = 3;
		while (i < ac -2)
		{
			dig_ditch(av[i], env);
			// cmd_args = ft_split(av[i], ' ');
			// if (!cmd_args)
			// {
			// 	perror("split failed");
			// 	return (1);
			// }
			// cmd_full = pathfinder(cmd_args[0], env);
			// if (!cmd_full)
			// {
			// 	printf("Command not found\n");
			// 	ft_free_split(cmd_args);
			// 	return (1);
			// }
			// laypipe(cmd_full, cmd_args, env);
			// free(cmd_full);
			// ft_free_split(cmd_args);
			i++;
		}
/****************************************** */
/*		The problem here is that dig_ditch()*/
/*		uses laypipe() which uses fork()	*/
/*		and we do not want to fork the last */
/*		command								*/
/****************************************** */
		dig_ditch(av[i], env);

		// cmd_args = ft_split(av[ac - 2], ' ');
		fdout = openfd(av[ac - 1], 1);
		dup2(fdout, 1);
		close(fdout);
		// cmd_full = pathfinder(cmd_args[0], env);
		// if (!cmd_full)
		// {
		// 	printf("command not found");
		// 	ft_free_split(cmd_args);
		// 	return (1);
		// }
		// if (execve(cmd_full, cmd_args, env) == -1)
		// {
		// 	perror("excecve failed:");
		// 	exit(EXIT_FAILURE);
		// }
		return (0);
	}
	else
		printf("You messed up\n");
	return (1);
}

// PRINT THE ENVIRONMENT
// int main(int ac, char **arg, char **env)
// {
// 	int i = 0;

// 	printf("Environment Variables:\n");
// 	while (env[i] != NULL) {
// 		printf("%s\n", env[i]);
// 		i++;
// 	}
// 	return (0);
// }
