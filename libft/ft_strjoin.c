/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:21:31 by ekosnick          #+#    #+#             */
/*   Updated: 2025/06/09 10:14:08 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NOte the below works in place of the while loops
// ft_strlcpy(join, s1, len); 
// ft_strlcat(join, s2, len);
// NOTE: you can guard against NULL pointers with:
// if (!s1 && !s2)
// 	return (st_strdup(""));
// if (!s1)
// 	return (ft_strdup(s1));
// if (!s2)
// 	return (ft_strdup(s2));
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		ii;
	int		j;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		join[j++] = s1[i++];
	ii = 0;
	while (s2[ii])
		join[j++] = s2[ii++];
	join[j] = '\0';
	return (join);
}
