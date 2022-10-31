/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:38:36 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/10/31 19:42:49 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "bmlib.h"

char	*get_comand(char **all_path, char **argv);
char	**get_path(char **env, char *path_compare);
char	*get_comand_util(char *rtrn, char *tmp, char **all_path, char **argv);

int	main(int argc, char **argv, char **env)
{
	char	*util;

	util = NULL;
	if (argc < 2)
		return (0);
	util = get_comand(get_path(env, "PATH="), argv + 1);
	if (!util)
		return (0);
}
