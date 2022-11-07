/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:55:19 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/07 21:05:22 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bmlib.h"

static int	end_pipex(t_pipex *pipex);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (!init_pipex(argc, &pipex))
		return (end_pipex(&pipex));
	if (!parse_input(argv, env, &pipex))
		return (end_pipex(&pipex));
	end_pipex(&pipex);
	return (1);
}

static int	init_pipex(int argc, t_pipex *pipex)
{
	pipex->inpfd = 0;
	pipex->outfd = 0;
	pipex->util = 0;
	pipex->argc = argc;
	pipex->path = NULL;
	pipex->cmds = NULL;
	return (1);
}

static int	end_pipex(t_pipex *pipex)
{
	size_t	iter;
	t_cmds	*tmp;

	iter = 0;
	(void)tmp;
	if (pipex->inpfd)
		close(pipex->inpfd);
	if (pipex->outfd)
		close(pipex->outfd);
	if (pipex->path)
	{
		while (pipex->path[iter])
			free(pipex->path[iter++]);
		free(pipex->path);
	}
	while (pipex->cmds)
	{
		iter = 0;
		free(pipex->cmds->cmd);
		while (pipex->cmds->flags[iter])
			free(pipex->cmds->flags[iter++]);
		free(--(pipex->cmds->flags));
		tmp = pipex->cmds->next;
		free(pipex->cmds);
		pipex->cmds = tmp;
	}
	return (0);
}


// void	show_input(t_pipex *pipex)
// {
// 	size_t	i;
// 	t_cmds	*tmp;
// 	char	**tmpph;

// 	tmpph = pipex->path;
// 	i = 0;
// 	tmp = pipex->cmds;
// 	ft_printf("\n-=-=-=-= CORRECT INPUT -=-=-=-=\n");
// 	ft_printf("\n Numero de inputs: <%d> |", pipex->argc);
// 	ft_printf(" Input fd: <%d> |", pipex->inpfd);
// 	ft_printf(" Output fd: <%d>\n", pipex->outfd);
// 	ft_printf("\n~~~~~~~~ PATH ~~~~~~~~\n");
// 	ft_printf("\n");
// 	i = -1;
// 	while (tmpph[++i])
// 		ft_printf("PATH[%d]=%s\n", i, tmpph[i]);
// 	ft_printf("\n~~~~~~~ COMANDS AND FLAGS ~~~~~~~\n");
// 	i = 0;
// 	while (tmp)
// 	{
// 		ft_printf(" - CMD:\t%s\n", tmp->cmd);
// 		while (*(tmp->flags + i))
// 		{
// 			ft_printf("\tFlag %d:\t%s\n", i, *(tmp->flags + i));
// 			i++;
// 		}
// 		i = 0;
// 		tmp = tmp->next;
// 	}
// }
