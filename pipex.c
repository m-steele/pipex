/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:17:10 by ekosnick          #+#    #+#             */
/*   Updated: 2025/06/30 16:42:59 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	dig_ditch(char *av, char **env)
{
	char	*cmd_full;
	char	**cmd_args;
	int		pid;

	printf("dig_ditch(): splitting command '%s'\n", av);
	cmd_args = ft_split(av, ' ');
	if (!cmd_args || !cmd_args[0])
	{
		printf("Empty command\n");
		ft_free_split(cmd_args);
		return (-1);
	}
	cmd_full = pathfinder(cmd_args[0], env);
	if (!cmd_full)
	{
		printf("Command '%s' not found\n", cmd_args[0]);
		ft_free_split(cmd_args);
		return (-1);
	}
	pid = laypipe(cmd_full, cmd_args, env);
	free(cmd_full);
	ft_free_split(cmd_args);
	return (pid);
}

void	last_cmd(int ac, char **av, char **env)
{
	char	*cmd_full;
	char	**cmd_args;
	// int		pid;

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
	// pid = laypipe(cmd_full, cmd_args, env);
	// free(cmd_full);
	// ft_free_split(cmd_args);
	// return (pid);
	execve(cmd_full, cmd_args, env);
}

int	main(int ac, char **av, char **env)
{
	int	fdin;
	int	fdout;
	int	i;
	int j = 0;
	int pids[ac];

	if (ac == 5)
	{
		// if (access(av[1], F_OK) != 0 || access(av[1], R_OK) != 0)
		// {
		// 	perror(av[1]);
		// 	return (1);
		// }
		fdin = openfd(av[1], 0);
		dup2(fdin, 0);
		close(fdin);
		i = 2;

		while (i < ac - 2)
			pids[j++] = dig_ditch(av[i++], env);
			// dig_ditch(av[i++], env);
			
		printf("After digditch loop ->	j = %i\ni = %i\n", j, i);
		while (j--)
			waitpid(pids[j], NULL, 0);
		printf("Second j = %i\ni = %i\n", j, i);
		fdout = openfd(av[ac - 1], 1);
		dup2(fdout, 1);
		close(fdout);
/*	THERE IS SOME TYPE OF PROBLEM HERE WHRE EITHER WITH MATING
THE OUTFILE OR THE EXECUTION OF THE LAST COMMAND
FARANCE SAYS THAT YOU JUST HANDLE THE CHILD AS YOU DO IN LAYPIPE()
AND THAT SHOULD DEAL WITH IT.*/

		last_cmd(ac, av, env);
		return (0);
	}
	else
		ft_printf("./pipex infile cmd1 cmd2 outfile\n");
	return (1);
}
	