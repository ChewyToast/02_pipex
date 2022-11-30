/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:55:19 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/30 17:53:12 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bmlib.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pip;
	pid_t	pid;

	if (argc != 5)
		exit (error_msg(NULL, "bash", INA, 1));
	if (!init_pipex(argc, argv, env, &pip))
		exit(error_msg(NULL, "bash", MKO, 1));
	if (pipe(pip.utils->pipes) < 0)
		exit (error_msg(NULL, "bash", ECP, clean_exit(&pip, 1)));
	pid = fork();
	if (pid < 0)
		exit (error_msg(NULL, "bash", ECF, clean_exit(&pip, 1)));
	else if (!pid)
		first_part(&pip);
	if (dup2(pip.utils->pipes[0], 0) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(&pip, 1)));
	close(pip.utils->pipes[1]);
	close(pip.utils->pipes[0]);
	second_part(&pip);
	return (0);
}

void	first_part(t_pipex *pip)
{
	get_path(pip, "PATH=");
	check_file(*(pip->inputs->argv + 1), R_OK, pip);
	pip->cmds = malloc(sizeof(t_cmds));
	if (!pip->cmds)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	check_cmd(pip, pip->cmds);
	pip->inputs->inpfd = open(*(pip->inputs->argv + 1), O_RDONLY);
	if (pip->inputs->inpfd < 0)
	{
		error_msg(BSH, *(pip->inputs->argv + 1), CNO, 1);
		exit (clean_exit(pip, 1));
	}
	if (dup2(pip->inputs->inpfd, 0) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
	if (dup2(pip->utils->pipes[1], 1) < 0)
		exit (error_msg(BSH, "dup2", BFD, clean_exit(pip, 1)));
	close(pip->inputs->inpfd);
	close(pip->utils->pipes[0]);
	close(pip->utils->pipes[1]);
	execve(pip->cmds->path_comand, pip->cmds->cmd, pip->inputs->env);
	clean_exit(pip, 1);
	perror(NULL);
	exit (1);
}

void	second_part(t_pipex *pip)
{
	get_path(pip, "PATH=");
	check_file(*(pip->inputs->argv + (pip->inputs->argc - 1)), W_OK, pip);
	pip->inputs->argv += pip->inputs->argc - 4;
	pip->inputs->outfd = open(*(pip->inputs->argv + 3),
			O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (pip->inputs->inpfd < 0)
	{
		error_msg(BSH, *(pip->inputs->argv + 3), CNO, 1);
		exit (clean_exit(pip, 1));
	}
	pip->cmds = malloc(sizeof(t_cmds));
	if (!pip->cmds)
		exit (error_msg(NULL, "bash", MKO, clean_exit(pip, 1)));
	check_cmd(pip, pip->cmds);
	if (dup2(pip->inputs->outfd, 1) < 0)
		exit (error_msg(BSH, "2", BFD, clean_exit(pip, 1)));
	if (!pip->utils->error)
		execve(pip->cmds->path_comand, pip->cmds->cmd, pip->inputs->env);
	exit (clean_exit(pip, 1));
}

// int	main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// 	char	**rtrn;
// 	char	command[] = "  ""script space.sh\"";
	// char	command[] = "  echo "" \\\\\\\\\\\"holaquetal\"dentrocomillas\"";
	// char	command[] = "  awk \'\"\'\"\'{count++} END \\\\\'{printcount}\'\"\'\"\'";
	// char	commandd[] = "awk \"{count++} END {printf \\\"count:%i\\\" , count}\"";
	// char	commanddd[] = "sed    \"s/And/But/\"";
	// char	commandddd[] = "./\"script space.sh\"";
	// char	commanddddd[] = "echo \"s\"\"b\"";
	// char	commanddddd[] = "./\'\"\'\"\'script space.sh\'\"\'\"\'";
	// ft_printf("\n###########################################\n\n-----INPUT:<%s>\n\n", command);
	// rtrn = ft_cmd_split(command);
	// while(*rtrn)
	// 	ft_printf("RESULT[$]%s[$]\n", *(rtrn++));
	// execle("/usr/bin/awk", "\"\'{count++} END {print count}\'\"", NULL, env);
	// ft_printf("\n###########################################\n------INPUT:<%s>\n\n", commandd);
	// rtrn = ft_cmd_split(commandd);
	// while(*rtrn)
	// 	ft_printf("RESULT[$]%s[$]\n", *(rtrn++));
	// ft_printf("\n###########################################\n------INPUT:<%s>\n\n", commanddd);
	// rtrn = ft_cmd_split(commanddd);
	// while(*rtrn)
	// 	ft_printf("RESULT[$]%s[$]\n", *(rtrn++));
	// ft_printf("\n###########################################\n------INPUT:<%s>\n\n", commandddd);
	// rtrn = ft_cmd_split(commandddd);
	// while(*rtrn)
	// 	ft_printf("RESULT[$]%s[$]\n", *(rtrn++));
	// ft_printf("\n###########################################\n------INPUT:<%s>\n\n", commanddddd);
	// rtrn = ft_cmd_split(commanddddd);
	// while(*rtrn)
	// 	ft_printf("RESULT[$]%s[$]\n", *(rtrn++));
	// // execle("/usr/bin/awk", "awk", "\"", "\'{count++} END \\\\\'{printcount}\'", "\"", NULL, env);
	// // execve("/usr/bin/awk", ft_split_args(commanddddd, 32), env);
	// // execve("/usr/bin/echo", ft_split_args(commanddddd, 32), env);
	// // execve("/bin/echo", ft_cmd_split(commanddddd), env);
	// ft_printf("\n###########################################\n");
// }
