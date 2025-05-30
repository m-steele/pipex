/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:58:42 by peatjohnsto       #+#    #+#             */
/*   Updated: 2024/10/19 11:26:28 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	process_s(va_list args)
{
	int		n;
	char	*s;

	n = 0;
	s = va_arg(args, char *);
	if (!s)
		s = "(null)";
	while (*s)
	{
		write(1, s, 1);
		s++;
		n++;
	}
	return (n);
}
