/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:41:44 by ncuello           #+#    #+#             */
/*   Updated: 2022/11/29 01:17:15 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "bmlib.h"

char	*ft_simple_quotes_two(char const *s, t_split *spt)
{
	char	*ptr;
	int		mode;

	mode = 1;
	while ((s[spt->i] != 39 || (s[spt->i] == 39 && (s[spt->i - 1] == 92
					|| mode == 1))) && s[spt->i])
	{	
		if (s[spt->i] == 39)
			mode = 0;
		spt->i++;
	}
	spt->end = spt->i - 1;
	ptr = ft_substr(s, spt->start, spt->end - spt->start + 1);
	if (!ptr)
		return (NULL);
	if (!ptr)
		return (NULL);
	return (ft_clean_char(ptr, 92, -1));
}

char	*ft_double_quotes_two(char const *s, t_split *spt)
{
	char	*ptr;
	int		mode;

	mode = 1;
	while ((s[spt->i] != 34 || (s[spt->i] == 34 && (s[spt->i - 1] == 92
					|| mode == 1))) && s[spt->i])
	{
		if (s[spt->i] == 34)
			mode = 0;
		spt->i++;
	}
	spt->end = spt->i - 1;
	ptr = (ft_substr(s, spt->start, spt->end - spt->start + 1));
	if (!ptr)
		return (NULL);
	ptr = ft_clean_char(ptr, 34, -1);
	if (!ptr)
		return (NULL);
	return (ft_clean_char(ptr, 92, -1));
}
