/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:43:00 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/07 21:04:44 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"
#include "bmlib.h"

static int	first_check_cmd_util(t_cmds *cmd);
static int	second_check_cmd_util(t_cmds *cmd, char **path, char *comnd);
static int	end_check_cmd(char *str2, char *str3, int ret);

int	ft_check_file(char *file, int mode)
{
	if (mode == R_OK)
	{
		if (access(file, F_OK))
			return (ft_pipex_error("bash: ", file,
					": No such file or directory", 0));
		else if (access(file, mode))
			exit (ft_pipex_error("bash: ", file,
					": Permission denied", 1));
	}
	else
	{
		if (!access(file, F_OK))
		{
			if (access(file, mode))
				exit (ft_pipex_error("bash: ", file,
						": Permission denied", 1));
		}
	}
	return (1);
}

int	ft_check_cmd(t_cmds *cmd, char **path)
{
	char	*comnd;

	if (!access(cmd->cmd, F_OK))
		return (first_check_cmd_util(cmd));
	else
	{
		comnd = ft_strjoin("/\0", cmd->cmd);
		if (!comnd)
			exit (ft_pipex_error(NULL, "bash:",
					" error allocating memory", 1));
		if (!second_check_cmd_util(cmd, path, comnd))
			return (0);
	}
	return (1);
}

static int	first_check_cmd_util(t_cmds *cmd)
{
	if (!access(cmd->cmd, X_OK))
		return (1);
	ft_pipex_error("bash: ", cmd->cmd, ": Permission denied", 0);
	exit (1);
}

static int	second_check_cmd_util(t_cmds *cmd, char **path, char *comnd)
{
	char	*tmp;

	while (*path)
	{
		tmp = ft_strjoin(*path, comnd);
		if (!tmp)
			return (end_check_cmd(NULL, comnd,
					ft_pipex_error(NULL, "bash:", MKO, 0)));
		if (!access(tmp, F_OK))
		{
			if (!access(tmp, X_OK))
			{
				cmd->cmd = tmp;
				return (end_check_cmd(NULL, comnd, 1));
			}
			else
				exit (end_check_cmd(comnd, tmp,
						ft_pipex_error("bash: ", tmp,
							": Permission denied", 1)));
		}
		free(tmp);
		path++;
	}
	exit (end_check_cmd(comnd, NULL,
			ft_pipex_error("bash: ", comnd + 1, ": command not found", 127)));
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
