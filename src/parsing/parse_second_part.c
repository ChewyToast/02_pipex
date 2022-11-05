/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_second_part.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 23:12:24 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/05 01:03:27 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"
#include "bmlib.h"

static t_cmds	*get_cmd(t_cmds *start, int i);

int	parse_second_part(t_pipex *pipex)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	while (i < pipex->argc - 5)
	{
		pid = fork();
		if (pid < 0)
			return (ft_pipex_error(NULL, "bash:",
					" error creating first fork()", 0));
		if (!pid)
		{
			if (!ft_check_cmd(get_cmd(pipex->cmds->next, i), pipex->path))
				exit (0);
			exit (1);
		}
		else
		{
			waitpid(pid, &status, 0);
			pipex->util += WEXITSTATUS(status);
		}
		i++;
	}
	return (pipex->util == i);
}

static t_cmds	*get_cmd(t_cmds *start, int i)
{
	while (i && start)
	{
		start = start->next;
		i++;
	}
	return (start);
}
