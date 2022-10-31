/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:35:16 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/10/31 20:51:19 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "bmlib.h"

char	*get_comand(char **all_path, char **argv);
char	**get_path(char **env, char *path_compare);
char	*get_comand_util(char *rtrn, char *tmp, char **all_path, char **argv);
char	**get_path(char **env, char *path_compare)
{
	while (*env)
		if (!ft_strncmp(*(env++), path_compare, 5))
			break ;
	if (!*env)
		return (NULL);
	return (ft_split(*(--env) + 5, ':' ));
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
	ft_printf("\nCOMAND: %s\n", rtrn);
	return (rtrn);
}

char	*get_comand_util(char *rtrn, char *tmp, char **all_path, char **argv)
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
		ft_printf("\ntry: %s\n", tmp);
		if (!access(tmp, X_OK))
			break ;
		free(tmp);
	}
	free(rtrn);
	if (tmp)
		return (tmp);
	else
		return (NULL);
}
