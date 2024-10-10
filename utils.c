/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:55:21 by fmaurer           #+#    #+#             */
/*   Updated: 2024/10/10 11:10:40 by fmaurer          ###   ########.fr       */
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
{
	char	**tmp;

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

void	check_cmdline(int ac, char **av, char **envp)
{
	char	*epath;

	if (ac != 5)
	{
		ft_printf("usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(0);
	}
	if ((access(av[1], R_OK) + access(av[4], R_OK)) != 0) 
		error_exit("some file not accessible\n");
	epath = get_path(av[2], envp);
	if (!epath)
		error_exit("cmd1 not executable\n");
	free(epath);
	epath = get_path(av[3], envp);
	if (!epath)
		error_exit("cmd2 not executable\n");
	free(epath);
}
