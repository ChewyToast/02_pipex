/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:36:47 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/11 16:02:03 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"
#include <stdlib.h>
#include <sys/wait.h>
#include "bmlib.h"
static void	prepare_fd(t_pipex *pip);

void	third_part(t_pipex *pip)
{
	pid_t	pid;
	int		status;

	close(pip->utils->pipes[1]);
	if (dup2(pip->utils->pipes[0], 0) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
	pid = fork();
	if (pid < 0)
	{
		pip->utils->exit_status = 1;
		exit (error_msg(NULL, "bash", ECF, 1));
	}
	else if (!pid)
	{
		get_path(pip, "PATH=");//	-----
		check_file(*(pip->inputs->argv + (pip->inputs->argc - 1)), W_OK, pip);//	-----
		pip->inputs->argv += pip->inputs->argc - 4;
		pip->cmds = malloc(sizeof(t_cmds));
		if (!pip->cmds)
			exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
		check_cmd(pip, pip->cmds);//	-----
		ft_printf("\n\nTHIRD PART EXECVES\n");
		prepare_fd(pip);
		if (pip->utils->error)
			exit (clean_exit(pip, 0));
		execve(*(pip->cmds->cmd), pip->cmds->cmd, pip->inputs->env);//	-----
		exit (clean_exit(pip, 1));// ------ FALTA EL MSG THE EXECV
	}
	waitpid(pid, &status, 0);
	pip->utils->exit_status = WEXITSTATUS(status);
}

static void	prepare_fd(t_pipex *pip)
{
	pip->inputs->outfd = open(*(pip->inputs->argv + 3), O_CREAT | O_RDWR, 0644);
	if (pip->inputs->inpfd < 0)
		exit (error_msg(BSH, *(pip->inputs->argv + 3), CNO, clean_exit(pip, 1)));

	if (dup2(pip->inputs->outfd, 1) < 0)
	 	exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
}