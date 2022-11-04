/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:48:54 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/04 20:49:52 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include <stdio.h>

# include <unistd.h>

# include <fcntl.h>

# include "pipex_struct.h"

//	--------parse_input.c
int			ft_pipex_error(char *first, char *second, int ret);

//	--------parse_first_part.c
int			parse_first_part(char *file, t_pipex *pipex);

//	--------parse_utils.c
int			ft_check_file(char *file, int mode);
int			ft_check_cmd(t_pipex *pipex, char **path);

#endif