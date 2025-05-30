/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peatjohnston <peatjohnston@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:46:11 by ekosnick          #+#    #+#             */
/*   Updated: 2024/11/02 11:26:13 by peatjohnsto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// sets all the allocated bytes to 0
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*pnt;
	size_t			i;

	i = 0;
	if (nmemb && (nmemb * size) / nmemb != size)
		return (NULL);
	pnt = (void *)malloc(nmemb * size);
	if (!pnt)
		return (NULL);
	while (i < nmemb * size)
		pnt[i++] = 0;
	return (pnt);
}
