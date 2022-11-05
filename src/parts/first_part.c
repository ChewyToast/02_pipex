/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:19:02 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/05 03:40:27 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"
#include "bmlib.h"

static int	check_and_exec(char *file, t_pipex *pipex);

int	parse_first_part(char *file, t_pipex *pipex)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (ft_pipex_error(NULL, "bash:",
				" error creating first fork()", 0));
	if (!pid)
		check_and_exec(file, pipex);
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (1);
}

static int	check_and_exec(char *file, t_pipex *pipex)
{
	if (!ft_check_file(file, R_OK))
		exit (0);
	if (!ft_check_cmd(pipex->cmds, pipex->path))
		exit (0);
	// if (!ft_open_and_pipe(file, pipex))
	// 	exit (0);
	// if (!ft_execve(pipex))
	// 	exit (0);
	return (1);
}
