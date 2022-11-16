/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:49:46 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/15 21:51:50 by bmoll-pe         ###   ########.fr       */
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
> Comencarem pero anar a veure quantes parts em de fer per saber quants de substrings
> tindra la string de strings "cmd", despres haurem de fer neteja de imput treient totes
> les '\' que trobem, (si n'hi ha dues de seguides s'ha de deixar en una). Per despres
> cridar a la funció que creara tots els substrings.
*/
char	**ft_cmd_split(char *input)
{
	char 	**cmd;
	ssize_t	counter;

	counter = parts_count(input);
	if (counter < 0)
		return (NULL); // ------- FALTA ERROR POR WRONG INPUT
	input = clean_input(input);
	if (!input)
		return (NULL); // ------- FALTA ERROR
	cmd = ft_calloc(sizeof(char *), counter + 2);
	if (!cmd)
		return (NULL); // ------- FALTA ERROR
	if (!parts_fill(cmd, input))
		return (NULL); // ------- FALTA ERROR
	return (cmd);
}

/*
> Com s'ha comentat a la funció desde la qual es cridada aquesta, aquí ens encarregarem
> de fer "net", treure tots els caracters '\', menys en el cas de '\\"\' que ha de quedar:
> '\'.
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
> Aqui ens encarregarem de crear tots els substrings segons les delimitacions comentades
> a la funció "parts_counts", a mes de tornarlos a netejar de '\'.
*/

