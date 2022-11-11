/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:55:19 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/11 16:50:28 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"
#include "pipex_utils.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pip;

	if (argc != 5)
		exit (error_msg(NULL, "bash", INA, 1));
	if (!init_pipex(argc, argv, env, &pip))
		exit(error_msg(NULL, "bash", MKO, 1));
	first_part(&pip);
	//second_part(&pip);
	third_part(&pip);
	exit (clean_exit(&pip, pip.utils->exit_status));
}
