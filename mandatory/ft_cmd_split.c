/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:33:47 by bruno             #+#    #+#             */
/*   Updated: 2022/11/30 22:45:34 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"

static size_t	count_parts(char *input, size_t rtrn, int util);
static _Bool	fill_parts(char *input, char **rtrn, int util, size_t count);
int				ft_isquote(char *str, char quote);
char			*smart_fill(char *input, char delim, size_t *count);

char	**ft_cmd_split(char *input)
{
	char	**rtrn;
	size_t	count;

	count = 0;
	if (input)
		count = count_parts(input, 0, 0);
	rtrn = ft_calloc(sizeof(char *), count + 1);
	if (!rtrn)
		return (NULL);
	if (!fill_parts(input, rtrn, 0, 0))
	{
		if (rtrn)
			while (count--)
				free(*(rtrn++));
		return (NULL);
	}
	return (rtrn);
}

static size_t	count_parts(char *input, size_t rtrn, int util)
{
	while (*input)
	{
		util = ft_isquote(input, 39);
		if (!util)
			util = ft_isquote(input, 34);
		if (util)
		{
			input++;
			while (*input && !ft_isquote(input, util))
				input++;
			rtrn++;
		}
		else if (!ft_isspace(*input))
		{
			input++;
			while (*input && !ft_isspace(*input) && !ft_isquote(input, 34)
				&& !ft_isquote(input, 39))
				input++;
			rtrn++;
			if (*input == 34 || *input == 39)
				input--;
		}
		if (*input)
			input++;
	}
	return (rtrn);
}


static _Bool	fill_parts(char *input, char **rtrn, int util, size_t count)
{
	while (*input)
	{
		util = ft_isquote(input, 39);
		if (!util)
			util = ft_isquote(input, 34);
		if (util)
		{
			input++;
			*rtrn = smart_fill((input), *(input - 1), &count);
			if (!*rtrn && count)
				return (0);
			rtrn++;
		}
		else if (!ft_isspace(*input))
		{
			*rtrn = smart_fill((input), 0, &count);
			if (!*rtrn && count)
				return (0);
			if (input[count] == 34 || input[count] == 39)
				input--;
			rtrn++;
		}
		input += count;
		count = 0;
		if (*input)
			input++;
	}
	return (rtrn);
}
