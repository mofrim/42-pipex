/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:55:21 by fmaurer           #+#    #+#             */
/*   Updated: 2024/10/30 06:49:07 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Exit with error custom error msg, or not. */
void	error_exit(char *msg)
{
	if (msg)
		perror(msg);
	else
		perror("Error");
	exit(EXIT_FAILURE);
}

void	free_split(char ***split)
{ char	**tmp;

	tmp = *split;
	while (**split)
	{
		free(**split);
		(*split)++;
	}
	free(tmp);
}

int	ft_initial_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

void	check_cmdline(int ac, char **av, char **envp, t_ppx *ppx)
{
	char	*epath;

	if (ac != 5)
	{
		ft_printf("usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(0);
	}
	if ((access(av[1], R_OK) + access(av[4], R_OK)) != 0) 
		error_exit("some file not accessible");
	epath = get_exec_path(av[2], envp);
	if (!epath)
		error_exit("cmd1 not executable");
	free(epath);
	epath = get_exec_path(av[3], envp);
	if (!epath)
		error_exit("cmd2 not executable");
	free(epath);
}

char **get_path_from_env(char **env)
{
	int		i;
	char	**path_split;

	if(!env || !env[0])
		error_exit("empty env");
	i = 0;
	while (!ft_initial_strcmp(env[i], "PATH") && env[i])
		i++;
	if(!env[i])
		error_exit("no PATH found in env");
	path_split = ft_split((env[i] + 5), ':');
	if (!path_split)
		error_exit("malloc in get_path_from_env ft_split failed");
	return (path_split);
}

/* Perform NULL check on pointer. error_exit with msg if NULL. */
void	nullcheck(void *p, char *msg)
{
	if (!p)
		error_exit(msg);
}

char	*join_exec_path_strings(char *path, char *exec)
{
	char	*path_slash;
	char	*exec_path;

	path_slash = ft_strjoin(path, "/");
	nullcheck(path_slash, "path_slash malloc failed");
	exec_path = ft_strjoin(path_slash, exec);
	nullcheck(exec_path,"exec_path malloc failed");
	free(path_slash);
	return (exec_path);
}
