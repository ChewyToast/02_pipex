/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:09:03 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/30 23:02:50 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "bmlib.h"

int	init_pipex(int argc, char **argv, char **env, t_pipex *pip)
{
	pip->cmds = NULL;
	pip->inputs = malloc(sizeof(t_input));
	if (!pip->inputs)
		return (0);
	pip->utils = malloc(sizeof(t_utils));
	if (!pip->utils)
	{
		free(pip->inputs);
		return (0);
	}
	pip->inputs->here_doc = 0;
	pip->inputs->inpfd = 0;
	pip->inputs->outfd = 0;
	pip->inputs->argc = argc;
	pip->inputs->argv = argv;
	pip->inputs->env = env;
	pip->utils->error = 0;
	pip->utils->path = NULL;
	pip->utils->exit_status = 0;
	return (1);
}

void	startup_fds(t_pipex *pip)
{
	int	fd;

	if (!ft_strncmp(pip->inputs->argv[1], "here_doc", 8))
	{
		pip->inputs->here_doc = 1;
		fd = here_doc(pip);
		if (dup2(fd, 0) < 0)
			exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
		pip->inputs->argv++;
	}
	else
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
}

int	here_doc(t_pipex *pip)
{
	pid_t	pid;
	int		pipes[2];
	int		status;

	if (pipe(pipes) < 0)
		exit (error_msg(NULL, "bash", ECP, clean_exit(pip, 1)));
	pid = fork();
	if (pid < 0)
		exit (error_msg(NULL, "bash", ECF, clean_exit(pip, 1)));
	else if (!pid)
		extra_loop(pip, pipes, 1);
	if (close(pipes[1]))
		exit (clean_exit(pip, error_msg(PPX, "open", CNC, 1)));
	waitpid(pid, &status, 0);
	if (status)
		exit (clean_exit(pip, 1));
	return (pipes[0]);
}

int	clean_exit(t_pipex *pip, int ret)
{
	size_t	iter;

	if (pip->inputs->inpfd)
		close(pip->inputs->inpfd);
	if (pip->inputs->outfd)
		close(pip->inputs->outfd);
	if (pip->utils->path)
	{
		iter = 0;
		while (pip->utils->path[iter])
			free(pip->utils->path[iter++]);
		free(pip->utils->path);
	}
	if (pip->cmds)
	{
		iter = 0;
		while (pip->cmds->cmd[iter])
			free(pip->cmds->cmd[iter++]);
		free(pip->cmds->pt_cmd);
		free(pip->cmds->cmd);
		free(pip->cmds);
	}
	free(pip->utils);
	free(pip->inputs);
	return (ret);
}

int	error_msg(char *first, char *second, char *thrd, int ret)
{
	size_t	len;

	if (!first)
		len = 0;
	else
		len = ft_strlen(first);
	write(2, first, len);
	write(2, second, ft_strlen(second));
	write(2, thrd, ft_strlen(thrd));
	write(2, "\n", 1);
	return (ret);
}
