#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include "inc/bmlib/bmlib.h"

char	*ft_strchr(const char *s, int c);
ssize_t	parts_count(char *input);
int		parts_fill(char **cmd, char *input);
char	*clean_input(char *input);
void	print_string(char *str1, char **str);

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
	printf("\ncounter: %zu\n", counter);
	if (counter < 0)
		return (NULL); // ------- FALTA ERROR POR WRONG INPUT
	// input = clean_input(input);
	if (!input)
		return (NULL); // ------- FALTA ERROR
	cmd = ft_calloc(sizeof(char *), counter + 1);
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
	clean = calloc(sizeof(char), ft_strlen(input) + 1);
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

/*
> Aqui ens encarregarem de crear tots els substrings segons les delimitacions comentades
> a la funció "parts_counts", a mes de tornarlos a netejar de '\'.
*/
int	parts_fill(char **cmd, char *input)
{
	size_t	count;
	size_t	util;
	size_t	squote_count;
	size_t	dquote_count;

	count = 0;
	squote_count = 0;
	dquote_count = 0;
	while (input[count] && cmd)
	{
		util = 0;
		// ft_printf("\n------inp: <%c> | inp[count]: <%c> | sq: %d | dq: %d-------\n", *input, input[count], squote_count, dquote_count);
		if (input[count] == 32 && input[count + 1] != 32 && !squote_count && !dquote_count)
		{
			while (*(input + count - util) == 32)
				util++;
			*cmd = ft_substr(input, 0, count - util + 1);// --- substr para \' -> '
			// ft_printf("\n1CMD: <%s>, sq: %d, dq: %d\n", *cmd, squote_count, dquote_count);
			if (!*cmd)
				return (0);// --------- FALTA EL FREE_ALL
			input += count;
			cmd++;
			count = 0;
		}
		else if (input[count] == 39 && (!input[count - 1] || input[count - 1] != 92) && !squote_count && !dquote_count)// ---- Si es una cometa i s'ha d'obrir cometes
			squote_count = 1;
		else if (input[count] == 39 && (!input[count - 1] || input[count - 1] != 92) && squote_count && !dquote_count)// ---- Si es una cometa i s'ha de tancar
		{
			*cmd = ft_substr(input + 2, 0, count - 2);// --- substr para \' -> '
			// ft_printf("\n2CMD: <%s>\n", *cmd);
			if (!*cmd)
				return (0);// --------- FALTA EL FREE_ALL
			input += count;
			cmd++;
			squote_count = 0;
			count = 0;
		}
		else if (input[count] == 34 && (!input[count - 1] || input[count - 1] != 92) && !squote_count && !dquote_count)// ---- Si es una cometa i s'ha d'obrir cometes
			dquote_count = 1;
		else if (input[count] == 34 && (!input[count - 1] || input[count - 1] != 92) && dquote_count && !squote_count)// ---- Si es una cometa i s'ha de tancar
		{
			*cmd = ft_substr(input + 2, 0, count - 2);// --- substr para \' -> '
			// ft_printf("\n3CMD: <%s>\n", *cmd);
			if (!*cmd)
				return (0);// --------- FALTA EL FREE_ALL
			input += count;
			cmd++;
			dquote_count = 0;
			count = 0;
		}
		count++;
	}
	return (1);
}

/*
> Contam totes ses parts que hi haura, una part esta delimitada per: comencament de string,
> espai en blanc (si no esta entre cometes (simples i/o dobles), cometes simples, cometes dobles,
> i final de string).
> LA CONDICIO: && (!*(input - 1) || *(input - 1) != 92) es perque ens hem d'assegurar que no hi hagi
> un "\" abans de la cometa detectada ja que de ser aixi no l'hem de contar com a delimitador.
*/
ssize_t	parts_count(char *input)
{
	size_t	count;
	size_t	squote_count;
	size_t	dquote_count;

	count = 0;
	squote_count = 0;
	dquote_count = 0;
	while (*input)
	{
		if (*input == 32 && !squote_count && !dquote_count)// ---- Si es un espai i no hi ha cap cometa oberta
			count++;
		if (*input == 39 && (!*(input - 1) || *(input - 1) != 92) && !squote_count && !dquote_count)// ---- Si es una cometa i s'ha d'obrir cometes
			squote_count = 1;
		else if (*input == 39 && (!*(input - 1) || *(input - 1) != 92) && squote_count)// ---- Si es una cometa i s'ha de tancar
		{
			count++;
			squote_count = 0;
		}
		else if (*input == 34 && (!*(input - 1) || *(input - 1) != 92) && !squote_count && !dquote_count)// ---- Si es una cometa i s'ha d'obrir cometes
			dquote_count = 1;
		else if (*input == 34 && (!*(input - 1) || *(input - 1) != 92) && dquote_count)// ---- Si es una cometa i s'ha de tancar
		{
			count++;
			dquote_count = 0;
		}
		// printf("\n*inp= <%c>, cont: %zu, squote_count: %zu, dquote_count: %zu\n",*input, count, squote_count, dquote_count);
		input++;
	}
	if (squote_count || dquote_count)
		return (-1);
	return (count);
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

void	print_string(char *str1, char **str)
{
	write(1, "\nsingle: <", 10);
	write(1, str1, ft_strlen(str1));
	write(1, ">\n cmd:\n", 8);
	while (*str)
	{
		write(1, "\t<", 2);
		if (*str)
			write(1, *str, ft_strlen(*str));
		else
			write(1, "NULL", 4);
		write(1, ">\n", 2);
		str++;
	}
}
