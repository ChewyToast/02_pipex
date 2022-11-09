/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:36:47 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/09 22:44:45 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"
#include <stdlib.h>

void	third_part(t_pipex *pip)
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
		check_file(*(pip->inputs->argv + (pip->inputs->argc - 1)), W_OK, pip);
		pip->inputs->argv += pip->inputs->argc - 4;
		check_cmd(pip, pip->cmds);
		// execv_cmd(pip);
		exit (0);
	}
	waitpid(pid, &status, 0);
	pip->utils->exit_status = WEXITSTATUS(status);
}