/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:33:47 by bruno             #+#    #+#             */
/*   Updated: 2022/11/30 16:24:37 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"

size_t	count_parts(char *input, size_t rtrn);
_Bool	fill_parts(char *input, char **rtrn);
int	ft_isscaped(char *str);
int	ft_isquote(char *str, char quote);
char	*smart_fill(char *input, char delim, size_t *count);

char	**ft_cmd_split(char *input)
{
	char	**rtrn;

	rtrn = ft_calloc(sizeof(char *), count_parts(input, 0) + 1);
	if (!rtrn)
		return (NULL);
	if (!fill_parts(input, rtrn))
		return (NULL); //Error exit have to be cleaned;
	return (rtrn);
	
}

size_t	count_parts(char *input, size_t rtrn)
{
	if (!*input)
		return (rtrn);
	while(*input)
	{
		if (ft_isquote(input, 39))
		{
			input++;
			while (*input && !ft_isquote(input, 39))
				input++;
			rtrn++;
		}
		else if (ft_isquote(input, 34))
		{
			input++;
			while (*input && !ft_isquote(input, 34))
				input++;
			rtrn++;
		}
		else if (!ft_isspace(*input))
		{
			input++;
			while (*input && !ft_isquote(input, 34) && !ft_isquote(input, 39))
				input++;
			rtrn++;
			if (*input == 34 || *input == 39)
				input--;
		}
		input++;
	}
	// ft_printf("parts count: %d\n", rtrn);
	return (rtrn);
}

_Bool	fill_parts(char *input, char **rtrn)
{
	size_t	count;

	count = 0;
	while(*input)
	{
		if (ft_isquote(input, 39))
		{
			// ft_printf("IS SIMPLE QUOTE!---------------------\n");
			input++;
			*rtrn = smart_fill((input), *(input - 1), &count);
			if (!*rtrn && count)
				return (0);
			// ft_printf("1CMD: [$]%s[$]\n", *rtrn);
			rtrn++;
		}
		else if (ft_isquote(input, 34))
		{
			// ft_printf("IS DOUBLE QUOTE!---------------------\n");
			input++;
			*rtrn = smart_fill((input), *(input - 1), &count);
			if (!*rtrn && count)
				return (0);
			// ft_printf("n2CMD: [$]%s[$]\n", *rtrn);
			rtrn++;
		}
		else if (!ft_isspace(*input))
		{
			// ft_printf("IS SPACE!---------------------\n");
			*rtrn = smart_fill((input), 0, &count);
			if (!*rtrn && count)
				return (0);
			if (input[count] == 34 || input[count] == 39)
				input--;
			// ft_printf("3CMD: [$]%s[$]\n", *rtrn);
			rtrn++;
		}
		// else
			// ft_printf("PASANDO DE: ]%c[\n", *input);
		input += count;
		count = 0;
		if (*input)
			input++;
	}
	return (rtrn);
}