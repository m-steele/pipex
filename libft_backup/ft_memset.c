/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peatjohnston <peatjohnston@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:27:40 by ekosnick          #+#    #+#             */
/*   Updated: 2024/10/01 15:21:42 by peatjohnsto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Allows user to replace a number of bytes with same char to each
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = (unsigned char)c;
	return (s);
}
