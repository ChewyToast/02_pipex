/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:48:54 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/05 01:11:28 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include <stdio.h>

# include <unistd.h>

# include <fcntl.h>

# include "pipex_struct.h"

//	--------parse_input.c
int			ft_pipex_error(char *first, char *second, char *thrd, int ret);

//	--------get_inputs.c
int			get_argv(char **argv, t_pipex *pipex, t_cmds *tmp);
int			get_path(t_pipex *pipex, char **env, char *path_compare);

//	--------parse_utils.c
int			ft_check_file(char *file, int mode);
int			ft_check_cmd(t_cmds *cmd, char **path);

//	--------parse_first_part.c
int			parse_first_part(char *file, t_pipex *pipex);

//	--------parse_second_part.c
int			parse_second_part(t_pipex *pipex);

//	--------parse_third_part.c
int	parse_third_part(char *file, t_pipex *pipex);

# define MKO "error trying to allocate memory"

#endif