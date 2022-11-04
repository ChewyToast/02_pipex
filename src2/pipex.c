/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:16:36 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/04 18:20:30 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"

static void	ft_init_pipex(int argc, t_pipex *pipex);
static int	ft_release_pipex(t_pipex *pipex);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	ft_init_pipex(argc, &pipex);
	if (!parse_input(argc, argv, env, &pipex))
		exit (ft_release_pipex(&pipex));
	ft_release_pipex(&pipex);
	exit (0);
	return (0);
}

static void	ft_init_pipex(int argc, t_pipex *pipex)
{
	pipex->inpfd = 0;
	pipex->outfd = 0;
	pipex->error = 1;
	pipex->argc = argc;
	pipex->path = NULL;
	pipex->cmds = NULL;
}

static int	ft_release_pipex(t_pipex *pipex)
{
	if (pipex->inpfd)
		close(pipex->inpfd);
	if (pipex->outfd)
		close(pipex->outfd);
	while (pipex->cmds)
	{
		if (pipex->cmds->cmd)
			free(pipex->cmds->cmd);
		pipex->cmds->cmd = NULL;
		while (*pipex->cmds->flags)
		{
			if (*(pipex->cmds->flags))
				free(*(pipex->cmds->flags));
			*(pipex->cmds->flags) = NULL;
			pipex->cmds->flags++;
		}
		pipex->cmds->flags = NULL;
		pipex->cmds = pipex->cmds->next;
	}
	if (pipex->cmds)
		free(pipex->cmds);
	pipex->cmds = NULL;
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
