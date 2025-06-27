/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:23:06 by ekosnick          #+#    #+#             */
/*   Updated: 2024/10/02 13:18:11 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// copy n bytes from src to dest with potentially overlapping memory
// void allows multiple data types to be tested at there mem-address
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const unsigned char	*tmp_src;
	unsigned char		*tmp_dest;
	size_t				i;

	i = 0;
	if (!src && !dst)
		return (NULL);
	tmp_dest = (unsigned char *) dst;
	tmp_src = (const unsigned char *) src;
	if (tmp_dest > tmp_src)
	{
		while (n--)
			tmp_dest[n] = tmp_src[n];
	}
	else
	{
		while (i < n)
		{
			tmp_dest[i] = tmp_src[i];
			i++;
		}
	}
	return (dst);
}
