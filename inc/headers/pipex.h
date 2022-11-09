/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:55:30 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/09 22:16:58 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "pipex_struct.h"

//	--------pipex.c
int			init_pipex(int argc, char **argv, char **env, t_pipex *pip);
void		first_part(t_pipex *pip);

#endif