/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:17:10 by ekosnick          #+#    #+#             */
/*   Updated: 2025/05/30 17:20:00 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int	openfd(char *fd, int in_out)
{
	if (in_out == 0)
		return(open(fd, O_RDONLY));
	if (in_out == 1)
		return(open(fd, O_WRONLY | O_CREAT | S_IRUSR | S_IWUSR,
			O_TRUNC | S_IROTH | S_IWOTH));
	else
		return (-1);
}

char *pathfinder(char *cmd, char *env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	
}

int	main(int ac, char **av, char **env)
{
	int	infile;
	int	outfile;

	if (ac >= 5)
	{
		infile = openfd(av[2], 0);
		outfile = openfd(av[ac - 1], 1);
		if (dup2(infile, 0) == -1)
			perror("Error in:");
		if (dup2(outfile, 1) == -1)
			perror("Error out:");

// pathfinder(env);/*get use PATH and : to find commands*/
// cmd(); /*write a function that implements a comand from pathfinder()*/
/*once you have these working then you can start creating the pipes*/
		close(infile);
		close(outfile);
	}
	else
		perror("Error ac:");
	return (1);
}