/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:08:37 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/30 23:29:25 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "bmlib.h"

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

int	check_file(char *file, int mode, t_pipex *pip)
{
	pip->utils->error = 1;
	pip->utils->exit_status = 1;
	if (mode == R_OK)
	{
		if (access(file, F_OK))
			return (error_msg("pipex: ", file, NFD, 0));
		else if (access(file, mode))
			return (error_msg("pipex: ", file, PMD, 0));
	}
	else
	{
		if (!access(file, F_OK))
		{
			if (access(file, mode))
				return (error_msg(BSH, file, PMD, 0));
		}
	}
	pip->utils->error = 0;
	pip->utils->exit_status = 0;
	return (1);
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

void	extra_loop(t_pipex *pip, int *pipes)
{
	int		tmp;
	char	*read;

	tmp = 1;
	close(pipes[0]);
	if (write(1, "> ", 2) < 0)
		exit (error_msg(BSH, "write", BFD, clean_exit(pip, 1)));
	read = get_next_line(0);
	while (read && (ft_strncmp(read, *(pip->inputs->argv + 2),
				ft_strlen(read) - tmp)))
	{
		tmp = 0;
		if (write(pipes[1], read, ft_strlen(read)) < 0)
			exit (error_msg(BSH, "write", BFD, clean_exit(pip, 1)));
		if (write(1, "> ", 2) < 0)
			exit (error_msg(BSH, "write", BFD, clean_exit(pip, 1)));
		read = get_next_line(0);
		if (ft_strlen(read) == 1 && ft_strlen(*(pip->inputs->argv + 2)) < 1)
			break ;
		if (read && ft_strlen(read) > 1)
			tmp = 1;
	}
	if (!read)
		exit(error_msg(NULL, "pipex", MKO, 1));
	exit (0);
}
