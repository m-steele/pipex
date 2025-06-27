/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peatjohnston <peatjohnston@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:26:16 by ekosnick          #+#    #+#             */
/*   Updated: 2024/10/01 13:01:05 by peatjohnsto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// replaces specified number of bytes with zero '\0'
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
