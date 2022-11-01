/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:55:30 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/01 20:34:41 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "pipex.h"
#include "pipex_struct.h"
#include "bmlib.h"

# include <stdio.h>

# include <unistd.h>

# include <fcntl.h>

int	parse_input(int argc, char **argv, char **env, t_pipex *pipex);
char	*get_comand(char **all_path, char **argv);
char	**get_path(char **env, char *path_compare);
int	parse_comands(char **argv, t_pipex *pipex);

#endif