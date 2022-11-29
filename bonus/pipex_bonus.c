/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 23:59:36 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/29 03:48:34 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "bmlib.h"

static void	first_part(t_pipex *pip, int *pipes);
static void	second_part(t_pipex *pip);
static void	prepare_next(t_pipex *pip, int *pipes);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pip;
	pid_t	pid;
	int		pipes[2];

	if (argc < 5 || (argc < 6 && !ft_strncmp(argv[1], "here_doc", 8)))
		exit (error_msg(NULL, "bash", INA, 1));
	if (!init_pipex(argc, argv, env, &pip))
		exit(error_msg(NULL, "bash", MKO, 1));
	startup_fds(&pip);
	argc -= 4 + pip.inputs->here_doc;
	while ((argc)--)
	{
		if (pipe(pipes) < 0)
			exit (error_msg(NULL, "bash", ECP, clean_exit(&pip, 1)));
		pid = fork();
		if (pid < 0)
			exit (error_msg(NULL, "bash", ECF, clean_exit(&pip, 1)));
		else if (pid == 0)
			first_part(&pip, pipes);
		prepare_next(&pip, pipes);
	}
	second_part(&pip);
}

static void	first_part(t_pipex *pip, int *pipes)
{
	if (pip->utils->error)
		exit (clean_exit(pip, pip->utils->error));
	get_path(pip, "PATH=");
	pip->cmds = malloc(sizeof(t_cmds));
	if (!pip->cmds)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	check_cmd(pip, pip->cmds);
	if (dup2(pipes[1], 1) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
	close(pipes[0]);
	close(pipes[1]);
	execve(pip->cmds->path_comand, pip->cmds->cmd, pip->inputs->env);
	perror(NULL);
	exit (clean_exit(pip, 1));
}

static void	second_part(t_pipex *pip)
{
	get_path(pip, "PATH=");
	if (!check_file(pip->inputs->argv[3], W_OK, pip))
		exit (clean_exit(pip, pip->utils->error));
	if (!pip->inputs->here_doc)
		pip->inputs->outfd = open(pip->inputs->argv[3],
				O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else
		pip->inputs->outfd = open(pip->inputs->argv[3],
				O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (pip->inputs->inpfd < 0)
		exit (clean_exit(pip, error_msg(BSH, pip->inputs->argv[3], CNO, 1)));
	pip->cmds = malloc(sizeof(t_cmds));
	if (!pip->cmds)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	check_cmd(pip, pip->cmds);
	if (dup2(pip->inputs->outfd, 1) < 0)
		exit (error_msg(BSH, "2", BFD, clean_exit(pip, 1)));
	execve(pip->cmds->path_comand, pip->cmds->cmd, pip->inputs->env);
	exit (clean_exit(pip, 1));
}

static void	prepare_next(t_pipex *pip, int *pipes)
{
	pip->inputs->argv++;
	pip->utils->error = 0;
	if (dup2(pipes[0], 0) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
	close(pipes[0]);
	close(pipes[1]);
}
