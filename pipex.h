/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekosnick <ekosnick@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:11:15 by ekosnick          #+#    #+#             */
/*   Updated: 2025/06/06 15:19:57 by ekosnick         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h> /* access() */
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h> /* waitpid() */
# include <errno.h>    /* errno, strerror */
# include <stdlib.h>   /* getenv, strdup, free */
# include <string.h>   /* strtok, strcmp, snprintf, strlen */
# include <dirent.h>   /* opendir, readdir, closedir, struct dirent */
# include <sys/stat.h> /* stat, S_ISREG */
# include <limits.h>   /* PATH_MAX (recommended for full_path buffer) */
# include "libft/libft.h"

#endif