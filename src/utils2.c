/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomoll <brunomoll@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:49:07 by bruno             #+#    #+#             */
/*   Updated: 2022/11/20 02:01:01 by brunomoll        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"
#include "pipex.h"

static void	check_cmd_while(t_pipex *pip, t_cmds *cmd);

void	get_path(t_pipex *pip, char *path_compare)
{
	while (*(pip->inputs->env))
	{
		if (!ft_strncmp(*(pip->inputs->env), path_compare, 5))
			break ;
		pip->inputs->env++;
	}
	if (*(pip->inputs->env))
	{
		pip->utils->path = ft_split(*(pip->inputs->env) + 5, ':');
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
	cmd->path_comand = ft_substr(*(cmd->cmd), 0, ft_strlen(*(cmd->cmd)));
	if (!cmd->path_comand)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	if (access(cmd->path_comand, F_OK))
	{
		tmp = ft_strjoin("/\0", cmd->path_comand);
		if (!tmp)
			exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
		free(cmd->path_comand);
		cmd->path_comand = tmp;
		check_cmd_while(pip, cmd);
	}
}

static void	check_cmd_while(t_pipex *pip, t_cmds *cmd)
{
	size_t	iter;
	char	*tmp;

	iter = 0;
	if (pip->utils->path)
	{
		while (pip->utils->path[iter])
		{
			tmp = ft_strjoin(pip->utils->path[iter], cmd->path_comand);
			if (!tmp)
				exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
			if (!access(tmp, F_OK))
			{
				if (!access(tmp, X_OK))
					break ;
				free(tmp);
				exit (clean_exit(pip, error_msg(BSH, cmd->path_comand,
							PMD, 1)));
			}
			free(tmp);
			iter++;
		}
		if (!pip->utils->path[iter])
			exit (clean_exit(pip, error_msg("pipex: ",
						cmd->path_comand + 1, CNF, 127)));
	}
	else
		exit (clean_exit(pip, error_msg("pipex: ",
					cmd->path_comand + 1, CNF, 127)));
	free(cmd->path_comand);
	cmd->path_comand = tmp;
}
