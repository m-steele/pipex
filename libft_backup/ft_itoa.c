/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peatjohnston <peatjohnston@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:04:07 by ekosnick          #+#    #+#             */
/*   Updated: 2024/10/03 18:24:47 by peatjohnsto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Takes an int and transforms it to ascii
#include "libft.h"

void	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static char	*ft_to_ascii(int n)
{
	char	*str;
	int		nums;
	int		temp;

	nums = 0;
	temp = n;
	while (temp != 0)
	{
		nums++;
		temp /= 10;
	}
	str = (char *)malloc((nums + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[nums--] = '\0';
	while (n > 0)
	{
		str[nums--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

static char	*ft_neg_ascii(int n)
{
	char	*z;
	char	*neg;
	char	*s;

	n = n * -1;
	s = "-";
	z = ft_to_ascii(n);
	if (!z)
		return (NULL);
	neg = ft_strjoin(s, z);
	free(z);
	if (!neg)
		return (NULL);
	return (neg);
}

static char	*ft_edge(int n)
{
	char	*str;

	if (n == INT_MIN)
	{
		str = (char *)malloc((12) * sizeof(char));
		if (!str)
			return (NULL);
		ft_strcpy(str, "-2147483648");
		return (str);
	}
	else
		str = (char *)malloc((2) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;

	if (n == 0 || n == -2147483648)
		return (ft_edge(n));
	else if (n > 0)
	{
		str = ft_to_ascii(n);
		return (str);
	}
	else if (n < 0)
	{
		str = ft_neg_ascii(n);
		return (str);
	}
	else
		return (NULL);
}
