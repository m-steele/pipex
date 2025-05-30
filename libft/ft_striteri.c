/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:24:39 by ekosnick          #+#    #+#             */
/*   Updated: 2024/10/02 10:24:42 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Modifies the string 's' so no copying or returning
// But requires a call back function of this form
// void	add_index_to_char(unsigned int i, char *c) {*c += i;}
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
