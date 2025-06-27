/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:00:48 by peatjohnsto       #+#    #+#             */
/*   Updated: 2024/10/19 11:36:37 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	process_c(va_list args, char spec)
{
	char	c;

	if (spec == 'c')
		c = va_arg(args, int);
	write(1, &c, 1);
	return (1);
}
