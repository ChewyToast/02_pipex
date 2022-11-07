/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 23:12:24 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/07 17:06:44 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"
#include "bmlib.h"

int	parse_second_part(t_pipex *pipex)
{
	int		i;
	pid_t	pid;
	int		status;
	t_cmds	*tmp_cmds;

	i = 0;
	tmp_cmds = pipex->cmds;
	while (i < pipex->argc - 5)
	{
		tmp_cmds = tmp_cmds->next;
		pid = fork();
		if (pid < 0)
			return (ft_pipex_error(NULL, "bash:",
					" error creating first fork()", 0));
		if (!pid)
		{
			if (!ft_check_cmd(tmp_cmds, pipex->path))
				exit (0);
			exit (1);
		}
		waitpid(pid, &status, 0);
		pipex->util += WEXITSTATUS(status);
		i++;
	}
	return (pipex->util == i);
}
