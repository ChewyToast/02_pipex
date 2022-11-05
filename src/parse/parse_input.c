/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:13:25 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/05 03:50:15 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"
#include "bmlib.h"

int	parse_input(char **argv, char **env, t_pipex *pipex)
{
	int	ret;

	ret = 1;
	if (pipex->argc < 4)
		return (ft_pipex_error(NULL, "bash:",
				" Invalid number of arguments", 0));
	if (!get_argv(argv + 2, pipex, pipex->cmds))
		return (0);
	if (!get_path(pipex, env, "PATH="))
		return (0);
	ft_printf("*(argv + 1: %s\n", *(argv + 1));
	ret += parse_first_part(*(argv + 1), pipex);
	ret += parse_second_part(pipex);
	ft_printf("*(argv + (pipex->argc - 1): %s\n", *(argv + (pipex->argc - 1)));
	ret += parse_third_part(*(argv + (pipex->argc - 1)), pipex);
	return (ret > 3);
}

int	ft_pipex_error(char *first, char *second, char *thrd, int ret)
{
	size_t	len;

	if (!first)
		len = 0;
	else
		len = ft_strlen(first);
	write(2, first, len);
	write(2, second, ft_strlen(second));
	write(2, thrd, ft_strlen(thrd));
	write(2, "\n", 1);
	return (ret);
}
