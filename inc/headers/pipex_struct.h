/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:49:40 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/08 17:51:14 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_STRUCT_H
# define PIPEX_STRUCT_H

# include <stdio.h>

# include <unistd.h>

# include <fcntl.h>

# include "pipex_struct.h"

typedef struct s_pipex	t_pipex;
typedef struct s_input	t_input;
typedef struct s_cmds	t_cmds;
typedef struct s_utils	t_utils;

struct s_pipex
{
	t_utils *utils;
	t_input	*inputs;
	t_cmds	*cmds;
};

struct s_input
{
	int		inpfd;
	int		outfd;
	int		argc;
	char	**argv;
	char	**env;
};

struct s_cmds
{
	char	**cmd;
	t_cmds	*next;
};

struct s_utils
{
	int		util;
	int		*pipes;
	char	**path;
	int		exit_status;
};

# define CNF ": command not found"
# define PMD ": Permission denied"
# define BFD ": Bad file descriptor"
# define ECP ": error creating pipe"
# define ECF ": error creating fork"
# define NFD ": No such file or directory"
# define INA ": Invalid number of arguments"
# define MKO ": error trying to allocate memory"

#endif