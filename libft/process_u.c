/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:12:43 by ekosnick          #+#    #+#             */
/*   Updated: 2024/10/19 11:25:55 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa(unsigned int u)
{
	char			*str;
	int				len;
	unsigned int	ut;

	ut = u;
	len = 0;
	if (u == 0)
		return (ft_strdup("0"));
	while (ut)
	{
		ut /= 10;
		len ++;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (u % 10) + '0';
		u /= 10;
	}
	return (str);
}

unsigned int	process_u(va_list args)
{
	unsigned int	n;
	unsigned int	u;
	char			*u_s;
	char			*s;

	n = 0;
	u = va_arg(args, int);
	u_s = ft_utoa(u);
	if (!u_s)
		u_s = "(NULL)";
	s = u_s;
	while (*s)
	{
		write(1, s, 1);
		s++;
		n++;
	}
	free(u_s);
	return (n);
}
