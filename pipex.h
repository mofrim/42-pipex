/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:55:43 by fmaurer           #+#    #+#             */
/*   Updated: 2024/10/10 11:11:30 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "libft/libft.h"

void	error_exit(char *msg);
int		ft_initial_strcmp(char *s1, char *s2);
void	free_split(char ***split);
char	*get_path(char *exec_file, char **env);
void	check_cmdline(int ac, char **av, char **envp);

#endif
