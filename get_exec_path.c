/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:05:20 by fmaurer           #+#    #+#             */
/*   Updated: 2024/11/03 20:07:38 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// execute permission: X_OK
// TODO protect every malloc ?!?!?
// TODO free everything correctly in case of failure
char	**get_exec_path(char *cmd, char **env)
{
	int		i;
	char	**path_split;
	char	*exec_path;
	char	**prog;
	char	*tmp;

	path_split = get_path_from_env(env);
	prog = ft_split(cmd, ' ');
	nullcheck(prog, "ft_split malloc failed in get_exec_path");
	if(access(prog[0], X_OK) == 0)
	{
		free_split(&path_split);
		return(prog);
	}
	i = -1;
	while (path_split[++i])
	{
		exec_path = join_exec_path_strings(path_split[i], prog[0]);
		if (access(exec_path, X_OK) == 0)
		{
			tmp = prog[0];
			prog[0] = ft_strcpy(exec_path);
			free(tmp);
			free(exec_path);
			free_split(&path_split);
			return (prog);
		}
		free(exec_path);
	}
	free_split(&path_split);
	free_split(&prog);
	return (NULL);
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
