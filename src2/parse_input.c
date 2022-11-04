/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:53:20 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/04 02:02:27 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "bmlib.h"

static int	parse_files(char *inpf, char *outpf, t_pipex *pipex);
static int	get_path(t_pipex *pipex, char **env, char *path_compare);
static int	parse_comands(char **argv, t_pipex *pipex);

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
		pipex->error = 1;
	if (!get_path(pipex, env, "PATH="))
		return (0);
	if (!parse_comands(argv + 2, pipex))
		return (0);
	return (1);
}

static int	parse_files(char *inpf, char *outpf, t_pipex *pipex)
{
	if (access(inpf, F_OK) != 0)
		return (ft_pipex_error("zsh: no such file or directory: ", inpf, 1));
	else if (access(inpf, R_OK) != 0)
		return (ft_pipex_error("zsh: permission denied: ", inpf, 1));
	if (access(outpf, F_OK) == 0 && access(outpf, W_OK) != 0)
		return (ft_pipex_error("zsh: permission denied: ", outpf, 1));
	pipex->inpfd = open(inpf, O_RDONLY);
	if (!pipex->inpfd)
		return (ft_pipex_error("zsh: error opening file: ", inpf, 1));
	pipex->outfd = open(outpf, O_CREAT);
	if (!pipex->outfd)
		return (ft_pipex_error("zsh: error opening file: ", outpf, 1));
	return (1);
}

static int	get_path(t_pipex *pipex, char **env, char *path_compare)
{
	while (*env)
	{
		if (!ft_strncmp(*env, path_compare, 5))
			break ;
		env++;
	}
	if (!*env)
		return (ft_pipex_error("zsh:",
				" PATH environment variable not found", 0));
	pipex->path = ft_split(*env + 5, ':' );
	if (!pipex->path)
		return (ft_pipex_error("pipex:",
				" error trying to allocate memory", 0));
	return (1);
}

static int	parse_comands(char **argv, t_pipex *pipex)
{
	pipex->cmds = malloc(sizeof(t_cmds));
	if (!pipex->cmds)
		return (0);
	pipex->cmds->flags = ft_split(*argv, 32);
	if (!pipex->cmds->flags)
		return (0);
	pipex->cmds->cmd = *(pipex->cmds->flags++);
	if (!fill_cmds(++argv, pipex, pipex->cmds))
		return (0);
	if (!parse_cmds(pipex))
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
