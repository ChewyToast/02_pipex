/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:43:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/04 22:56:33 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"
#include "bmlib.h"

static int	first_check_cmd_util(t_pipex *pipex);
static int	second_check_cmd_util(t_pipex *pipex, char **path, char *comnd);
static int	end_check_cmd(char *str2, char *str3, int ret);

int	ft_check_file(char *file, int mode)
{
	if (mode == R_OK)
	{
		if (access(file, F_OK))
			return (ft_pipex_error("bash: no such file or directory: ",
					file, 0));
		else if (access(file, mode))
			return (ft_pipex_error("bash: permission denied: ", file, 0));
	}
	else
	{
		if (!access(file, F_OK))
		{
			if (access(file, mode))
				return (ft_pipex_error("bash: permission denied: ", file, 0));
		}
	}
	return (1);
}

int	ft_check_cmd(t_pipex *pipex, char **path)
{
	char	*comnd;

	if (!access(pipex->cmds->cmd, F_OK))
		return (first_check_cmd_util(pipex));
	else
	{
		comnd = ft_strjoin("/\0", pipex->cmds->cmd);
		if (!comnd)
			return (ft_pipex_error("bash:", " error allocating memory", 0));
		if (!second_check_cmd_util(pipex, path, comnd))
			return (0);
	}
	return (1);
}

static int	first_check_cmd_util(t_pipex *pipex)
{
	if (!access(pipex->cmds->cmd, X_OK))
		return (1);
	ft_pipex_error("bash: permission denied: ", pipex->cmds->cmd, 0);
	return (0);
}

static int	second_check_cmd_util(t_pipex *pipex, char **path, char *comnd)
{
	char	*tmp;

	while (*path)
	{
		tmp = ft_strjoin(*path, comnd);
		if (!tmp)
			return (end_check_cmd(NULL, comnd,
					ft_pipex_error("bash:", " error allocating memory", 0)));
		if (!access(tmp, F_OK))
		{
			if (!access(tmp, X_OK))
			{
				pipex->cmds->cmd = tmp;
				return (end_check_cmd(NULL, comnd, 1));
			}
			else
				return (end_check_cmd(comnd, tmp,
						ft_pipex_error("bash: permission denied: ", tmp, 0)));
		}
		free(tmp);
		path++;
	}
	return (end_check_cmd(comnd, NULL,
			ft_pipex_error("bash: command not found: ", comnd + 1, 0)));
}

static int	end_check_cmd(char *str2, char *str3, int ret)
{
	(void)ret;
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	return (ret);
}
