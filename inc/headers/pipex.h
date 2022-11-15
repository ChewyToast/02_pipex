/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:32:12 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/15 20:50:17 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>

# include <unistd.h>

# include <fcntl.h>

# include <sys/wait.h>

# include "pipex_struct.h"

//	--------pipex.c
void		first_part(t_pipex *pip);
void		second_part(t_pipex *pip);

//	--------utils1.c
int			init_pipex(int argc, char **argv, char **env, t_pipex *pip);
int			clean_exit(t_pipex *pip, int ret);
int			error_msg(char *first, char *second, char *thrd, int ret);
void		get_path(t_pipex *pip, char *path_compare);
void		check_file(char *file, int mode, t_pipex *pip);
void		check_cmd(t_pipex *pip, t_cmds *cmd);

char	**ft_cmd_split(char *input);

#endif