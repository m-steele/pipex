/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_xx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:51:25 by ekosnick          #+#    #+#             */
/*   Updated: 2024/10/19 11:24:01 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoupperhex(unsigned long num)
{
	char			*str;
	char			*hex;
	unsigned long	x;
	int				len;

	hex = "0123456789ABCDEF";
	if (num == 0)
		return (ft_strdup("0"));
	x = num;
	len = 0;
	while (x)
	{
		x /= 16;
		len++;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str[len] = '\0';
	while (len--)
	{
		str[len] = hex[num % 16];
		num /= 16;
	}
	return (str);
}

unsigned int	process_xx(va_list args)
{
	unsigned int	n;
	unsigned int	xx;
	char			*xx_s;
	char			*s;

	n = 0;
	xx = va_arg(args, int);
	xx_s = ft_itoupperhex(xx);
	if (!xx_s)
		xx_s = "(null)";
	s = xx_s;
	while (*s)
	{
		write(1, s, 1);
		s++;
		n++;
	}
	free(xx_s);
	return (n);
}
