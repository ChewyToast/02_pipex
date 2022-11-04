/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_first_part.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:19:02 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/04 22:46:33 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"
#include "bmlib.h"

int	parse_first_part(char *file, t_pipex *pipex)
{
	pid_t	pid;
	int		status;

	(void)pipex;
	pid = fork();
	if (pid < 0)
		return (ft_pipex_error("bash:", " error creating first fork()", 0));
	if (!pid)
	{
		if (!ft_check_file(file, R_OK))
			exit (0);
		if (!ft_check_cmd(pipex, pipex->path))
			exit (0);
		exit (1);
	}
	else
	{
		waitpid(pid, &status, 0);
		ft_printf("\nWEXITSTATUS:%d\n", WEXITSTATUS(status));
		return (WEXITSTATUS(status));
	}
	return (1);
}
