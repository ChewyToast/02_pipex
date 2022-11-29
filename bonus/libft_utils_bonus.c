/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:41:26 by ncuello           #+#    #+#             */
/*   Updated: 2022/11/29 01:17:19 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "bmlib.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	count;

	count = 0;
	if (n == 0)
		return (0);
	while (s1[count] == s2[count] && s1[count] && s2[count] && count < n - 1)
		count ++;
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*dst;
	size_t	i;
	size_t	j;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dst = (char *) malloc(len_s1 + len_s2 + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len_s2)
	{
		dst[i + j] = s2[j];
		j++;
	}
	*(dst + i + j) = '\0';
	return (dst);
}

int	ft_strlen(const char *string)
{
	int	counter;

	counter = 0;
	while (*string != '\0')
	{
		counter ++;
		++string;
	}
	return (counter);
}

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		len;

	len = ft_strlen(s);
	dst = (char *) malloc(len + 1);
	if (!dst)
		return (NULL);
	return ((char *)ft_memcpy(dst, s, len + 1));
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		counter;
	char		*ptr;
	const char	*ptr1;

	counter = 0;
	ptr = dst;
	ptr1 = src;
	if (dst == src)
		return (dst);
	while (counter < n)
	{
		*(ptr + counter) = *(ptr1 + counter);
		counter++;
	}
	return (dst);
}
