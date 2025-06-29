/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:17:10 by ekosnick          #+#    #+#             */
/*   Updated: 2025/06/29 15:27:14 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dig_ditch(char *av, char **env)
{
	char	*cmd_full;
	char	**cmd_args;

	cmd_args = ft_split(av, ' ');
	if (!cmd_args)
	{
		perror("split failed");
		return ;
	}
	if (!cmd_args[0] || !cmd_args[0][0])
	{
		printf("Empty command\n");
		ft_free_split(cmd_args);
		return ;
	}
	cmd_full = pathfinder(cmd_args[0], env);
	if (!cmd_full)
	{
		printf("Command '%s' not found\n", cmd_args[0]);
		ft_free_split(cmd_args);
		return ;
	}
	laypipe(cmd_full, cmd_args, env);
	free(cmd_full);
	ft_free_split(cmd_args);
}

void	last_cmd(int ac, char **av, char **env)
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

	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		here_doc_child_writer(delim, fd[1]);
	}
	wait(NULL);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	bonus_delim(int ac, char **av, char **env)
{
	int	i;
	int	fdout;

	if (ft_strncmp(av[1], "here_doc", 8) == 0 && ac >= 6)
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

	if (ac >= 6 && ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		bonus_delim(ac, av, env);
		return (0);
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
