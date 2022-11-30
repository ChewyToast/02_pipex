/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:37:56 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/30 16:24:23 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"

// # include <stdlib.h>

// # include <unistd.h>

// # include <stdio.h>

// # include <fcntl.h>

// # include <sys/wait.h>

// int	ft_strlen(const char *s);
// int	ft_isspace(int argv);
size_t	count_parts(char *input, size_t rtrn);
_Bool	fill_parts(char *input, char **rtrn);
int	ft_isscaped(char *str);
int	ft_isquote(char *str, char quote);
char	*smart_fill(char *input, char delim, size_t *count);

int	ft_isscaped(char *str)
{
	size_t	count;

	count = 0;
	if (*(str - 1))
		str--;
	else
		return (0);
	while (*(str - count) && *(str - count) == 92)
		count++;
	// ft_printf("barras contadas: %d\n", count);
	if (count % 2)
		return (*(str + 1));
	return (0);
}

int	ft_isquote(char *str, char quote)
{
	size_t	count;

	count = 0;
	if (*str != quote)
	{
		// ft_printf("IS not a quote: (%c)-(%c)\n", *str, quote);
		return (0);
	}
	if (!ft_isscaped(str))
	{
		// ft_printf("IS QUOTE\n");
		return (*str);
	}
	// ft_printf("IS NOT QUOTE (%c) dell (%c)\n", *str, quote);
	return (0);
}


char	*smart_fill(char *input, char delim, size_t *count)
{
	size_t	tmp;
	char	*str;

	tmp = 0;
	if (delim)
	{
		while(input[*count] && !ft_isquote(&input[*count], delim))
			*count += 1;
		if(*count == 0)
			return (NULL);
		str = ft_calloc(sizeof(char), *(count) + 1);
		if (!str)
			return (NULL);
		while(*input && !ft_isquote(input, delim))
		{
			if (*input == 92)
				input++;
			// printf("Copy in str[%ld] (%c) = *input (%c)\n", tmp, str[tmp], *input);
			str[tmp] = *input;
			input++;
			tmp++;
		}
	}
	else
	{
		while(input[*count] && !ft_isspace(input[*count]) && !ft_isquote(&input[*count], 34) && !ft_isquote(&input[*count], 39))
			*count += 1;
		if(*count == 0)
			return (NULL);
		// ft_printf("IN SMART: COUNT:%d\n", *count);
		str = ft_calloc(sizeof(char), *(count) + 1);
		if (!str)
			return (NULL);
		while(*input && !ft_isspace(*input) && !ft_isquote(input, 34) && !ft_isquote(input, 39))
		{
			if (*input == 92)
				input++;
			// printf("Copy in str[%ld] (%c) = *input (%c)\n", tmp, str[tmp], *input);
			str[tmp] = *input;
			input++;
			tmp++;
		}
	}
	// ft_printf("IN SMART: RETURN: [$]%s[$]\n", str);
	return (str);
}



// int	ft_isspace(int argv)
// {
// 	if (argv == 32
// 		|| argv == '\n'
// 		|| argv == '\t'
// 		|| argv == '\v'
// 		|| argv == '\f'
// 		|| argv == '\r')
// 		return (argv);
// 	return (0);
// }

// int	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// int	main(int argc, char **argv)
// {
// 	size_t	count;
// 	char	*str;

// 	count = 0;
// 	write(1, argv[1], ft_strlen(argv[1]));
// 	write(1, "\n", 1);
// 	str = smart_fill(argv[1], 34, &count);
// 	printf("\nRETURN: [$]%s[$]\n", str);
// 	// write(1, str, ft_strlen(str));
// 	// if (ft_isquote(argv[1] + (ft_strlen(argv[1]) - 1), 34))
// 	// 	write(1, "IS QUOTE\n", 9);
// 	// else
// 	// 	write(1, "IS NOT QUOTE\n", 9);
// 	return (0);
// }