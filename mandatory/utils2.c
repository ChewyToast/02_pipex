/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:49:07 by bruno             #+#    #+#             */
/*   Updated: 2022/11/30 23:02:59 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "pipex.h"

static int	check_cmd_while(t_pipex *pip, t_cmds *cmd);

void	get_path(t_pipex *pip, char *path_compare)
{
	size_t	count;

	count = 0;
	while (pip->inputs->env[count])
	{
		if (!ft_strncmp(pip->inputs->env[count], path_compare, 5))
			break ;
		count++;
	}
	if (pip->inputs->env[count])
	{
		pip->utils->path = ft_split(pip->inputs->env[count] + 5, ':');
		if (!pip->utils->path)
			exit (error_msg(NULL, "bash", MKO, 1));
	}
	else
	{
		pip->utils->path = ft_split(DEFPATH, ':');
		if (!pip->utils->path)
			exit (error_msg(NULL, "bash", MKO, 1));
	}
}

void	check_file(char *file, int mode, t_pipex *pip)
{
	if (mode == R_OK)
	{
		if (access(file, F_OK))
			exit (error_msg("pipex: ", file, NFD, clean_exit(pip, 1)));
		else if (access(file, mode))
			exit (error_msg("pipex: ", file, PMD, clean_exit(pip, 1)));
	}
	else
	{
		if (!access(file, F_OK))
		{
			if (access(file, mode))
				exit (error_msg(BSH, file, PMD, clean_exit(pip, 1)));
		}
	}
}

void	check_cmd(t_pipex *pip, t_cmds *cmd)
{
	char	*tmp;

	cmd->cmd = ft_cmd_split(*(pip->inputs->argv + 2));
	if (!cmd->cmd)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	cmd->pt_cmd = ft_substr(*(cmd->cmd), 0, ft_strlen(*(cmd->cmd)));
	if (!cmd->pt_cmd)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	if (pip->utils->path)
	{
		tmp = ft_strjoin("/\0", cmd->pt_cmd);
		if (!tmp)
			exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
		free(cmd->pt_cmd);
		cmd->pt_cmd = tmp;
		if (check_cmd_while(pip, cmd))
			return ;
		cmd->pt_cmd = ft_substr(tmp, 1, 0xffffffff);
		free(tmp);
	}
	if (access(cmd->pt_cmd, F_OK) || (ft_strnstr(cmd->pt_cmd, ".sh", 0xffffff)
			&& !ft_strrchr(cmd->pt_cmd, '/')))
		exit (clean_exit(pip, error_msg(PPX, cmd->pt_cmd, CNF, 127)));
	if (access(cmd->pt_cmd, X_OK))
		exit (clean_exit(pip, error_msg(BSH, cmd->pt_cmd, PMD, 126)));
}

static int	check_cmd_while(t_pipex *pip, t_cmds *cmd)
{
	size_t	iter;
	char	*tmp;

	iter = 0;
	while (pip->utils->path[iter])
	{
		tmp = ft_strjoin(pip->utils->path[iter], cmd->pt_cmd);
		if (!tmp)
			exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
		if (!access(tmp, F_OK))
		{
			if (!access(tmp, X_OK))
				break ;
			free(tmp);
			exit (clean_exit(pip, error_msg(BSH, cmd->pt_cmd,
						PMD, 1)));
		}
		free(tmp);
		iter++;
	}
	if (!pip->utils->path[iter])
		return (0);
	free(cmd->pt_cmd);
	cmd->pt_cmd = tmp;
	return (1);
}
