/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:55:19 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/08 17:43:19 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_utils.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pip;

	init_pipex(argc, &pipex, env);
	first_part(&pip);
	second_part(&pip);
	third_part(&pip);
	exit (pip.utils->exit_status);
}
