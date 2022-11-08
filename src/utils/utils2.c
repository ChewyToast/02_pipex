/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:49:07 by bruno             #+#    #+#             */
/*   Updated: 2022/11/08 20:45:13 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_struct.h"

int	get_path(pip, char *path_compare)
{
	while (*(pip->inputs->env))
	{
		if (!ft_strncmp(*(pip->inputs->env), path_compare, 5))
			break;
		env++;
	}
	if (!*(pip->inputs->env))7
}