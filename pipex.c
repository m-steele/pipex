/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:17:10 by ekosnick          #+#    #+#             */
/*   Updated: 2025/07/02 14:11:34 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(t_pip p, int *pipefd, char **av, char **env)
{
	int	saved_cmd;

	if (p.pid1 == 0)
	{
		if (dup2(p.fdin, STDIN_FILENO) == -1)
		{
			ft_printf("Input file:'%s' not found\n", av[1]);
			exit(1);
		}
		saved_cmd = dup(STDOUT_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_cmd(saved_cmd, av[2], env);
	}
}

void	child2(t_pip p, int *pipefd, char **av, char **env)
{
	int	saved_cmd;

	if (p.pid2 == 0)
	{
		saved_cmd = dup(STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		if (dup2(p.fdout, STDOUT_FILENO) == -1)
		{
			ft_printf("Outfile '%s' failed\n", av[4]);
			exit(1);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		exec_cmd(saved_cmd, av[3], env);
	}
}

void	parent(t_pip p, int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(p.pid1, NULL, 0);
	waitpid(p.pid2, NULL, 0);
}

int	start_pipex(int ac, char **av, char **env)
{
	t_pip	p;
	int		pipefd[2];

	if (access(av[1], F_OK) != 0)
	{
		perror(av[1]);
		return (1);
	}
	pipe(pipefd);
	p.fdin = openfd(av[1], 0);
	p.fdout = openfd(av[ac - 1], 1);
	if (p.fdin < 0 || p.fdout < 0)
	{
		perror("open");
		return (1);
	}
	p.pid1 = fork();
	child1(p, pipefd, av, env);
	p.pid2 = fork();
	child2(p, pipefd, av, env);
	parent(p, pipefd);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
	{
		ft_printf("./pipex infile cmd1 cmd2 outfile\n");
		return (1);
	}
	start_pipex(ac, av, env);
	return (0);
}
