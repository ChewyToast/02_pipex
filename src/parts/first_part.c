/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:02:10 by bruno             #+#    #+#             */
/*   Updated: 2022/11/08 17:48:05 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

void	first_part(t_pipex *pip)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		pip->utils->exit_status = 1;
		return ;//	------- ERROR EXIT
	}
	else if (!pid)
	{
		if (get_path())
			exit ()//	------- ERROR EXIT
		if (check_file())
			exit ()//	------- ERROR EXIT
		if (check_cmd())
			exit ()//	------- ERROR EXIT
		if (execv_cmd())
			exit ()//	------- ERROR EXIT
		exit (0);
	}
	waitpid(pid, &status, 0);
	pip->utils->exit_status = WEXITSTATUS(status);
}