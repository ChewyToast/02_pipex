/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:02:10 by bruno             #+#    #+#             */
/*   Updated: 2022/11/10 21:51:30 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"
#include <stdlib.h>
#include <sys/wait.h>
#include "bmlib.h"
static void	prepare_fd(t_pipex *pip);

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
		get_path(pip, "PATH=");//	-----
		check_file(*(pip->inputs->argv + 1), R_OK, pip);//	-----
		pip->cmds = malloc(sizeof(t_cmds));
		if (!pip->cmds)
			exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
		check_cmd(pip, pip->cmds);//	-----
		ft_printf("\nFIRST PART EXECVES\n");
		prepare_fd(pip);
		execve(*(pip->cmds->cmd), pip->cmds->cmd, pip->inputs->env);//	-----
		exit (clean_exit(pip, 1));// ------ FALTA EL MSG THE EXECV
	}
	waitpid(pid, &status, 0);
}

static void	prepare_fd(t_pipex *pip)
{
	ft_printf("\nIn child the pipes[0] = %d, and the pipes[1] = %d\n", pip->utils->pipes[0], pip->utils->pipes[1]);
	ft_printf("\n1 - Closing pipes[0]: %d\n2 - Dup2(inpfd (%d), 0)\n3 - Dup2(pipes[1] (%d), 1)", pip->utils->pipes[0], pip->inputs->inpfd, pip->utils->pipes[1]);
	close(pip->utils->pipes[0]);
	pip->inputs->inpfd = open(*(pip->inputs->argv + 1), O_RDONLY);
	if (pip->inputs->inpfd < 0)
		exit (error_msg(BSH, *(pip->inputs->argv + 1), CNO, clean_exit(pip, 1)));
	if (dup2(pip->inputs->inpfd, 0) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
	if (dup2(pip->utils->pipes[1], 1) < 0)
	 	exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
}