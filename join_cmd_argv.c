/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:26:59 by fmaurer           #+#    #+#             */
/*   Updated: 2024/11/04 08:32:49 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

// It is not meant to be like this!!!
char **join_cmd_argv(t_ppx *ppx)
{
	int	argcnt;
	int		i;
	char	**argv;
	
	argcnt = 0;
	while (ppx->cmd1[argcnt])
		argcnt++;
	argv = malloc(sizeof(char *) * (argcnt + 3));
	if (!argv)
		error_exit_free("malloc in join_cmd_argv failed", &ppx);
	i = 0;
	while(ppx->cmd1[i])
	{
		argv[i] = ppx->cmd1[i];
		i++;
	}
	argv[i] = ppx->file1;
	argv[++i] = NULL;
	return (argv);
}

