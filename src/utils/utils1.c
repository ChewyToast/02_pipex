/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:13:20 by bruno             #+#    #+#             */
/*   Updated: 2022/11/10 21:15:59 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "pipex_struct.h"

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
	pip->utils->pipes = NULL;
	pip->utils->path = NULL;
	pip->utils->exit_status = 0;
	return (1);
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
		free(pip->cmds);
	}
	if (pip->inputs)
		free(pip->inputs);
	if (pip->utils)
	{
		if (pip->utils->pipes)
			free(pip->utils->pipes);
		free(pip->utils);
	}
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