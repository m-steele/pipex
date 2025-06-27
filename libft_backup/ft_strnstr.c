/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peatjohnston <peatjohnston@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:34:48 by ekosnick          #+#    #+#             */
/*   Updated: 2024/10/03 17:18:06 by peatjohnsto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// looking for little string in big string; need two indexes
// NULL if no little; cpy big starting where it starts from little
// within a given range of bytes starting from big def by user
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (big[i + j] == little[j] && i + j < len)
			if (!little[++j])
				return ((char *)big + i);
		i++;
		j = 0;
	}
	return (NULL);
}
