/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:51:51 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/01 20:32:05 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "pipex_struct.h"
#include "bmlib.h"

/*
 This program consists of being able to execute and redirect programs

 and their inputs and outputs, so the first part of main will consist

 of checking that the files/directories and executables received as

 arguments are valid/accessible* and/or that they have the necessary

 execution permissions.
*/

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (!parse_input(argc, argv, env, &pipex))
		exit (0);
}
