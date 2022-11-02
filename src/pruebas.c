/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:57:28 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/03 00:56:47 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "bmlib.h"

// int	main(void)
// {
// 	int	fd;

// 	fd = open("prueba", O_RDWR);
// 	if (!fork())
// 	{
// 		ft_printf("\nHIJO FD VALUE: %d\n", fd);
// 		close(0);
// 		close(fd);
// 		if (read(fd, NULL, 0) == -1)
// 			return (ft_printf("\nSOY EL HIJO Y ESTA CERRADO\n"));
// 		else
// 			return (ft_printf("\nSOY EL HIJO Y ESTA ABIERTO\n"));
// 	}
// 	else
// 	{
// 		ft_printf("\nPADRE FD VALUE: %d\n", fd);
// 		close(0);
// 		usleep(500);
// 		if (read(fd, NULL, 0) == -1)
// 			return (ft_printf("\nSOY EL PADRE Y ESTA CERRADO\n"));
// 		else
// 		{
// 			dup2(fd, 1);
// 			close(1);
// 			return (ft_printf("\nSOY EL PADRE Y ESTA ABIERTO\n"));
// 		}
// 	}
// }

// static int	para_el_hijo(char **argv, char **path);
// static int	find_path(char **env);
// static int	ejecutalo_hijo(char *com, char **argv, char **env, int *pipes);

// int	main(int argc, char **argv, char **env)
// {
// 	int		i;
// 	char	**pather;
// 	int		*pipes;
// 	int	fd;
// 	char	*tmp;

// 	(void)argv;
// 	fd = open("prueba", O_RDWR);
// 	if (fd == -1)
// 		return (ft_printf("\nERROR DE OPEN\n"));
// 	if (argc < 2)
// 		return (write(2, "INPUT?\n", 7));
// 	pipes = malloc(sizeof(int) * 2);
// 	if (pipe(pipes) == -1)//- - - - - - - - - - - - -- - - Creamos pipe
// 		exit (write(2, "ERROR AL CREAR PIPES\n", 21));
// 	else
// 		ft_printf("\nPipe creado, puente entre: %d y %d\n", pipes[0], pipes[1]);
// 	i = find_path(env);
// 	pather = ft_split(env[i] + 5, ':');
// 	close(0);
// 	dup2(1, pipes[1]);
// 	close(pipes[1]);
// 	i = fork();//- - - - - - - - - - - - - Hacemos fork
// 	if (i < 0)
// 		exit (0);
// 	else if (i == 0)
// 	{
// 		ft_printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CHILDREN\n\n");
// 		i = para_el_hijo(argv, pather);
// 		if (i == -1)
// 			exit (ft_printf("\nCHILLDREN: daddy we are fucked up\n"));
// 		else if (i == -2)
// 			ejecutalo_hijo(argv[1], argv + 1, env, pipes);//- -- - -"Dup2"
// 		else
// 		{
// 			tmp = ft_strjoin("/", argv[1]);
// 			if (!ejecutalo_hijo(ft_strjoin(pather[i - 1], tmp), argv + 1,
							//env, pipes))
// 				exit (write(2, "ERROR AL EJECUTAR\n", 18));
// 		}
// 	}
// 	wait(&i);
// 	ft_printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END CHILD\n");
// 	ft_printf("\nPADRE: Ya termine de esperar\n");
// 	ft_printf("\nAbrimos archivo y hacemos dup2(%d, %d)\n", 1, pipes[1]);
// 	free(pipes);
// 	ft_printf("\nSE FINI LE PIPEEEEX LU FRANCEEE\n");
// 	exit (0);
// }

// //	execve(argv[1], argv + 1, env);

// static int	ejecutalo_hijo(char *com, char **argv, char **env, int *pipes)
// {
// 	int	i;

// 	i = 0;
// 	ft_printf("CHILLDREN: Running execve, %s\n", com);
// 	while (argv[i])
// 	{
// //		ft_printf("\nARGV[%d]: %s\n", i, argv[i]);
// 		i++;
// 	}
// 	ft_printf("\nHacemos dup2(%d, %d)\n", pipes[0], 1);
// 	ft_printf("\nRESULTADO DE %s: ", com);
// 	close(pipes[1]);
// 	close(1);
// 	dup2(pipes[0], 1);
// 	close(pipes[0]);
// //	ft_printf("\nRESULTADO DE %s:\n", com);
// 	execve(com, argv, env);
// 	return (0);
// }

// static int	para_el_hijo(char **argv, char **pather)
// {
// 	char	*tmp;
// 	char	*tmp2;
// 	int		j;
// 	int		i;

// 	i = 0;
// 	j = access(argv[1], X_OK);
// //	ft_printf("try with:<%s>\n", argv[1]);
// 	if (!j)
// 		return (1);
// 	else
// 	{
// 		tmp2 = ft_strjoin("/", argv[1]);
// 		while (pather[i])
// 		{
// 			tmp = ft_strjoin(pather[i++], tmp2);
// 			j = access(tmp, X_OK);
// //			ft_printf("try with:<%s>\n", tmp);
// 			free(tmp);
// 			if (j == 0)
// 				return (i);
// 		}
// 	}
// 	return (-1);
// }

// static int	find_path(char **env)
// {
// 	char	path[] = "PATH=\0";
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (env[i])
// 	{
// 		j = 0;
// 		while (env[i][j] == path[j] && path[j])
// 			j++;
// 		if (path[j] == '\0')
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }
