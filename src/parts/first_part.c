/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 04:58:17 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/07 23:43:43 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"
#include "bmlib.h"

static int	do_child(char *file, t_pipex *pipex);
static int	do_father(pid_t pid, int status);

int	parse_first_part(char *file, t_pipex *pipex)
{
	pid_t	pid;

	pipex->pipes = malloc(sizeof(int) * 2);
	if (!pipex->pipes)
		return (ft_pipex_error(NULL, "bash:", MKO, 0));
	if (pipe(pipex->pipes) < 0)
		return (ft_pipex_error(NULL, "bash:", "error creating pipe()", 0));
	pid = fork();
	if (pid < 0)
		return (ft_pipex_error(NULL, "bash:", " error creating fork()", 0));
	if (!pid)
		return (do_child(file, pipex));
	else
		return (do_father(pid, 0));
}

static int	do_child(char *file, t_pipex *pipex)
{
	close(pipex->pipes[0]);
	if (!ft_check_file(file, R_OK))
			exit (1);
	if (!ft_check_cmd(pipex->cmds, pipex->path))
			exit (1);
	pipex->inpfd = open(file, O_RDONLY);
	if (pipex->inpfd < 0)
		exit (ft_pipex_error("bash:", file, ": Cannot open", 1));
	if (dup2(0, pipex->inpfd) < 0)
		exit (ft_pipex_error("bash:", " dup2", ": Bad file descriptor", 1));
	if (dup2(pipex->pipes[1], 1) < 0)
		exit (ft_pipex_error("bash:", " dup2", ": Bad file descriptor", 1));
	execve(pipex->cmds->cmd, pipex->cmds->flags, pipex->env);
	exit (1);
}

static int	do_father(pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	ft_printf("exit value: %d\n", WEXITSTATUS(status));
	return (!WEXITSTATUS(status));// NO ESTIC SEGUR SI HA DE SER NEGAT O NO
}