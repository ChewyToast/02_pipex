/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:49:40 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/04 23:35:41 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_STRUCT_H
# define PIPEX_STRUCT_H

typedef struct s_pipex	t_pipex;
typedef struct s_cmds	t_cmds;

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
	int		util;
	char	**path;
	t_cmds	*cmds;
};

#endif