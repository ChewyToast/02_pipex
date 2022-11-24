/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 20:49:46 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/24 05:46:20 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bmlib.h"

typedef struct s_sp	t_sp;
char	*ft_strchr(const char *s, int c);
ssize_t	parts_count(char *input);
int		parts_fill(char **cmd, char *input);
char	*clean_input(char *input);
int		error_free(char **cmd);

struct s_sp
{
	size_t	count;
	size_t	space;
	size_t	quote;
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
	// input = clean_input(input);
	if (!input)
		return (NULL);
	cmd = ft_calloc(sizeof(char *), counter + 20);
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
	sp->space = 0;
	sp->quote = 0;
	sp->parts = 0;
}


_Bool	its_space(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\r')
		return (1);
	return (0);
}

int	scaped(char *start)
{
	size_t	count;

	count = 0;
	while ((start - count) && *(start - count) == '\\')
		count--;
	return (count % 2);
}

int	its_quote(char *c)
{
	if (*c == '\'' && !scaped(c - 1))
	{
		// ft_printf("...........................its simple quote\n");
		return (1);
	}
	if (*c == '\"' && !scaped(c - 1))
	{
		// ft_printf("............................its double quote\n");
		return (1);
	}
	return (0);
}


/*
> Aqui ens encarregarem de crear tots els substrings segons les
> delimitacions comentades a la funció "parts_counts", a mes
> de tornarlos a netejar de '\'.
*/
int	parts_fill(char **cmd, char *input)
{
	char	quote;
	t_sp	sp;
	char	*tmp;
	char	*tmp2;

	init_sp(&sp);
	while (input[sp.count])
	{
		// ft_printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\nSTART=$%s$\n", input + sp.count);
		while (input[sp.space] && its_space(input[sp.space]))//	-------- 1.count spaces
			sp.space++;
		input += sp.space;
		if (input[sp.count] && !its_quote(input + sp.count))// ------ 2. is normal string
		{
			// ft_printf("normal: %c\n", input[sp.count]);
			while (input[sp.count] && !its_space(input[sp.count]) && !its_quote(input + sp.count))
			{
				// ft_printf("	inbucle normal::%s:\n", input + sp.count);
				sp.count++;
			}
			// ft_printf("	inbucle normal::%s:\n", input + sp.count);
		}
		else if (input[sp.count] && its_quote(input))// ------ 3. is quote string
		{
			// ft_printf("quote: %c\n", input[sp.count]);
			quote = input[sp.count];
			input++;
			while (input[sp.count] && (input[sp.count] != quote || (input[sp.count] == quote && !its_quote(input + sp.count))))
			{
				// ft_printf("	inbucle::%s: | quote: %c\n", input + sp.count, quote);
				sp.count++;
			}
			// ft_printf("	inbucle::%s: | quote: %c\n", input + sp.count, quote);
		}
		if (sp.count)// ------ hay algo que copiar
		{
			// ft_printf("\tSPACES: %d\n", sp.space);
			if (sp.space || (!sp.space && !sp.parts))// ------ en caso de haber espacios, nuevo string
			{
				*cmd = ft_substr(input, 0, sp.count);
				if (!*cmd)
				{
					// ft_printf("\n1 ERROR ERROR ERROR ERROR\n");
					// error_free(cmd);
					return (0);
				}
				// ft_printf("\n1>_%s_\n", *cmd);
				cmd++;
				sp.parts++;
			}
			else if (!sp.space && sp.parts)// ------ en caso de no haber espacios, juntamos con el anterior
			{
				tmp = *(cmd - 1);
				tmp2 = ft_substr(input, 0, sp.count);
				if (!tmp2)
				{
					// ft_printf("\n2 ERROR ERROR ERROR ERROR\n");
					// error_free(cmd);
					return (0);
				}
				*(cmd - 1) = ft_strjoin(tmp, tmp2);
				free(tmp);
				free(tmp2);
				if (!*(cmd - 1))
				{
					// ft_printf("\n3 ERROR ERROR ERROR ERROR\n");
					// error_free(cmd);
					return (0);
				}
				// ft_printf("\n2>_%s_\n", *(cmd - 1));
			}
		}
		if (input[sp.count] == 32)
			input += sp.count;
		else
			input += sp.count + 1;
		sp.space = 0;
		sp.count = 0;
		// ft_printf("\nEND:$%s$\n\n", input);
	}
	return (1);
}


	// while (input[sp.count])
	// {
	// 	while (input[sp.count] && input[sp.count] == 32)
	// 		sp.count++;
	// 	input += sp.count;
	// 	sp.count = 0;
	// 	if (input[sp.count] && input[sp.count] != 34 && input[sp.count] != 39)
	// 	{
	// 		while (input[sp.count] && (input[sp.count] != 32
	// 				&& input[sp.count] != '\f'
	// 				&& input[sp.count] != '\n' && input[sp.count] != '\r'
	// 				&& input[sp.count] != '\t' && input[sp.count] != '\v'))
	// 			sp.count++;
	// 		if (!sp.count)
	// 			break ;
	// 		// ft_printf("-----------------WORD\n");
	// 		*cmd = ft_substr(input, 0, sp.count);
	// 		ft_printf("\n<%s>\n", *cmd);
	// 		sp.parts++;
	// 		cmd++;
	// 		input += sp.count;
	// 		// ft_printf("ANA: <%s>\n", input);
	// 		sp.count = 0;
	// 	}
	// 	else if (input[sp.count] && input[sp.count] == 34)
	// 	{
	// 		input++;
	// 		while (input[sp.count] && (input[sp.count] != 34 || (input[sp.count] == 34 && input[sp.count - 1] == 92)))
	// 		{
	// 			// ft_printf("/input[sp]: %c/ | /input[sp - 1]: %c/\n", input[sp.count], input[sp.count - 1]);
	// 			sp.count++;
	// 		}
	// 		if (!sp.count)
	// 			break ;
	// 		// ft_printf("-----------------WORD\n");
	// 		*cmd = ft_substr(input, 0, sp.count);
	// 		ft_printf("\n<%s>\n", *cmd);
	// 		sp.parts++;
	// 		cmd++;
	// 		input += sp.count + 1;
	// 		// ft_printf("ANA: <%s>\n", input);
	// 		sp.count = 0;
	// 		// ft_printf("/OUTinput[sp]: %c/ | /input[sp - 1]: %c/\n", input[sp.count], input[sp.count - 1]);
	// 	}
	// 	else if (input[sp.count] && input[sp.count] == 39)
	// 	{
	// 		input++;
	// 		while (input[sp.count] && (input[sp.count] != 39 || (input[sp.count] == 39 && input[sp.count - 1] == 92)))
	// 			sp.count++;
	// 		if (!sp.count)
	// 			break ;
	// 		// ft_printf("-----------------WORD\n");
	// 		*cmd = ft_substr(input, 0, sp.count);
	// 		ft_printf("\n<%s>\n", *cmd);
	// 		sp.parts++;
	// 		cmd++;
	// 		input += sp.count + 1;
	// 		// ft_printf("ANA: <%s>\n", input);
	// 		sp.count = 0;
	// 	}
	// }
	// return (1);
