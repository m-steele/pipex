/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 09:56:37 by ekosnick          #+#    #+#             */
/*   Updated: 2025/06/29 16:10:02 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	openfd(char *fd, int in_out)
{
	if (in_out == 0)
		return (open(fd, O_RDONLY));
	if (in_out == 1)
		return (open(fd, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH, 0644));
	if (in_out == 2)
		return (open(fd, O_CREAT | O_WRONLY | O_APPEND, 0644));
	else
		return (-1);
}
