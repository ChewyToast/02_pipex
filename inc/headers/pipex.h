/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:55:30 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/07 23:29:36 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>

# include <unistd.h>

# include <fcntl.h>

# include "pipex_struct.h"

void	show_input(t_pipex *pipex);

//	--------pipex.c
static int	init_pipex(int argc, t_pipex *pipex, char **env);
int			ft_pipex_error(char *first, char *second, char *thrd, int ret);

//	--------parse_input.c
int			parse_input(char **argv, char **env, t_pipex *pipex);

# define MKO "error trying to allocate memory"

#endif