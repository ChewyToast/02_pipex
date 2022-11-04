/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:13:25 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/04 22:56:52 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"
#include "bmlib.h"

static int	get_argv(char **argv, t_pipex *pipex, t_cmds *tmp);
static int	get_path(t_pipex *pipex, char **env, char *path_compare);

int	parse_input(char **argv, char **env, t_pipex *pipex)
{
	int	ret;

	ret = 1;
	if (pipex->argc != 5)
		return (ft_pipex_error("pipex:", " Invalid number of arguments", 0));
	if (!get_argv(argv + 2, pipex, pipex->cmds))
		return (0);
	if (!get_path(pipex, env, "PATH="))
		return (0);
	ret += parse_first_part(*(argv + 1), pipex);
	return (ret > 1);
}

static int	get_argv(char **argv, t_pipex *pipex, t_cmds *tmp)
{
	int		i;

	i = 3;
	pipex->cmds = malloc(sizeof(t_cmds));
	if (!pipex->cmds)
		return (0);
	pipex->cmds->flags = ft_split(*argv, ' ');
	pipex->cmds->cmd = *(pipex->cmds->flags++);
	argv++;
	tmp = pipex->cmds;
	while (pipex->argc > i && *(argv - 1))
	{
		tmp->next = malloc(sizeof(t_cmds));
		if (!tmp->next)
			return (0);
		tmp = tmp->next;
		tmp->flags = ft_split(*argv, ' ');
		if (!tmp->flags)
			return (0);
		tmp->cmd = *(tmp->flags++);
		tmp->next = NULL;
		argv++;
		i++;
	}
	return (1);
}

static int	get_path(t_pipex *pipex, char **env, char *path_compare)
{
	t_cmds	*tmp;

	while (*env)
	{
		if (!ft_strncmp(*env, path_compare, 5))
			break ;
		env++;
	}
	if (!*env)
	{
		tmp = pipex->cmds;
		while (tmp)
		{
			write(2, "bash: ", 6);
			ft_pipex_error(tmp->cmd, ": No such file or directory", 0);
			tmp = tmp->next;
		}
		return (0);
	}
	pipex->path = ft_split(*env + 5, ':' );
	if (!pipex->path)
		return (ft_pipex_error("pipex:",
				" error trying to allocate memory", 0));
	return (1);
}

int	ft_pipex_error(char *first, char *second, int ret)
{
	write(2, first, ft_strlen(first));
	write(2, second, ft_strlen(second));
	write(2, "\n", 1);
	return (ret);
}
