/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:13:20 by bruno             #+#    #+#             */
/*   Updated: 2022/11/30 22:32:43 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "pipex.h"

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

void	clean_execv(t_pipex *pip)
{
	size_t	iter;

	if (close(pip->inputs->inpfd))
		exit (clean_exit(pip, error_msg(PPX, "open", CNC, 1)));
	if (close(pip->utils->pipes[0]))
		exit (clean_exit(pip, error_msg(PPX, "open", CNC, 1)));
	if (close(pip->utils->pipes[1]))
		exit (clean_exit(pip, error_msg(PPX, "open", CNC, 1)));
	execve(pip->cmds->path_comand, pip->cmds->cmd, pip->inputs->env);
	if (pip->utils->path)
	{
		iter = 0;
		while (pip->utils->path[iter])
			free(pip->utils->path[iter++]);
		free(pip->utils->path);
	}
	clean_exit(pip, 1);
	perror(NULL);
	exit (1);
}

static void	extra_clean_exit(t_pipex *pip)
{
	size_t	iter;

	if (pip->cmds)
	{
		iter = 0;
		if (pip->cmds->cmd)
		{
			while (pip->cmds->cmd[iter])
				free(pip->cmds->cmd[iter++]);
			free(pip->cmds->cmd);
		}
		free(pip->cmds->path_comand);
		free(pip->cmds);
	}
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
	extra_clean_exit(pip);
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