int	parts_fill(char **cmd, char *input)
{
	t_sp	sp;

	init_sp(&sp);
	while(input[sp.count])
	{
		// ft_printf("\n~~ START char: <%c>\n", input[sp.count]);
		while (input[sp.count] && input[sp.count] == 32)
			sp.count++;
		input += sp.count;
		sp.count = 0;
		// ft_printf("~~ IN char: <%c>\n", input[sp.count]);
		if (input[sp.count] && input[sp.count] != 34 && input[sp.count] != 39)
		{
			while (input[sp.count] && (input[sp.count] != 32 && input[sp.count] != '\f'
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
		// ft_printf("~~ OUT char: <%c>\n", input[sp.count]);
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

// int	parts_fill(char **cmd, char *input)
// {
// 	t_sp	sp;

// 	init_sp(&sp);
// 	while(input[sp.count])
// 	{
// 		while (input[sp.count] && (input[sp.count] == 32 || input[sp.count] == '\f'
// 			|| input[sp.count] == '\n' || input[sp.count] == '\r'
// 			|| input[sp.count] == '\t' || input[sp.count] == '\v'))
// 			sp.count++;
// 		input += sp.count;
// 		sp.count = 0;
// 		if (input[sp.count])
// 		{
// 			if (input[sp.count] == 39)
// 				sp.squot = 1;
// 			else if (input[sp.count] == 34)
// 				sp.dquot = 1;
// 			if (sp.dquot || sp.squot)
// 			{
// 				while ((input[sp.count] == 39 && sp.squot && input[sp.count - 1] != 92)
// 					|| (input[sp.count] == 34 && sp.dquot && input[sp.count - 1] != 92))
// 					sp.count++;
// 				sp.dquot = 0;
// 				sp.squot = 0;
// 			}
// 			else
// 				while (input[sp.count] && (input[sp.count] != 32 && input[sp.count] != '\f'
// 					&& input[sp.count] != '\n' && input[sp.count] =!= '\r'
// 					&& input[sp.count] != '\t' && input[sp.count] != '\v'))
// 				sp.count++;
// 			*cmd = ft_substr(input, 0, sp.count);
// 			ft_printf("*cmd:\t<%s>", *cmd);
// 			cmd++;
// 		}
// 	}
// }
// int	parts_fill(char **cmd, char *input)
// {
// 	size_t	util;
// 	size_t	count;
// 	size_t	squote_count;
// 	size_t	dquote_count;

// 	count = 0;
// 	squote_count = 0;
// 	dquote_count = 0;
// 	// ft_printf("\nENTRO\n");
// 	// ft_printf("INPUT:<%s>", input);
// 	while (input[count] && cmd)
// 	{
// 		util = 0;
// 		// if (*(cmd - 1))
// 		// 	ft_printf("\n------inp: <%c> | inp[count]: <%c> | sq: %d | dq: %d-------\n", *input, input[count], squote_count, dquote_count);
// 		if (input[count] == 32 && input[count + 1] != 32 && !squote_count && !dquote_count)
// 		{
// 			if (input[count - 1] == 32)
// 			{
// 				while (*(input + count - util) == 32)
// 					util++;
// 				*cmd = ft_substr(input, 0, count - util + 1);// --- substr para \' -> '
// 			}
// 			else
// 				*cmd = ft_substr(input, 0, count);// --- substr para \' -> '
// 			// *cmd = ft_substr(input, 0, count - 2);// --- substr para \' -> '
// 			// ft_printf("\n1CMD: <%s>, sq: %d, dq: %d\n", *cmd, squote_count, dquote_count);
// 			if (!*cmd)
// 				return (0);// --------- FALTA EL FREE_ALL
// 			input += count;
// 			cmd++;
// 			count = 0;
// 		}
// 		else if (input[count] == 39 && (!input[count - 1] || input[count - 1] != 92) && !squote_count && !dquote_count)// ---- Si es una cometa i s'ha d'obrir cometes
// 			squote_count = 1;
// 		else if (input[count] == 39 && (!input[count - 1] || input[count - 1] != 92) && squote_count && !dquote_count)// ---- Si es una cometa i s'ha de tancar
// 		{
// 			*cmd = ft_substr(input + 2, 0, count - 2);// --- substr para \' -> '
// 			// ft_printf("\n2CMD: <%s>\n", *cmd);
// 			if (!*cmd)
// 				return (0);// --------- FALTA EL FREE_ALL
// 			input += count;
// 			cmd++;
// 			squote_count = 0;
// 			count = 0;
// 		}
// 		else if (input[count] == 34 && (!input[count - 1] || input[count - 1] != 92) && !squote_count && !dquote_count)// ---- Si es una cometa i s'ha d'obrir cometes
// 			dquote_count = 1;
// 		else if (input[count] == 34 && (!input[count - 1] || input[count - 1] != 92) && dquote_count && !squote_count)// ---- Si es una cometa i s'ha de tancar
// 		{
// 			*cmd = ft_substr(input + 2, 0, count - 2);// --- substr para \' -> '
// 			// ft_printf("\n3CMD: <%s>\n", *cmd);
// 			if (!*cmd)
// 				return (0);// --------- FALTA EL FREE_ALL
// 			input += count;
// 			cmd++;
// 			dquote_count = 0;
// 			count = 0;
// 		}
// 		count++;
// 	}
// 	if (!*(cmd - 1))
// 		*cmd = ft_substr(input, 0, count);// --- substr para \' -> '
// 	else if (*(cmd - 1) && *input == 32)
// 		*cmd = ft_substr(input + 1, 0, count);// --- substr para \' -> '
// 	// ft_printf("\nEND_CMD: <%s>\n", *cmd);
// 	return (1);
// }

/*
> Contam totes ses parts que hi haura, una part esta delimitada per: comencament de string,
> espai en blanc (si no esta entre cometes (simples i/o dobles), cometes simples, cometes dobles,
> i final de string).
> LA CONDICIO: && (!*(input - 1) || *(input - 1) != 92) es perque ens hem d'assegurar que no hi hagi
> un "\" abans de la cometa detectada ja que de ser aixi no l'hem de contar com a delimitador.
*/

ssize_t	parts_count(char *input)
{
	t_sp	sp;
	
	init_sp(&sp);
	while(input[sp.count])
	{
		while (input[sp.count] && (input[sp.count] == 32 || input[sp.count] == '\f'
				|| input[sp.count] == '\n' || input[sp.count] == '\r'
				|| input[sp.count] == '\t' || input[sp.count] == '\v'))
			sp.count++;
		input += sp.count;
		sp.count = 0;
		if (input[sp.count] && (input[sp.count] != 34 && input[sp.count] != 39))
		{
			while (input[sp.count] && (input[sp.count] != 32 && input[sp.count] != '\f'
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
// ssize_t	parts_count(char *input)
// {
// 	size_t	count;
// 	size_t	squote_count;
// 	size_t	dquote_count;

// 	count = 0;
// 	squote_count = 0;
// 	dquote_count = 0;
// 	while (*input)
// 	{
// 		if (*input == 32 && !squote_count && !dquote_count)// ---- Si es un espai i no hi ha cap cometa oberta
// 			count++;
// 		if (*input == 39 && (!*(input - 1) || *(input - 1) != 92) && !squote_count && !dquote_count)// ---- Si es una cometa i s'ha d'obrir cometes
// 			squote_count = 1;
// 		else if (*input == 39 && (!*(input - 1) || *(input - 1) != 92) && squote_count)// ---- Si es una cometa i s'ha de tancar
// 		{
// 			count++;
// 			squote_count = 0;
// 		}
// 		else if (*input == 34 && (!*(input - 1) || *(input - 1) != 92) && !squote_count && !dquote_count)// ---- Si es una cometa i s'ha d'obrir cometes
// 			dquote_count = 1;
// 		else if (*input == 34 && (!*(input - 1) || *(input - 1) != 92) && dquote_count)// ---- Si es una cometa i s'ha de tancar
// 		{
// 			count++;
// 			dquote_count = 0;
// 		}
// 		// printf("\n*inp= <%c>, cont: %zu, squote_count: %zu, dquote_count: %zu\n",*input, count, squote_count, dquote_count);
// 		input++;
// 	}
// 	if (squote_count || dquote_count)
// 		return (-1);
// 	return (count);
// }

int	error_free(char **cmd)
{
	size_t	iter;
	
	iter = 0;
	while (cmd[iter])
		free(cmd[iter++]);
	free(cmd);
	return (0);
}
