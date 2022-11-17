/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomoll <brunomoll@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:55:19 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/17 11:09:59 by brunomoll        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bmlib.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pip;
	pid_t	pid;
	int		status;

	if (argc != 5)
		exit (error_msg(NULL, "bash", INA, 1));
	if (!init_pipex(argc, argv, env, &pip))
		exit(error_msg(NULL, "bash", MKO, 1));
	if (pipe(pip.utils->pipes) < 0)
		exit (error_msg(NULL, "bash", ECP, clean_exit(&pip, 1)));
	pid = fork();
	close(0);
	if (pid < 0)
		exit (error_msg(NULL, "bash", ECF, clean_exit(&pip, 1)));
	else if (!pid)
		first_part(&pip);
	waitpid(pid, &status, 0);
	if (dup2(pip.utils->pipes[0], 0) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(&pip, 1)));
	close(pip.utils->pipes[1]);
	second_part(&pip);
	return (0);
}

void	first_part(t_pipex *pip)
{
	get_path(pip, "PATH=");
	check_file(*(pip->inputs->argv + 1), R_OK, pip);
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
	close(pip->utils->pipes[0]);
	execve(pip->cmds->path_comand, pip->cmds->cmd, pip->inputs->env);
	close(1);
	clean_exit(pip, 1);
	perror(NULL);
	exit (1);
}

void	second_part(t_pipex *pip)
{
	get_path(pip, "PATH=");
	check_file(*(pip->inputs->argv + (pip->inputs->argc - 1)), W_OK, pip);
	pip->inputs->argv += pip->inputs->argc - 4;
	pip->inputs->outfd = open(*(pip->inputs->argv + 3), O_CREAT | O_RDWR, 0666);
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
		execve(pip->cmds->path_comand, pip->cmds->cmd, pip->inputs->env);
	exit (clean_exit(pip, 1));
}
