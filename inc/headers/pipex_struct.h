/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:56:41 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/28 23:27:19 by bmoll-pe         ###   ########.fr       */
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
	t_utils	*utils;
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
	char	*path_comand;
	char	**cmd;
};

struct s_utils
{
	int		error;
	int		pipes[2];
	char	**path;
	int		exit_status;
};

# define BSH "bash: "
# define PPX "pipex: "
# define CNO ": Cannot open"
# define CNF ": command not found"
# define PMD ": Permission denied"
# define BFD ": Bad file descriptor"
# define ECP ": error creating pipe"
# define ECF ": error creating fork"
# define NFD ": No such file or directory"
# define INA ": Invalid number of arguments"
# define MKO ": error trying to allocate memory"

#endif