// }

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
	char	quote;
	t_sp	sp;

	init_sp(&sp);
	while (input[sp.count])
	{
		while (input[sp.space] && its_space(input[sp.space]))//	-------- 1.count spaces
			sp.space++;
		input += sp.space;
		if (input[sp.count] && !its_quote(input + sp.count))// ------ 2. is normal string
			while (input[sp.count] && !its_space(input[sp.count]) && !its_quote(input + sp.count))
				sp.count++;
		else if (input[sp.count] && its_quote(input))// ------ 3. is quote string
		{
			quote = input[sp.count];
			input++;
			while (input[sp.count] && (input[sp.count] != quote || (input[sp.count] == quote && !its_quote(input + sp.count))))
				sp.count++;
		}
		if (sp.count)// ------ hay algo que copiar
		{
			if (sp.space || (!sp.space && !sp.parts))// ------ en caso de haber espacios, nuevo string
				sp.parts++;
		}
		if (input[sp.count] == 32)
			input += sp.count;
		else
			input += sp.count + 1;
		sp.space = 0;
		sp.count = 0;
	}
	return (sp.parts);
	// t_sp	sp;

	// init_sp(&sp);
	// while (input[sp.count])
	// {
	// 	while (input[sp.count] && (input[sp.count] == 32
	// 			|| input[sp.count] == '\f'
	// 			|| input[sp.count] == '\n' || input[sp.count] == '\r'
	// 			|| input[sp.count] == '\t' || input[sp.count] == '\v'))
	// 		sp.count++;
	// 	input += sp.count;
	// 	sp.count = 0;
	// 	if (input[sp.count] && (input[sp.count] != 34 && input[sp.count] != 39))
	// 	{
	// 		while (input[sp.count] && (input[sp.count] != 32
	// 				&& input[sp.count] != '\f'
	// 				&& input[sp.count] != '\n' && input[sp.count] != '\r'
	// 				&& input[sp.count] != '\t' && input[sp.count] != '\v'))
	// 			sp.count++;
	// 	}
	// 	else if (input[sp.count] && input[sp.count] == 34 && input[sp.count - 1] != 92)
	// 	{
	// 		input++;
	// 		while (input[sp.count] && (input[sp.count] != 34 || (input[sp.count] == 34 && input[sp.count - 1] == 92)))
	// 			sp.count++;
	// 	}
	// 	else if (input[sp.count] && input[sp.count] == 39 && input[sp.count - 1] != 92)
	// 	{
	// 		input++;
	// 		while (input[sp.count] && (input[sp.count] != 39 || (input[sp.count] == 39 && input[sp.count - 1] == 92)))
	// 			sp.count++;
	// 	}
	// 	if (!sp.count)
	// 		break ;
	// 	sp.parts++;
	// 	input += sp.count;
	// 	sp.count = 0;
	// }
	// return (sp.parts);
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
