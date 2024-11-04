/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:55:43 by fmaurer           #+#    #+#             */
/*   Updated: 2024/11/04 20:06:18 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* waitpid */
#include <sys/wait.h>

/* open, O_* flags, */
#include <fcntl.h>

#include <stdio.h>

/* fork, execve, pipe  */
#include <unistd.h>

#include <stdlib.h>
#include <errno.h>
#include "libft/libft/libft.h"

typedef struct	s_ppx {
	char	**cmd1;
	char	**cmd2;
	char	*file1;
	char	*file2;
} t_ppx;

void	error_exit_free(char *msg, t_ppx **ppx);
void	error_exit(char *msg);
int		ft_initial_strcmp(char *s1, char *s2);
void	free_split(char ***split);
char	**get_exec_path(char *exec_file, char **env);
char 	**get_path_from_env(char **env);
void	check_cmdline(int ac, char **av, char **envp, t_ppx *ppx);
void	nullcheck(void *p, char *msg);
char	*join_exec_path_strings(char *path, char *exec);
t_ppx	*init_ppx();
void	free_ppx(t_ppx **ppx);

#endif
