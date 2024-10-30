/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 00:08:26 by fmaurer           #+#    #+#             */
/*   Updated: 2024/10/30 06:50:07 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "libft/libft.h"

// execute permission: X_OK
// TODO protect every malloc ?!?!?
char	*get_exec_path(char *cmd, char **env)
{
	int		i;
	char	**path_split;
	char	*exec_path;
	char	**prog;

	path_split = get_path_from_env(env);
	prog = ft_split(cmd, ' ');
	nullcheck(prog, "ft_split malloc failed in get_exec_path");
	if(access(prog[0], X_OK) == 0)
		return(prog[0]);
	i = -1;
	while (path_split[++i])
	{
		exec_path = join_exec_path_strings(path_split[i], prog[0]);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		free(exec_path);
	}
	free_split(&path_split);
	free_split(&prog);
	return (NULL);
}

//  ./pipex file1 cmd1 cmd2 file2
int main(int ac, char **av, char **envp)
{
	char	*epath;
	t_ppx	ppx;
	
	// rewrite so that alls commands and files get stored inside t_ppx struct
	// making it easier or just possible to cleanly free everything in case of
	// error.
	check_cmdline(ac, av, envp, &ppx);
	epath = get_exec_path(av[2], envp);
	ft_printf("cmd1 executable using path: %s\n", epath);
	free(epath);
	epath = get_exec_path(av[3], envp);
	ft_printf("cmd2 executable using path: %s\n", epath);
	return (0);
}
