/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:55:30 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/11 20:03:06 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex_struct.h"

//	--------pipex.c
int			init_pipex(int argc, char **argv, char **env, t_pipex *pip);
void		first_part(t_pipex *pip);
void		second_part(t_pipex *pip);
void		third_part(t_pipex *pip);

#endif