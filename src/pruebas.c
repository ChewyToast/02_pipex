/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:57:28 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/10/26 22:46:46 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include "bmlib.h"

static int	para_el_hijo(char **argv, char **path);
static int	find_path(char **env);

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	**pather;

	(void)argv;
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
	i = fork();
	if (i < 0)
		exit (0);
	else if (i == 0)
	{
		i = para_el_hijo(argv, pather);
		if (i == -1)
			return (ft_printf("\nHIJO: Nos han jodido padre!\n"));
		else
			return (ft_printf("\nHIJO: Tenemos visto bueno papa!, el indice es: %d\n\n", i));
	}
	else
		ft_printf("\nPADRE: CONTESTAME PEQUE\n");
}

//	execve(argv[1], argv + 1, env);

static int	para_el_hijo(char **argv, char **pather)
{
	char	*tmp;
	char	*tmp2;
	int		j;
	int		i;

	i = 0;
	j = access(argv[1], X_OK);
	if (!j)
		return (1);
	else
	{
		tmp2 = ft_strjoin("/", argv[1]);
		while (j != 0 && pather[i])
		{
			tmp = ft_strjoin(pather[i++], tmp2);
			j = access(tmp, F_OK);
			free(tmp);
		}
		if (j == 0)
			return (i);
	}
	return (-1);
}

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
