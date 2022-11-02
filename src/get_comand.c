/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:45:47 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/03 00:53:55 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "bmlib.h"

static char	*get_comand_util(char *rtrn,
				char *tmp, char **all_path, char **argv);

int	get_path(t_pipex *pipex, char **env, char *path_compare)
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

int	parse_comands_util(char **argv, t_pipex *pipex, t_cmds *s_tmp)
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

char	*get_comand(char **all_path, char **argv)
{
	char	*rtrn;
	char	*tmp;

	rtrn = NULL;
	tmp = NULL;
	if (!all_path)
		rtrn = NULL;
	else if (!access(*argv, X_OK))
		rtrn = *argv;
	else
		rtrn = get_comand_util(rtrn, tmp, all_path, argv);
	ft_printf("COMAND: %s\n", rtrn);
	return (rtrn);
}

static char	*get_comand_util(char *rtrn,
		char *tmp, char **all_path, char **argv)
{
	rtrn = ft_strjoin("/\0", *argv);
	if (!rtrn)
		return (NULL);
	while (*all_path)
	{
		tmp = ft_strjoin(*(all_path++), rtrn);
		if (!tmp)
		{
			free(rtrn);
			return (NULL);
		}
		ft_printf("try: %s\n", tmp);
		if (!access(tmp, X_OK))
			break ;
		free(tmp);
		tmp = NULL;
	}
	free(rtrn);
	if (tmp)
		return (tmp);
	else
		return (NULL);
}
