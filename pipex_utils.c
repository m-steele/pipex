/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:20:49 by ekosnick          #+#    #+#             */
/*   Updated: 2025/06/12 12:32:10 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

char	*cmd_path(char **path_split, char *cmd)
{
	int		i;
	char	*full_path;
	char	*temp;
	
	i = 0;
	while (path_split[i++])
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