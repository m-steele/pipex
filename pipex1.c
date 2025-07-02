/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:17:10 by ekosnick          #+#    #+#             */
/*   Updated: 2025/07/02 13:20:24 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	dig_ditch(char *av, char **env)
// {
// 	char	*cmd_full;
// 	char	**cmd_args;

// 	cmd_args = ft_split(av, ' ');
// 	if (!cmd_args)
// 	{
// 		perror("split failed");
// 		return ;
// 	}
// 	if (!cmd_args[0] || !cmd_args[0][0])
// 	{
// 		printf("Empty command\n");
// 		ft_free_split(cmd_args);
// 		return ;
// 	}
// 	cmd_full = pathfinder(cmd_args[0], env);
// 	if (!cmd_full)
// 	{
// 		printf("Command '%s' not found\n", cmd_args[0]);
// 		ft_free_split(cmd_args);
// 		return ;
// 	}
// 	laypipe(cmd_full, cmd_args, env);
// 	free(cmd_full);
// 	ft_free_split(cmd_args);
// }

// void	last_cmd(int ac, char **av, char **env)
// {
// 	char	*cmd_full;
// 	char	**cmd_args;

// 	cmd_args = ft_split(av[ac - 2], ' ');
// 	if (!cmd_args)
// 	{
// 		printf("split failed\n");
// 		exit(127);
// 	}
// 	if (!cmd_args[0] || !cmd_args[0][0])
// 	{
// 		printf("Empty command\n");
// 		ft_free_split(cmd_args);
// 		exit(127);
// 	}
// 	cmd_full = pathfinder(cmd_args[0], env);
// 	if (!cmd_full)
// 	{
// 		printf("Command '%s' not found\n", cmd_args[0]);
// 		ft_free_split(cmd_args);
// 		exit(127);
// 	}
// 	execve(cmd_full, cmd_args, env);
// 	perror("execve failed");
// 	free(cmd_full);
// 	ft_free_split(cmd_args);
// 	exit(1);
// }

// int	main(int ac, char **av, char **env)
// {
// 	int		fdin;
// 	int		fdout;
// 	int		i;

// 	if (ac == 5)
// 	{
// 		if (access(av[1], F_OK) != 0)
// 		{
// 			perror(av[1]);
// 			return (1);
// 		}
// 		fdin = openfd(av[1], 0);
// 		dup2(fdin, 0);
// 		i = 2;
// 		printf("Before digditch loop ->	i = %i\n", i);
// 		while (i < ac -2)
// 			dig_ditch(av[i++], env);
// 		printf("After digditch loop ->	i = %i\n", i);
// 		fdout = openfd(av[ac - 1], 1);
// 		printf("openfd fdout = %i\n", fdout);
// 		dup2(fdout, 1);
// 		last_cmd(ac, av, env);
// 		printf("After the last command\n");
// 		return (0);
// 	}
// 	else
// 		ft_printf("./pipex infile cmd1 cmd2 outfile\n");
// 	return (1);
// }

void	child1(int pid1, int fdin, int *pipefd, char **av, char **env)
{
	int saved_cmd;

	if (pid1 == 0)
	{
		if (dup2(fdin, STDIN_FILENO) == -1)
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

void	child2(int pid2, int fdout, int *pipefd, char **av, char **env)
{
	int saved_cmd;
	
	if (pid2 == 0)
	{
		saved_cmd = dup(STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		if (dup2(fdout, STDOUT_FILENO) == -1)
		{
			ft_printf("Outfile '%s' failed\n", av[4]);
			exit(1);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		exec_cmd(saved_cmd, av[3], env);
	}
}

// void	child2(int pid2, int fdout, int *pipefd, char **av, char **env)
// {
// 	if (pid2 == 0)
// 	{
// 		dup2(pipefd[0], STDIN_FILENO);
// 		dup2(fdout, STDOUT_FILENO);
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		exec_cmd(av[3], env);
// 	}
// }

void	parent(int pid1, int pid2, int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);	
}

int	start_pipex(int ac, char **av, char **env)
{
	int		fdin;
	int		fdout;
	int		pipefd[2];
	int		pid1;
	int		pid2;

	if (access(av[1], F_OK) != 0)
	{
		perror(av[1]);
		return (1);
	}
	pipe(pipefd);
	fdin = openfd(av[1], 0);
	fdout = openfd(av[ac - 1], 1);
	if (fdin < 0 || fdout < 0)
	{
		perror("open");
		return (1);
	}
	pid1 = fork();
	child1(pid1, fdin, pipefd, av, env);
	pid2 = fork();
	child2(pid2, fdout, pipefd, av, env);
	parent(pid1, pid2, pipefd);
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


// int	main(int ac, char **av, char **env)
// {
// 	int		fdin;
// 	int		fdout;
// 	int		pipefd[2];
// 	int		pid1;
// 	int		pid2;

// 	if (ac == 5)
// 	{
// 		if (access(av[1], F_OK) != 0)
// 		{
// 			perror(av[1]);
// 			return (1);
// 		}
// 		pipe(pipefd);
// 		fdin = openfd(av[1], 0);
// 		fdout = openfd(av[ac - 1], 1);
// 		if (fdin < 0 || fdout < 0)
// 		{
// 			perror("open");
// 			return (1);
// 		}
// 		pid1 = fork();
// 		child1(pid1, fdin, pipefd, av, env);
// 		pid2 = fork();
// 		child2(pid2, fdout, pipefd, av, env);
// 		parent(pid1, pid2, pipefd);
// 		return (0);
// 	}
// 	else
// 		ft_printf("./pipex infile cmd1 cmd2 outfile\n");
// 	return (1);
// }
