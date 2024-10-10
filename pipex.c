/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 00:08:26 by fmaurer           #+#    #+#             */
/*   Updated: 2024/10/10 11:12:16 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

// execute permission: X_OK

char	*get_path(char *exec_file, char **env)
{
	int		i;
	char	**path_split;
	char	*exec_path;
	char	*path_slash;

	i = -1;
	while (!ft_initial_strcmp(env[++i], "PATH"))
		;
	path_split = ft_split((env[i] + 5), ':');
	i = -1;
	while (path_split[++i])
	{
		path_slash = ft_strjoin(path_split[i], "/");
		exec_path = ft_strjoin(path_slash, exec_file);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		free(exec_path);
		free(path_slash);
	}
	free_split(&path_split);
	return (NULL);
}

//  ./pipex file1 cmd1 cmd2 file2
int main(int ac, char **av, char **envp)
{
	char	*epath;
	
	check_cmdline(ac, av, envp);
	epath = get_path(av[2], envp);
	ft_printf("cmd1 executable using path: %s\n", epath);
	return (0);
}
