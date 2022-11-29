/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncuello <ncuello@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:26:55 by ncuello           #+#    #+#             */
/*   Updated: 2022/06/22 21:02:45 by ncuello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static int	ft_get_words(char const *str, char c, int words);
static char	**ft_result(char const *str, char c, char **result, t_split *spt);
static char	**ft_free_array(char **ptr);
char		*ft_substr(char const *s, unsigned int start, size_t len);

char	**ft_split_args(char const *s, char c)
{
	t_split	spt;
	char	**arry;

	arry = (char **) malloc ((ft_get_words(s, c, 0) + 1) * sizeof(char *));
	if (!arry)
		return (NULL);
	spt.i = 0;
	spt.num_words = 0;
	arry = ft_result(s, c, arry, &spt);
	return (arry);
}

static int	ft_get_words(char const *str, char c, int words)
{
	if (*str == '\0')
		return (words);
	while (*str)
	{
		if (*str == 39 && *(str - 1) != 92)
		{
			str++;
			while ((*str != 39 || (*str == 39 && *(str - 1) == 92)) && *str)
				str++;
			words++;
		}
		else if (*str == 34 && *(str - 1) != 92)
		{
			str++;
			while ((*str != 34 || (*str == 34 && *(str - 1) == 92)) && *str)
				str++;
			words++;
		}
		else if (*str != c && (*(str + 1) == c || *(str + 1) == '\0'))
			words++;
		str++;
	}
	return (words);
}

static char	**ft_result(char const *str, char c, char **result, t_split *spt)
{
	while (str[spt->i] != '\0')
	{
		if (spt->i > 0 && str[spt->i] == 39 && str[spt->i - 1] != 92)
		{
			result[spt->num_words] = ft_simple_quotes(str, spt);
			if (result[spt->num_words++] == NULL)
				return (ft_free_array(result));
		}
		else if (spt->i > 0 && str[spt->i] == 34 && str[spt->i - 1] != 92)
		{
			result[spt->num_words] = ft_double_quotes(str, spt);
			if (result[spt->num_words++] == NULL)
				return (ft_free_array(result));
		}
		if ((spt->i > 0 && str[spt->i] != c && str[spt->i - 1] == c)
			|| (spt->i == 0 && str[spt->i] != c))
		{
			result[spt->num_words] = ft_word(str, spt, c);
			if (result[spt->num_words++] == NULL)
				return (ft_free_array(result));
		}
		spt->i++;
	}
	result[spt->num_words] = NULL;
	return (result);
}

static char	**ft_free_array(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free (ptr[i]);
		i++;
	}
	free (ptr);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dst;
	unsigned int	i;
	unsigned int	s_len;

	s_len = (unsigned int)ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len > s_len || (s_len - start) < len)
		len = s_len - start;
	dst = (char *) malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(dst + i) = *(s + start + i);
		i++;
	}
	*(dst + i) = '\0';
	return (dst);
}
