/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:53:20 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/02 20:04:21 by bmoll-pe         ###   ########.fr       */
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
	// if (argc != 5)
	// 	return (ft_pipex_error("Error:", 158));
	if (!check_files(*(argv + 1), *(argv + argc - 1), pipex))
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
	ft_printf("\nINPF: <%s>\n", inpf);
	ft_printf("\nOUTPF: <%s>\n", outpf);
	if (access(inpf, F_OK) != 0)
		return (ft_pipex_error(inpf, 0));
	if (access(inpf, R_OK) != 0)
		return (ft_pipex_error(inpf, 0));
	if (access(outpf, F_OK) == 0 && access(outpf, W_OK) != 0)
		return (ft_pipex_error(outpf, 0));
	pipex->inpfd = open(inpf, O_RDONLY);
	if (!pipex->inpfd)
		return (ft_pipex_error(inpf, -3));
	pipex->outfd = open(outpf, O_CREAT);
	if (!pipex->outfd)
	{
		close (pipex->inpfd);
		return (ft_pipex_error(outpf, 1));
	}
	else
	{
		write(pipex->outfd, "asdf", 4);
	}
	return (1);
}

static	int	ft_pipex_error(char *first, int errono)
{
	(void)first;
	(void)errono;
	perror(first);
	// if (errono == 0)
	// 	perror(0);
	// else if (errono == -1)
	// 	perror(" Path not found\n");
	// else if (errono == -2)
	// 	perror(" Error parsing the input\n");
	// else if (errono == -3)
	// 	perror(": File open error");
	// else
	// 	perror(strerror(errono));
	return (0);
}
