/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:39:24 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/09 17:20:09 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

/* `ulimit -n` on my system. Number of open files per process. */
# define ULIMIT_N 1024

/* For ssize_t and NULL*/
# include <stddef.h>

/* For write & read */
# include <unistd.h>

/* For malloc & free */
# include <stdlib.h>

/* libft. */
# include "../libft.h"

#endif
