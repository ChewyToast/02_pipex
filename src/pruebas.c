/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:57:28 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/10/27 17:30:15 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "bmlib.h"

static int	para_el_hijo(char **argv, char **path);
static int	find_path(char **env);
static int	ejecutalo_hijo(char *com, char **argv, char **env, int *pipes);

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	**pather;
	int		*pipes;
	char	*tmp;

	(void)argv;
	if (argc < 2)
		return (write(2, "INPUT?\n", 7));
	pipes = malloc(sizeof(int) * 2);
	ft_printf("\n----------------------------------------------------\n");
	if (pipe(pipes) == -1)
		exit (write(2, "ERROR AL CREAR PIPES\n", 21));
	else
		ft_printf("Pipe creado, puente entre: %d y %d\n", pipes[0], pipes[1]);
	ft_printf("\n----------------------------------------------------\n");
	i = find_path(env);
	if (!i)
		exit (write(1, "PATH?\n", 7));
	else
		ft_printf("\nPATH pos: %d and sting: %s\n", i, env[i]);
	ft_printf("\n----------------------------------------------------\n");
	pather = ft_split(env[i] + 5, ':');
	i = 0;
	while (pather[i])
		ft_printf("String PATH: %s\n", pather[i++]);
	ft_printf("\n----------------------------------------------------\n");
	i = fork();
	if (i < 0)
		exit (0);
	else if (i == 0)
	{
		ft_printf("\n----------------------------------------------------\n");
		i = para_el_hijo(argv, pather);
		ft_printf("\n----------------------------------------------------\n");
		if (i == -1)
			exit (ft_printf("\nCHILLDREN: daddy we are fucked up\n"));
		else if (i == -2)
		{
			ft_printf("\nCHILLDREN: daddy we got it!, whithout nothing\n\n", i);
			ejecutalo_hijo(argv[1], argv + 1, env, pipes);
		}
		else
		{
			ft_printf("\nCHILLDREN: daddy we got it!, its the num: %d\n\n", i);
			tmp = ft_strjoin("/", argv[1]);
			ft_printf("tmp<%s>\n", tmp);
			if (!ejecutalo_hijo(ft_strjoin(pather[i - 1], tmp), argv + 1, env, pipes))
				exit (write(2, "ERROR AL EJECUTAR\n", 18));
		}
	}
	else
	{
		ft_printf("\nPADRE: Where the fuck u are little monkey?\n");
		wait(&i);
		ft_printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		ft_printf("\nPADRE: Ya termine de esperar\n");
	}
	dup2(open("prueba", O_RDWR), pipes[1]);
	free(pipes);
	exit (0);
}

//	execve(argv[1], argv + 1, env);

static int	ejecutalo_hijo(char *com, char **argv, char **env, int *pipes)
{
	int	i;

	i = 0;
	ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	ft_printf("CHILLDREN: Running execve, %s\n", com);
	while (argv[i])
	{
		ft_printf("\nARGV[%d]: %s\n", i, argv[i]);
		i++;
	}
	dup2(1, pipes[0]);
	if (execve(com, argv, env) == -1)
		return (0);
	return (1);
}

static int	para_el_hijo(char **argv, char **pather)
{
	char	*tmp;
	char	*tmp2;
	int		j;
	int		i;

	i = 0;
	j = access(argv[1], X_OK);
	ft_printf("try with:<%s>\n", argv[1]);
	if (!j)
		return (1);
	else
	{
		tmp2 = ft_strjoin("/", argv[1]);
		while (pather[i])
		{
			tmp = ft_strjoin(pather[i++], tmp2);
			j = access(tmp, X_OK);
			ft_printf("try with:<%s>\n", tmp);
			free(tmp);
			if (j == 0)
				return (i);
		}
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
