/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:20:49 by ekosnick          #+#    #+#             */
/*   Updated: 2025/06/29 13:58:41 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*cmd_path(int i, char **path_split, char *cmd)
{
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
	cmd_pt = cmd_path(i, path_split, cmd);
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
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execve(cmd_full, cmd_args, env);
		perror("Child Error:");
		exit(EXIT_FAILURE);
	}
}

void	here_doc_child_writer(char *delim, int fd)
{
	char	*ln;
	size_t	len;

	ln = NULL;
	len = ft_strlen(delim);
	while (1)
	{
		write(1, "here_doc: ", 10);
		ln = get_next_line(0);
		if (!ln || (ft_strncmp(ln, delim, len) == 0 && ln[len] == '\n'))
			break ;
		write(fd, ln, ft_strlen(ln));
		free(ln);
	}
	free(ln);
	close(fd);
	exit(0);
}
