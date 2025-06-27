/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:52:14 by ekosnick          #+#    #+#             */
/*   Updated: 2024/10/02 10:13:55 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// just want to return a pointer to the duplicate copy of the string
// 'start' keeps track of the newly allocated mem
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	char	*start;

	new = (char *)malloc(ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	start = new;
	while (*s)
		*new++ = *s++;
	*new = '\0';
	return (start);
}
