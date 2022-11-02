/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:45:47 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/02 19:46:44 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "pipex_struct.h"
#include "bmlib.h"

static char	*get_comand_util(char *rtrn,
				char *tmp, char **all_path, char **argv);

// Here we get the array of strings of the possible PATHs for the commands.
char	**get_path(char **env, char *path_compare)
{
	while (*env)
	{
		if (!ft_strncmp(*env, path_compare, 5))
			break ;
		env++;
	}
	if (!*env)
		return (NULL);
	return (ft_split(*env + 5, ':' ));
}

// Here we fill in the list of commands with their respective flags, to later
// confirm if they can be executed
int	parse_comands(char **argv, t_pipex *pipex)
{
	int		tmp;
	t_cmds	*s_tmp;

	tmp = 0;
	pipex->cmds = malloc(sizeof(t_cmds));
	if (!pipex->cmds)
		return (0);
	pipex->cmds->flags = ft_split(*argv, 32);
	// ft_printf("\nAFTER SPLIT, pipex->cmds->flags = <%s>\n", *pipex->cmds->flags);
	if (!pipex->cmds->flags)
		return (0);
	pipex->cmds->cmd = *(pipex->cmds->flags++);
	// ft_printf("\npipex->cmds->cmd = <%s>\n", pipex->cmds->cmd);
	// ft_printf("\npipex->cmds->flags = <%s>\n", *pipex->cmds->flags);
	s_tmp = pipex->cmds;
	argv++;
	while (tmp < pipex->argc - 4)
	{
		s_tmp->next = malloc(sizeof(t_cmds));
		if (!s_tmp->next)
		{
//			ft_free_cmds(pipex->cmds);
			return (0);
		}
		s_tmp = s_tmp->next;
		s_tmp->next = NULL;
		// ft_printf("\nHI, tmp: %d, pipex->argc - 1: %d\n", tmp, pipex->argc - 1);
		s_tmp->flags = ft_split(*argv, 32);
		if (!s_tmp->flags)
		{
//			ft_free_cmds(pipex->cmds);
			return (0);
		}
		s_tmp->cmd = *(s_tmp->flags++);
		argv++;
		tmp++;
	}
	// ft_printf("\nFINISH\n");
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
