/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:27:31 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/04 17:17:19 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"

static int	exsist_cmds(t_pipex *pipex, char **paths);
static char	*exsist_cmds_utils(char **paths, char *cmd);
static int	permis_cmds(t_pipex *pipex);

int	fill_cmds(char **argv, t_pipex *pipex, t_cmds *s_tmp)
{
	int		tmp;

	tmp = 0;
	while (tmp < pipex->argc - 4)
	{
		s_tmp->next = malloc(sizeof(t_cmds));
		if (!s_tmp->next)
			return (0);
		s_tmp = s_tmp->next;
		s_tmp->next = NULL;
		s_tmp->flags = ft_split(*argv, 32);
		if (!s_tmp->flags)
			return (0);
		s_tmp->cmd = *(s_tmp->flags++);
		argv++;
		tmp++;
	}
	return (1);
}

int	parse_cmds(t_pipex *pipex)
{
	if (!exsist_cmds(pipex, pipex->path))
		return (0);
	if (!permis_cmds(pipex))
		return (0);
	return (1);
}

static int	exsist_cmds(t_pipex *pipex, char **paths)
{
	t_cmds	*t_tmp;
	char	*cmd;

	t_tmp = pipex->cmds;
	while (t_tmp)
	{
		if (access(t_tmp->cmd, F_OK))
		{
			cmd = ft_strjoin("/\0", t_tmp->cmd);
			if (!cmd)
				return (0);
			t_tmp->cmd = exsist_cmds_utils(paths, cmd);
			if (!t_tmp->cmd)
				return (0);
		}
		t_tmp = t_tmp->next;
	}
	return (1);
}

static char	*exsist_cmds_utils(char **paths, char *cmd)
{
	char	*tmp;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, cmd);
		if (!tmp)
			return (NULL);
		if (!access(tmp, F_OK))
			return (tmp);
		free(tmp);
		paths++;
	}
	ft_pipex_error("zsh: command not found: ", cmd + 1, 0);
	return (NULL);
}

static int	permis_cmds(t_pipex *pipex)
{
	t_cmds	*tmp;
	int		ret;

	tmp = pipex->cmds;
	ret = 1;
	while (tmp)
	{
		if (access(tmp->cmd, X_OK))
			ret = ft_pipex_error("zsh: permision deneied: ", tmp->cmd, 0);
		tmp = tmp->next;
	}
	return (ret);
}
