/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:28:32 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/10 21:51:39 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"
#include <stdlib.h>
#include <sys/wait.h>

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
			pip->cmds = malloc(sizeof(t_cmds));
			if (!pip->cmds)
				exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
			check_cmd(pip, pip->cmds);
			if (pip->utils->error)
				exit (clean_exit(pip, 0));
			// execv_cmd(pip);
			exit (clean_exit(pip, 1));// ------ FALTA EL MSG THE EXECV
		}
		iter++;
		waitpid(pid, &status, 0);
	}
}
