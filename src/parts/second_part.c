/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:28:32 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/09 23:03:25 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"
#include <stdlib.h>

void	second_part(t_pipex *pip)
{
	int		status;
	int		iter;
	pid_t	pid;

	iter = 1;
	while(iter < pip->inputs->argc - 4)
	{
		pid = fork();
		if (pid < 0)
		{
			pip->utils->exit_status = 1;
			exit (error_msg(NULL, "bash", ECF, 1));
		}
		else if (!pid)
		{
			get_path(pip, "PATH=");
			pip->inputs->argv += iter;
			check_cmd(pip, pip->cmds);
			// execv_cmd(pip);
			exit (clean_exit(pip, 0));
		}
		iter++;
		waitpid(pid, &status, 0);
		pip->utils->exit_status = WEXITSTATUS(status);
	}
}