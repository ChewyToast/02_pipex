/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:13:20 by bruno             #+#    #+#             */
/*   Updated: 2022/11/08 15:49:11 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_struct.h"

void	init_pipex(int argc, char **argv, char **env, t_pipex *pip)
{
	pip->input->inpfd = 0;
	pip->input->outfd = 0;
	pip->input->argc = argc;
	pip->input->argv = argv;
	pip->input->env = env;
	pip->cmds = NULL;
	pip->utils->util = 0;
	pip->util->pipes = NULL;
	pip->util->path = NULL;
	pip->util->exit_status = 0;
}

void	clean_exit(t_pipex *pip)
{
	size_t	iter;

	iter = 0;
	if (pipex->inpfd)
		close(pipex->inpfd);
	if (pipex->outfd)
		close(pipex->outfd);
	if (pipex->utils->path)
	{
		while (pipex->utils->path[iter])
			free(pipex->utils->path[iter++]);
		free(pipex->utils->path);
	}
}

void	clean_exit_util(t_pipex *pip)
{
	size_t	iter;
	t_cmds	*tmp;

	while (pipex->cmds)
	{
		iter = 0;
		free(pipex->cmds->cmd);
		while (pipex->cmds->flags[iter])
			free(pipex->cmds->flags[iter++]);
		free(--(pipex->cmds->flags));
		tmp = pipex->cmds->next;
		free(pipex->cmds);
		pipex->cmds = tmp;
	}
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