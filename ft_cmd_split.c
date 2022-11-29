/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:33:47 by bruno             #+#    #+#             */
/*   Updated: 2022/11/29 18:49:52 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"

char	**ft_cmd_split(char *input)
{
	t_split	cs;
	char	*rtrn;

	rtrn = malloc(sizeof(char *) * count_parts(input, 0));
	if (!rtrn)
		return (NULL);
	if (!fill_parts(input))
		return (NULL); //Error exit have to be cleaned;
	return (rtrn);
	
}

size_t	count_parts(char *input, size_t rtrn)
{
	if (!*input)
		return (rtrn);
	while(*input)
	{
		if (*input == 39 && *(input - 1) != 92)
		{
			input++;
			while (*input && (*input != 39 || (input - 1) == 92))
				input++;
			rtrn++;
		}
		else if (*input == 34 && *(input - 1) != 92)
		{
			input++;
			while (*input && *(input != 34 || *(input - 1) == 92))
				input++;
			rtrn++;
		}
		else if (!ft_isspace(*input) && (!*(input + 1)
				|| ft_isspace(*(input + 1))))
			rtrn++
		input++;
	}
	return (rtrn);
}

_Bool	fill_parts(char *input, char **rtrn)
{
	if (!*input)
		return (rtrn);
	while(*input)
	{
		if (*input == 39 && *(input - 1) != 92)
		{
			input++;
			while (*input && (*input != 39 || (input - 1) == 92))
				input++;
			rtrn++;// Substr
		}
		else if (*input == 34 && *(input - 1) != 92)
		{
			input++;
			while (*input && *(input != 34 || *(input - 1) == 92))
				input++;
			rtrn++// Substr
		}
		else if (!ft_isspace(*input) && (!*(input + 1)
				|| ft_isspace(*(input + 1))))
			rtrn++// Substr
		input++;
	}
	return (rtrn);
}