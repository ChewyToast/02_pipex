/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:00:18 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/29 03:41:03 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex_struct_bonus.h"

# include "bmlib.h"

//	--------utils1.c
int			init_pipex(int argc, char **argv, char **env, t_pipex *pip);
void		startup_fds(t_pipex *pip);
int			here_doc(t_pipex *pip);
int			clean_exit(t_pipex *pip, int ret);
int			error_msg(char *first, char *second, char *thrd, int ret);

//	--------utils2.c
void		get_path(t_pipex *pip, char *path_compare);
int			check_file(char *file, int mode, t_pipex *pip);
void		check_cmd(t_pipex *pip, t_cmds *cmd);
void		extra_loop(t_pipex *pip, int *pipes);

//	--------ft_cmd_split.c
typedef struct s_split
{
	int	start;
	int	end;
	int	num_words;
	int	i;
}	t_split;

typedef struct s_clean
{
	int		num_c;
	int		len;
	int		j;
	char	*new_str;
}	t_clean;

char		**ft_split_args(char const *s, char c);
char		*ft_simple_quotes_two(char const *s, t_split *spt);
char		*ft_double_quotes_two(char const *s, t_split *spt);
char		*ft_clean_char(char *str, char c, int i);
char		*ft_simple_quotes(char const *s, t_split *spt);
char		*ft_double_quotes(char const *s, t_split *spt);
char		*ft_word(char const *s, t_split *spt, char c);

#endif