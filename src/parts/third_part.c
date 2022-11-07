/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 00:25:18 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/07 16:48:40 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"
#include "bmlib.h"

int	parse_third_part(char *file, t_pipex *pipex)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (ft_pipex_error(NULL, "bash:",
				" error creating first fork()", 0));
	if (!pid)
	{
		if (!ft_check_file(file, W_OK))
			exit (0);
		if (!ft_check_cmd(pipex->cmds->next, pipex->path))
			exit (0);
		exit (1);
	}
	else
	{
		waitpid(pid, &status, 0);
		pipex->util += WEXITSTATUS(status);
	}
	return (1);
}
