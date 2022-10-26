/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:57:28 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/10/26 22:30:02 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "bmlib.h"

static int	find_path(char **env);

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		j;
	char	**pather;
	char	*tmp;
	char	*tmp2;

	(void)argv;
	j = 0;
	if (argc < 2)
		return (write(1, "INPUT?\n", 7));
	i = find_path(env);
	if (!i)
		return (write(1, "PATH?\n", 7));
	else
		ft_printf("PATH pos: %d and sting: %s\n", i, env[i]);
	pather = ft_split(env[i] + 5, ':');
	i = 0;
	while (pather[i])
		ft_printf("String PATH: %s\n", pather[i++]);
	i = 0;
	j = access(argv[1], X_OK);
	if (!j)
		exit(0);
	else
	{
		tmp2 = ft_strjoin("/", argv[1]);
		ft_printf("\nentro en el bucle\n");
		while (j != 0 && pather[i])
		{
			tmp = ft_strjoin(pather[i++], tmp2);
			ft_printf("dentro, string: %s\n", tmp);
			j = access(tmp, F_OK);
			free(tmp);
		}
	}
	exit (0);
}

//	execve(argv[1], argv + 1, env);

static int	find_path(char **env)
{
	char	path[] = "PATH=\0";
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] == path[j] && path[j])
			j++;
		if (path[j] == '\0')
			return (i);
		i++;
	}
	return (0);
}
