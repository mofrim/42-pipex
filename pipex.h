/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:55:43 by fmaurer           #+#    #+#             */
/*   Updated: 2024/10/30 06:50:36 by fmaurer          ###   ########.fr       */
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

typedef struct	s_ppx {
	char	**cmd1;
	char	**cmd2;
	char	*file1;
	char	*file2;
} t_ppx;

void	error_exit(char *msg);
int		ft_initial_strcmp(char *s1, char *s2);
void	free_split(char ***split);
char	*get_exec_path(char *exec_file, char **env);
char 	**get_path_from_env(char **env);
void	check_cmdline(int ac, char **av, char **envp, t_ppx *ppx);
void	nullcheck(void *p, char *msg);
char	*join_exec_path_strings(char *path, char *exec);

#endif
