/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:37:56 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/11/30 20:33:13 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmlib.h"

static int	ft_isscaped(char *str)
{
	size_t	count;

	count = 0;
	if (*(str - 1))
		str--;
	else
		return (0);
	while (*(str - count) && *(str - count) == 92)
		count++;
	if (count % 2)
		return (*(str + 1));
	return (0);
}

int	ft_isquote(char *str, char quote)
{
	size_t	count;

	count = 0;
	if (*str != quote)
		return (0);
	if (!ft_isscaped(str))
		return (*str);
	return (0);
}

static char	*extra_smart_fill(char *input, size_t *count)
{
	size_t	tmp;
	char	*str;

	tmp = 0;
	while (input[*count] && !ft_isspace(input[*count])
		&& !ft_isquote(&input[*count], 34)
		&& !ft_isquote(&input[*count], 39))
		*count += 1;
	if (*count == 0)
		return (NULL);
	str = ft_calloc(sizeof(char), *(count) + 1);
	if (!str)
		return (NULL);
	while (*input && !ft_isspace(*input)
		&& !ft_isquote(input, 34)
		&& !ft_isquote(input, 39))
	{
		if (*input == 92)
			input++;
		str[tmp] = *input;
		input++;
		tmp++;
	}
	return (str);
}

char	*smart_fill(char *input, char delim, size_t *count)
{
	size_t	tmp;
	char	*str;

	tmp = 0;
	if (delim)
	{
		while (input[*count] && !ft_isquote(&input[*count], delim))
			*count += 1;
		if (*count == 0)
			return (NULL);
		str = ft_calloc(sizeof(char), *(count) + 1);
		if (!str)
			return (NULL);
		while (*input && !ft_isquote(input, delim))
		{
			if (*input == 92)
				input++;
			str[tmp] = *input;
			input++;
			tmp++;
		}
	}
	else
		str = extra_smart_fill(input, count);
	return (str);
}
