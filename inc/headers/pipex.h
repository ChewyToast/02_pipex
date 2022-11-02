/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:55:30 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/03 00:54:55 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>

# include <unistd.h>

# include <fcntl.h>

typedef struct s_pipex	t_pipex;
typedef struct s_cmds	t_cmds;

int		parse_input(int argc, char **argv, char **env, t_pipex *pipex);
char	*get_comand(char **all_path, char **argv);
int		get_path(t_pipex *pipex, char **env, char *path_compare);
int		parse_comands(char **argv, t_pipex *pipex);
int		parse_comands_util(char **argv, t_pipex *pipex, t_cmds *s_tmp);
int		ft_pipex_error(char *first, char *second, int ret);
void	show_input(t_pipex *pipex);

struct s_cmds
{
	char	*cmd;
	char	**flags;
	t_cmds	*next;
};

struct s_pipex
{
	int		inpfd;
	int		outfd;
	int		argc;
	char	**path;
	t_cmds	*cmds;
};

#endif