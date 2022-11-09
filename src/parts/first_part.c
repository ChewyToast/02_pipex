/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:02:10 by bruno             #+#    #+#             */
/*   Updated: 2022/11/09 22:40:20 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"
#include <stdlib.h>

void	first_part(t_pipex *pip)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		pip->utils->exit_status = 1;
		exit (error_msg(NULL, "bash", ECF, 1));
	}
	else if (!pid)
	{
		get_path(pip, "PATH=");
		check_file(*(pip->inputs->argv + 1), R_OK, pip);
		check_cmd(pip, pip->cmds);
		// execv_cmd(pip);
		exit (clean_exit(pip, 0));
	}
	waitpid(pid, &status, 0);
	pip->utils->exit_status = WEXITSTATUS(status);
}