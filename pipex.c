/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 00:08:26 by fmaurer           #+#    #+#             */
/*   Updated: 2024/11/07 10:54:43 by fmaurer          ###   ########.fr       */
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
	int		fd;
	int		fd2;
	int		pipefd[2];

	// TODO rewrite to parse_cmdline() which integrates init_ppx()
	ppx = init_ppx();
	check_cmdline(ac, av, envp, ppx);

	if (pipe(pipefd) == -1)
		error_exit_free("Pipe creation failed", &ppx);

	cpid1 = fork();
	/* if i did write
	 *
	 * cpid2 = fork();
	 *
	 * right here, after the 1st fork, the whole child1-code would be executed
	 * twice. One time in child1 as a parent of child2, because cpid1 == 0
	 * there. But cpid1 == 0  is also true inside child2 because the variable
	 * gets copied there. 
	 */
	if (cpid1 < 0)
		error_exit_free("fork failed", &ppx);
	if (cpid1 == 0)
	{
		write(1, ".", 1);
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		fd = open(ppx->file1, O_RDONLY);
		if (fd == -1)
			error_exit_free("Opening file1 failed", &ppx);
		dup2(fd, 0);
		close(fd);
		execve(ppx->cmd1[0], ppx->cmd1, envp);
	}
	/* 2nd fork has to be here because we dont want the child1 code to be
	 * execute again in child2 */
	cpid2 = fork();
	ft_printf("cpid2 = %d\n", cpid2);
	if (cpid2 < 0)
		error_exit_free("fork failed", &ppx);
	if (cpid2 == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
		fd2 = open(ppx->file2, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
		if (fd2 == -1)
			error_exit_free("Opening file2 failed", &ppx);
		dup2(fd2, 1);
		close(fd2);
		execve(ppx->cmd2[0], ppx->cmd2, envp);
	}
	wait(NULL);
	close(pipefd[0]);
	close(pipefd[1]);
	ft_printf("freeing & returning\n");
	free_ppx(&ppx);
	return (0);
}
