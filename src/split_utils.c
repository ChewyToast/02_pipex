/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncuello <ncuello@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:32:04 by ncuello           #+#    #+#             */
/*   Updated: 2022/10/12 19:18:51 by ncuello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_clean_char(char *str, char c, int i)
{
	t_clean	cln;

	cln.len = ft_strlen(str);
	cln.num_c = 0;
	while (str[++i])
	{
		if (str[i] == c && (i > 0 && str[i - 1] != 92))
			cln.num_c++;
	}
	cln.new_str = (char *) malloc(cln.len - cln.num_c + 1);
	if (!cln.new_str)
		return (NULL);
	i = 0;
	cln.j = 0;
	while (str[cln.j])
	{
		if (str[cln.j] != c || (str[cln.j] == c && str[cln.j - 1] == 92))
			cln.new_str[i++] = str[cln.j];
		cln.j++;
	}
	cln.new_str[i] = '\0';
	return (cln.new_str);
}

char	*ft_simple_quotes(char const *s, t_split *spt)
{
	char	*ptr;

	spt->start = ++spt->i;
	while ((s[spt->i] != 39 || (s[spt->i] == 39 && s[spt->i - 1] == 92))
		&& s[spt->i])
		spt->i++;
	spt->end = spt->i - 1;
	ptr = ft_substr(s, spt->start, spt->end - spt->start + 1);
	if (!ptr)
		return (NULL);
	return (ft_clean_char(ptr, 92, -1));
}

char	*ft_double_quotes(char const *s, t_split *spt)
{
	char	*ptr;

	spt->start = ++spt->i;
	while ((s[spt->i] != 34 || (s[spt->i] == 34 && s[spt->i - 1] == 92))
		&& s[spt->i])
		spt->i++;
	spt->end = spt->i - 1;
	ptr = (ft_substr(s, spt->start, spt->end - spt->start + 1));
	if (!ptr)
		return (NULL);
	return (ft_clean_char(ptr, 92, -1));
}

char	*ft_word(char const *s, t_split *spt, char c)
{
	char	*ptr;

	spt->start = spt->i;
	while (s[spt->i] != '\0')
	{
		if (s[spt->i] == 39 && s[spt->i - 1 != 92])
			return (ft_simple_quotes(s, spt));
		if (s[spt->i] == 34 && s[spt->i - 1] != 92)
			return (ft_double_quotes_two(s, spt));
		if (s[spt->i] != c && s[spt->i] != 34 && s[spt->i] != 39
			&& (s[spt->i + 1] == c || s[spt->i + 1] == '\0'))
		{
			spt->end = spt->i;
			ptr = ft_substr(s, spt->start, spt->end - spt->start + 1);
			return (ptr);
			if (!ptr)
				return (NULL);
			return (ft_clean_char(ptr, 92, -1));
		}
		spt->i++;
	}
	return (NULL);
}
