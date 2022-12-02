/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:55:19 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/12/02 22:49:09 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bmlib.h"

static void	startup_fds(t_pipex *pip);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pip;
	pid_t	pid;

	if (argc != 5)
		exit (error_msg(NULL, "bash", INA, 1));
	if (!init_pipex(argc, argv, env, &pip))
		exit(error_msg(NULL, "bash", MKO, 1));
	startup_fds(&pip);
	if (pipe(pip.utils->pipes) < 0)
		exit (error_msg(NULL, "bash", ECP, clean_exit(&pip, 1)));
	pid = fork();
	if (pid < 0)
		exit (error_msg(NULL, "bash", ECF, clean_exit(&pip, 1)));
	else if (!pid)
		first_part(&pip);
	pip.utils->error = 0;
	if (dup2(pip.utils->pipes[0], 0) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(&pip, 1)));
	close(pip.utils->pipes[1]);
	close(pip.utils->pipes[0]);
	second_part(&pip);
	return (0);
}

void	first_part(t_pipex *pip)
{
	if (pip->utils->error)
		exit (clean_exit(pip, pip->utils->error));
	get_path(pip, "PATH=");
	pip->cmds = malloc(sizeof(t_cmds));
	if (!pip->cmds)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	check_cmd(pip, pip->cmds);
	pip->inputs->inpfd = open(*(pip->inputs->argv + 1), O_RDONLY);
	if (pip->inputs->inpfd < 0)
	{
		error_msg(BSH, *(pip->inputs->argv + 1), CNO, 1);
		exit (clean_exit(pip, 1));
	}
	if (dup2(pip->inputs->inpfd, 0) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
	if (dup2(pip->utils->pipes[1], 1) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
	clean_execv(pip);
}

void	second_part(t_pipex *pip)
{
	get_path(pip, "PATH=");
	if (!check_file(pip->inputs->argv[4], W_OK, pip))
		exit (clean_exit(pip, pip->utils->error));
	pip->inputs->argv += 1;
	pip->inputs->outfd = open(*(pip->inputs->argv + 3),
			O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (pip->inputs->inpfd < 0)
	{
		error_msg(BSH, *(pip->inputs->argv + 3), CNO, 1);
		exit (clean_exit(pip, 1));
	}
	pip->cmds = malloc(sizeof(t_cmds));
	if (!pip->cmds)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	check_cmd(pip, pip->cmds);
	if (dup2(pip->inputs->outfd, 1) < 0)
		exit (error_msg(BSH, "2", BFD, clean_exit(pip, 1)));
	if (!pip->utils->error)
		execve(pip->cmds->pt_cmd, pip->cmds->cmd, pip->inputs->env);
	exit (clean_exit(pip, 1));
}

static void	startup_fds(t_pipex *pip)
{
	if (!check_file(*(pip->inputs->argv + 1), R_OK, pip))
		return ;
	pip->inputs->inpfd = open(*(pip->inputs->argv + 1), O_RDONLY);
	if (pip->inputs->inpfd < 0)
		exit (clean_exit(pip, error_msg(BSH, *(pip->inputs->argv + 1),
					CNO, 1)));
	if (dup2(pip->inputs->inpfd, 0) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
}
