/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:53:20 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/03 00:53:54 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "bmlib.h"

static int	parse_files(char *inpf, char *outpf, t_pipex *pipex);

/*
 Here we start the parsing of the input from the files, checking if they exist

 or not and if they have the necessary permissions. Then we continue looking

 at the commands that must be executed, we must find the PATH, if they exist

 and if we have access.
*/

int	parse_input(int argc, char **argv, char **env, t_pipex *pipex)
{
	if (argc != 5)
		return (ft_pipex_error("zsh:", " Wrong number of parameters", 0));
	if (!parse_files(*(argv + 1), *(argv + argc - 1), pipex))
		return (0);
	if (!get_path(pipex, env, "PATH="))
		return (0);
	if (!parse_comands(argv + 2, pipex))
		return (ft_pipex_error("zsh:", " parse_comands error", 0));
	return (1);
}

int	parse_comands(char **argv, t_pipex *pipex)
{
	pipex->cmds = malloc(sizeof(t_cmds));
	if (!pipex->cmds)
		return (0);
	pipex->cmds->flags = ft_split(*argv, 32);
	if (!pipex->cmds->flags)
		return (0);
	pipex->cmds->cmd = *(pipex->cmds->flags++);
	if (!parse_comands_util(++argv, pipex, pipex->cmds))
		return (0);
	return (1);
}

static int	parse_files(char *inpf, char *outpf, t_pipex *pipex)
{
	int	tmp;

	tmp = 0;
	if (access(inpf, F_OK) != 0)
		tmp = ft_pipex_error("zsh: no such file or directory: ", inpf, 1);
	else if (access(inpf, R_OK) != 0)
		tmp = ft_pipex_error("zsh: permission denied: ", inpf, 1);
	if (access(outpf, F_OK) == 0 && access(outpf, W_OK) != 0)
		tmp = ft_pipex_error("zsh: permission denied: ", outpf, 1);
	pipex->inpfd = open(inpf, O_RDONLY);
	if (!pipex->inpfd)
		tmp = ft_pipex_error("zsh: error opening file: ", inpf, 1);
	pipex->outfd = open(outpf, O_CREAT);
	if (!pipex->outfd)
		tmp = ft_pipex_error("zsh: error opening file: ", outpf, 1);
	if (tmp)
		return (0);
	return (1);
}

int	ft_pipex_error(char *first, char *second, int ret)
{
	write(2, first, ft_strlen(first));
	write(2, second, ft_strlen(second));
	write(2, "\n", 1);
	return (ret);
}
