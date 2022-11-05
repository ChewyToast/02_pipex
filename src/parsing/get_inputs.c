/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 23:02:59 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/05 01:09:39 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"
#include "bmlib.h"

int	get_argv(char **argv, t_pipex *pipex, t_cmds *tmp)
{
	int		i;

	i = 4;
	pipex->cmds = malloc(sizeof(t_cmds));
	if (!pipex->cmds)
		return (ft_pipex_error(NULL, "bash: ", MKO, 0));
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

int	get_path(t_pipex *pipex, char **env, char *path_compare)
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
			ft_pipex_error("bash: ", tmp->cmd,
				": No such file or directory", 0);
			tmp = tmp->next;
		}
		return (0);
	}
	pipex->path = ft_split(*env + 5, ':' );
	if (!pipex->path)
		return (ft_pipex_error(NULL, "bash: ", MKO, 0));
	return (1);
}
