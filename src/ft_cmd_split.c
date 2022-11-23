/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomoll <brunomoll@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:49:46 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/20 02:07:32 by brunomoll        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bmlib.h"

typedef struct s_sp	t_sp;
char	*ft_strchr(const char *s, int c);
ssize_t	parts_count(char *input);
int		parts_fill(char **cmd, char *input);
char	*clean_input(char *input);

struct s_sp
{
	size_t	dquot;
	size_t	squot;
	size_t	count;
	size_t	parts;
};

/*
> Comencarem pero anar a veure quantes parts em de fer per saber quants de 
> substrings tindra la string de strings "cmd", despres haurem de fer
>neteja de imput treient totes les '\' que trobem, (si n'hi ha dues de
> seguides s'ha de deixar en una). Per despres cridar a la funció que creara
> tots els substrings.
*/
char	**ft_cmd_split(char *input)
{
	char	**cmd;
	ssize_t	counter;

	counter = parts_count(input);
	if (counter < 0)
		return (NULL);
	input = clean_input(input);
	if (!input)
		return (NULL);
	cmd = ft_calloc(sizeof(char *), counter + 2);
	if (!cmd)
		return (NULL);
	if (!parts_fill(cmd, input))
		return (NULL);
	return (cmd);
}

/*
> Com s'ha comentat a la funció desde la qual es cridada aquesta, aquí
> ens encarregarem de fer "net", treure tots els caracters '\', menys
> en el cas de '\\"\' que ha de quedar: '\'.
*/
char	*clean_input(char *input)
{
	size_t	iter;
	char	*clean;

	iter = 0;
	clean = ft_calloc(sizeof(char), ft_strlen(input) + 1);
	if (!clean)
		return (NULL);
	while (*input)
	{
		if (*input == 92)
			input++;
		clean[iter++] = *input;
		input++;
	}
	clean[iter] = '\0';
	return (clean);
}

static void	init_sp(t_sp *sp)
{
	sp->count = 0;
	sp->squot = 0;
	sp->dquot = 0;
	sp->parts = 0;
}

/*
> Aqui ens encarregarem de crear tots els substrings segons les
> delimitacions comentades a la funció "parts_counts", a mes
> de tornarlos a netejar de '\'.
*/

int	parts_fill(char **cmd, char *input)
{
	t_sp	sp;

	init_sp(&sp);
	while (input[sp.count])
	{
		while (input[sp.count] && input[sp.count] == 32)
			sp.count++;
		input += sp.count;
		sp.count = 0;
		if (input[sp.count] && input[sp.count] != 34 && input[sp.count] != 39)
		{
			while (input[sp.count] && (input[sp.count] != 32
					&& input[sp.count] != '\f'
					&& input[sp.count] != '\n' && input[sp.count] != '\r'
					&& input[sp.count] != '\t' && input[sp.count] != '\v'))
				sp.count++;
		}
		else if (input[sp.count] && input[sp.count] == 34)
		{
			input++;
			while (input[sp.count] && input[sp.count] != 34)
				sp.count++;
		}
		else if (input[sp.count] && input[sp.count] == 39)
		{
			input++;
			while (input[sp.count] && input[sp.count] != 39)
				sp.count++;
		}
		if (!sp.count)
			break ;
		*cmd = ft_substr(input, 0, sp.count);
		sp.parts++;
		cmd++;
		input += sp.count;
		sp.count = 0;
	}
	return (1);
}

/*
> Contam totes ses parts que hi haura, una part esta delimitada per:
> comencament de string, espai en blanc (si no esta entre cometes
> (simples i/o dobles), cometes simples, cometes dobles, i final de string).
> LA CONDICIO: && (!*(input - 1) || *(input - 1) != 92) es perque ens hem
> d'assegurar que no hi hagi un "\" abans de la cometa detectada ja que de
> ser aixi no l'hem de contar com a delimitador.
*/

ssize_t	parts_count(char *input)
{
	t_sp	sp;

	init_sp(&sp);
	while (input[sp.count])
	{
		while (input[sp.count] && (input[sp.count] == 32
				|| input[sp.count] == '\f'
				|| input[sp.count] == '\n' || input[sp.count] == '\r'
				|| input[sp.count] == '\t' || input[sp.count] == '\v'))
			sp.count++;
		input += sp.count;
		sp.count = 0;
		if (input[sp.count] && (input[sp.count] != 34 && input[sp.count] != 39))
		{
			while (input[sp.count] && (input[sp.count] != 32
					&& input[sp.count] != '\f'
					&& input[sp.count] != '\n' && input[sp.count] != '\r'
					&& input[sp.count] != '\t' && input[sp.count] != '\v'))
				sp.count++;
		}
		else if (input[sp.count] && input[sp.count] == 34)
		{
			input++;
			while (input[sp.count] && input[sp.count] != 34)
				sp.count++;
		}
		else if (input[sp.count] && input[sp.count] == 39)
		{
			input++;
			while (input[sp.count] && input[sp.count] != 39)
				sp.count++;
		}
		if (!sp.count)
			break ;
		sp.parts++;
		input += sp.count;
		sp.count = 0;
	}
	return (sp.parts);
}

int	error_free(char **cmd)
{
	size_t	iter;

	iter = 0;
	while (cmd[iter])
		free(cmd[iter++]);
	free(cmd);
	return (0);
}
