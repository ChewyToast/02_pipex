/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:02:10 by bruno             #+#    #+#             */
/*   Updated: 2022/11/10 15:02:24 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"
#include <stdlib.h>
#include <sys/wait.h>
#include "bmlib.h"

void	first_part(t_pipex *pip)
{
	pid_t	pid;
	int		status;

	pip->utils->pipes = malloc(sizeof(int) * 2);
	if (!pip->utils->pipes)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	if (pipe(pip->utils->pipes) < 0)
		exit (error_msg(NULL, "bash", ECP, clean_exit(pip, 1)));
	pid = fork();
	if (pid < 0)
	{
		pip->utils->exit_status = 1;
		exit (error_msg(NULL, "bash", ECF, 1));
	}
	else if (!pid)
	{
		close(pip->utils->pipes[0]);
		get_path(pip, "PATH=");
		check_file(*(pip->inputs->argv + 1), R_OK, pip);
		pip->cmds = malloc(sizeof(t_cmds));
		if (!pip->cmds)
			exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
		check_cmd(pip, pip->cmds);
		pip->inputs->inpfd = open(*(pip->inputs->argv + 1), O_RDONLY);
		if (pip->inputs->inpfd < 0)
			exit (error_msg(BSH, *(pip->inputs->argv + 1), CNO, clean_exit(pip, 1)));
		if (dup2(0, pip->inputs->inpfd) < 0)
			exit (error_msg(BSH, " dup2", BFD, clean_exit(pip, 1)));
		// if (dup2(pip->utils->pipes[1], 1) < 0)
		// 	exit (error_msg(BSH, " dup2", BFD, clean_exit(pip, 1)));
		ft_printf("\nBEFORE EXECV: %s\n", *(pip->cmds->cmd));
		execve(*(pip->cmds->cmd), pip->cmds->cmd, pip->inputs->env);
		exit (clean_exit(pip, 1));// ------ FALTA EL MSG THE EXECV
	}
	ft_printf("\nwait\n");
	waitpid(pid, &status, 0);
	ft_printf("\nend\n");
	pip->utils->exit_status = WEXITSTATUS(status);
}
