/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peatjohnston <peatjohnston@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:58:31 by ekosnick          #+#    #+#             */
/*   Updated: 2024/10/03 17:40:45 by peatjohnsto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// file descriptor Put number func
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	single;

	if (n == INT_MIN)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		ft_putnbr_fd(n, fd);
	}
	else
	{
		if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
		else
		{
			single = n + 48;
			write(fd, &single, 1);
		}
	}
}
