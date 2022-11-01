/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:53:20 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/01 20:54:03 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "pipex_struct.h"
#include "bmlib.h"

static int	check_files(char *inpf, char *outpf, t_pipex *pipex);
static	int	ft_pipex_error(char *first, int errono);

/*
 Here we start the parsing of the input from the files, checking if they exist

 or not and if they have the necessary permissions. Then we continue looking

 at the commands that must be executed, we must find the PATH, if they exist

 and if we have access.
*/

int	parse_input(int argc, char **argv, char **env, t_pipex *pipex)
{
	if (argc != 5)
		return (ft_pipex_error("Error:", 158));
	if (!check_files(*(argv + 1), *(argv + argc), pipex))
		return (0);
	pipex->argc = argc;
	pipex->path = get_path(env, "PATH=");
	if (!pipex->path)
	{
		close (pipex->inpfd);
		close (pipex->outfd);
		return (ft_pipex_error("Error:", -1));
	}
	if (!parse_comands(argv + 2, pipex))
		return (ft_pipex_error("Parse:", -2));
	return (1);
}

static int	check_files(char *inpf, char *outpf, t_pipex *pipex)
{
	if (access(inpf, F_OK) != 0)
		return (ft_pipex_error(inpf, 0));
	if (access(inpf, R_OK) != 0)
		return (ft_pipex_error(inpf, 0));
	if (access(outpf, F_OK) == 0 && access(outpf, W_OK) != 0)
		return (ft_pipex_error(outpf, 0));
	pipex->inpfd = open(inpf, O_RDONLY);
	if (!pipex->inpfd)
		return (ft_pipex_error(inpf, -3));
	pipex->outfd = open(inpf, O_WRONLY | O_CREAT, 0666);
	if (!pipex->outfd)
	{
		close (pipex->inpfd);
		return (ft_pipex_error(outpf, 0));
	}
	return (1);
}

static	int	ft_pipex_error(char *first, int errono)
{
	if (errono == 0)
		perror(0);
	else if (errono == -1)
		perror(" Path not found\n");
	else if (errono == -2)
		perror(" Error parsing the input\n");
	else if (errono == -3)
		perror(": File open error");
	else
		perror(strerror(errono));
	return (0);
}
