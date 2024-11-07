/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 00:08:26 by fmaurer           #+#    #+#             */
/*   Updated: 2024/11/06 22:20:41 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "fcntl.h"

//  ./pipex file1 cmd1 cmd2 file2
int main(int ac, char **av, char **envp)
{
	t_ppx	*ppx;
	pid_t	cpid1;
	pid_t	cpid2;
	int		status;
	int		fd;
	int		fd2;
	int		pipefd[2];

	// TODO rewrite to parse_cmdline() which integrates init_ppx()
	ppx = init_ppx();
	check_cmdline(ac, av, envp, ppx);
	ft_printf("cmd1 executable using path: %s\n", ppx->cmd1[0]);
	ft_printf("cmd2 executable using path: %s\n", ppx->cmd2[0]);
	ft_printf("found file1: %s\n", ppx->file1);
	ft_printf("found file2: %s\n", ppx->file2);

	if (pipe(pipefd) == -1)
		error_exit_free("Pipe creation failed", &ppx);

	cpid1 = fork();
	if (cpid1 == -1)
		error_exit_free("First fork failed", &ppx);
	else if (cpid1 == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		fd = open(ppx->file1, O_RDONLY);
		if (fd == -1)
			error_exit_free("Opening file1 failed", &ppx);
		dup2(fd, 0);
		close(fd);
		execve(ppx->cmd1[0], ppx->cmd1, envp);
		close(pipefd[1]);
	}
	else
	{
		// waitpid(cpid1, &status, 0);
		ft_printf("cpid1: %d\n", cpid1);
		ft_printf("cpid1 exited with status: %d\n", status);
		ft_printf("forking cmd2\n");
		cpid2 = fork();
		if (cpid2 == -1)
			error_exit_free("Second fork failed", &ppx);
		if(cpid2 == 0)
		{
			ft_printf("here\n");
			dup2(pipefd[0], 0);
			close(pipefd[1]);
			fd2 = open(ppx->file2, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
			if (fd2 == -1)
				error_exit_free("Opening file2 failed", &ppx);
			dup2(fd2, 1);
			close(fd2);
			execve(ppx->cmd2[0], ppx->cmd2, envp);
		}
	}
	ft_printf("freeing & returning\n");
	free_ppx(&ppx);
	return (0);
}
