/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:35:46 by bruno             #+#    #+#             */
/*   Updated: 2022/11/11 20:05:53 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_UTILS_BONUS_H
# define PIPEX_UTILS_BONUS_H

# include "pipex_struct.h"

// 	--------utils1.c
int		clean_exit(t_pipex *pip, int ret);
int		error_msg(char *first, char *second, char *thrd, int ret);
void	get_path(t_pipex *pip, char *path_compare);
void	check_file(char *file, int mode, t_pipex *pip);
void	check_cmd(t_pipex *pip, t_cmds *cmd);

#endif