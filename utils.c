/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:55:21 by fmaurer           #+#    #+#             */
/*   Updated: 2024/11/04 20:23:36 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_ppx	*init_ppx()
{
	t_ppx	*ppx;
	
	ppx = malloc(sizeof(t_ppx));
	ppx->cmd1 = NULL;
	ppx->cmd2 = NULL;
	ppx->file1 = NULL;
	ppx->file2 = NULL;
	return (ppx);
}

void	free_ppx(t_ppx **ppx)
{
	if ((*ppx)->cmd1)
		free_split(&(*ppx)->cmd1);
	if ((*ppx)->cmd2)
		free_split(&(*ppx)->cmd2);
	if ((*ppx)->file1)
		free((*ppx)->file1);
	if ((*ppx)->file2)
		free((*ppx)->file2);
	free(*ppx);
}

/* Exit with error custom error msg, or not. */
void	error_exit_free(char *msg, t_ppx **ppx)
{
	if (msg)
		perror(msg);
	else
		perror("Error");
	free_ppx(ppx);
	exit(EXIT_FAILURE);
}

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
	if (ac != 5)
	{
		ft_printf("usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(0);
	}
	if ((access(av[1], R_OK) + access(av[4], R_OK)) != 0) 
		error_exit_free("some file not accessible", &ppx);
	ppx->file1 = av[1];
	ppx->file2 = av[4];
	ppx->cmd1 = get_exec_path(av[2], envp);
	if (!ppx->cmd1)
		error_exit_free("cmd1 not executable", &ppx);
	ppx->cmd2 = get_exec_path(av[3], envp);
	if (!ppx->cmd2)
		error_exit_free("cmd2 not executable", &ppx);
}

/* Perform NULL check on pointer. error_exit with msg if NULL. */ void	nullcheck(void *p, char *msg)
{
	if (!p)
		error_exit(msg);
}

