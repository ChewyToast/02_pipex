/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:51:51 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/03 00:53:56 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "bmlib.h"

static void	ft_init_pipex(int argc, t_pipex *pipex);
static int	ft_release_pipex(t_pipex *pipex);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	ft_init_pipex(argc, &pipex);
	if (!parse_input(argc, argv, env, &pipex))
		return (ft_release_pipex(&pipex));
	show_input(&pipex);
	return (0);
}

static void	ft_init_pipex(int argc, t_pipex *pipex)
{
	pipex->inpfd = 0;
	pipex->outfd = 0;
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
	if (pipex->path)
	{
		while (*pipex->path)
			free(*(pipex->path++));
		free(pipex->path);
	}
	while (pipex->cmds)
	{
		if (pipex->cmds->cmd)
			free(pipex->cmds->cmd);
		while (pipex->cmds->flags)
			if (*(pipex->cmds->flags))
				free(*(pipex->cmds->flags++));
		free(pipex->cmds->flags);
		pipex->cmds = pipex->cmds->next;
	}
	return (0);
}

void	show_input(t_pipex *pipex)
{
	size_t	i;
	t_cmds	*tmp;

	i = 0;
	tmp = pipex->cmds;
	ft_printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	ft_printf("\n ~ Numero de inputs: <%d> |", pipex->argc);
	ft_printf(" ~ Input fd: <%d> |", pipex->inpfd);
	ft_printf(" ~ Output fd: <%d>", pipex->outfd);
	ft_printf("\n\n~~~~~~~~~~~ COMANDS AND FLAGS ~~~~~~~~~~~\n\n");
	while (tmp)
	{
		ft_printf(" - CMD:\t%s\n", tmp->cmd);
		while (*(tmp->flags + i))
		{
			ft_printf("\tFlag %d:\t%s\n", i, *(tmp->flags + i));
			i++;
		}
		i = 0;
		tmp = tmp->next;
	}
}
