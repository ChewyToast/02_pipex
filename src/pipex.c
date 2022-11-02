/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:51:51 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/02 19:47:04 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include "pipex_struct.h"
#include "bmlib.h"

void	show_input(t_pipex *pipex);

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
	close(pipex.inpfd);
	show_input(&pipex);
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
	ft_printf(" ~ Output fd: <%d> |", pipex->outfd);
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
