/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:17:10 by ekosnick          #+#    #+#             */
/*   Updated: 2025/06/27 12:36:18 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

// char	*cmd_path(char **path_split, char *cmd)
// {
// 	int		i;
// 	char	*full_path;
// 	char	*temp;
	
// 	i = -1;
// 	while (path_split[i++])
// 	{
// 		full_path = ft_strjoin(path_split[i], "/");
// 		if (!full_path)
// 		{
// 			ft_free_split(path_split);
// 			return (NULL);			
// 		}
// 		temp = full_path;
// 		full_path = ft_strjoin(full_path, cmd);
// 		free(temp);
// 		if (access(full_path, X_OK) == 0)
// 		{
// 			free_split(path_split);
// 			return (full_path);
// 		}
// 		free(full_path);
// 	}
// 	free_split(path_split);
// 	return (NULL);	
// }

// char	*pathfinder(char *cmd, char **env)
// {
// 	char	*path;
// 	char	*cmd_pt;
// 	char	**path_split;
// 	int		i;

// 	if (ft_strchr(cmd, '/'))
// 	{
// 		if (access(cmd, X_OK) == 0)
// 			return (ft_strdup(cmd));
// 		else
// 			return (NULL);
// 	}
// 	i = 0;
// 	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
// 		i++;
// 	if (!env[i])
// 		return (NULL);/* cmd ***** */
// 	path = env[i] + 5;
// 	path_split = ft_split(path, ':');
// 	if (!path_split)
// 		return (NULL);
// 	cmd_pt = cmd_path(path_split, cmd);
// 	return (cmd_pt);
// }

// void	laypipe(char *cmd_full, char **cmd_args, char **env)
// {
// 	int		fd[2];
// 	int		pid;

// 	pipe(fd);
// 	pid = fork();
// 	if (pid > 0)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], 0); /*STDIN_FILENO*/
// 		waitpid(pid, NULL, 0);
// 	}
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], 1); /*STDOUT_FILENO*/
// 		execve(cmd_full, cmd_args, env);
// 		perror("Child Error:");
// 		exit(EXIT_FAILURE);
// 	}
// }

void	dig_ditch(char *av, char **env)
{
	char	*cmd_full;
	char	**cmd_args;
	
	cmd_args = ft_split(av, ' ');
	if (!cmd_args)
	{
		perror("split failed");
		return;
	}
	if (!cmd_args[0] || !cmd_args[0][0])
	{
		printf("Empty command\n");
		ft_free_split(cmd_args);
		return;
	}
	cmd_full = pathfinder(cmd_args[0], env);
	if (!cmd_full)
	{
		printf("Command '%s' not found\n", cmd_args[0]);
		ft_free_split(cmd_args);
		return;
	}
	laypipe(cmd_full, cmd_args, env);
	free(cmd_full);
	ft_free_split(cmd_args);
}

void last_cmd(int ac, char **av, char **env)
{
	char	*cmd_full;
	char	**cmd_args;

	cmd_args = ft_split(av[ac - 2], ' ');
	if (!cmd_args)
	{
		printf("split failed\n");
		exit(127);
	}
	if (!cmd_args[0] || !cmd_args[0][0])
	{
		printf("Empty command\n");
		ft_free_split(cmd_args);
		exit(127);
	}
	cmd_full = pathfinder(cmd_args[0], env);
	if (!cmd_full)
	{
		printf("Command '%s' not found\n", cmd_args[0]);
		ft_free_split(cmd_args);
		exit(127);
	}
	execve(cmd_full, cmd_args, env);
}

void	here_doc_writer(char *delim)
{
	int		fd[2];
	char	*ln = NULL;
	size_t	len = ft_strlen(delim);

	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		while (1)
		{
			write(1, "here_doc: ", 10);
			ln = get_next_line(0);
			if (!ln || (ft_strncmp(ln, delim, len) == 0 && ln[len] =='\n'))
				break;
			write(fd[1], ln, ft_strlen(ln));
			free(ln);
		}
		free(ln);
		close(fd[1]);
		exit(0);
	}
	wait(NULL);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void bonus_delim(int ac, char **av, char **env)
{
	int	i;
	int	fdout;
	
	if (ft_strncmp(av[1],"here_doc", 8) == 0 && ac >= 6)
	{
		here_doc_writer(av[2]);
		i = 3;
		while (i < ac - 2)
			dig_ditch(av[i++], env);
		fdout = openfd(av[ac - 1], 2);
		dup2(fdout, 1);
		close(fdout);
		last_cmd(ac, av, env);
	}
	else
		ft_printf("./pipex here_doc LIMITER cmd1 cmd2 outfile\n");
}

int	main(int ac, char **av, char **env)
{
	int		fdin;
	int		fdout;
	int		i;

	if (ft_strncmp(av[1],"here_doc", 8) == 0)
	{
		bonus_delim(ac, av, env);
		return(0);
	}
	if (ac >= 5)
	{
		fdin = openfd(av[1], 0);
		dup2(fdin, 0);
		i = 2;
		while (i < ac -2)
			dig_ditch(av[i++], env);
		fdout = openfd(av[ac - 1], 1);
		dup2(fdout, 1);
		last_cmd(ac, av, env);
		return (0);
	}
	else
		ft_printf("./pipex [infile | here_doc LIMITER] cmd1 cmd2 outfile\n");
	return (1);
}
