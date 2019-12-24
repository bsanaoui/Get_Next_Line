/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:05:59 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/10/24 17:06:00 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

void			*ft_calloc(size_t nitems, size_t size)
{
	void	*result;
	size_t	i;

	i = 0;
	if (nitems == 0 || size == 0)
		return (NULL);
	result = malloc(size * nitems);
	if (result == NULL)
		return (NULL);
	while (i < nitems)
	{
		((char *)result)[i] = 0;
		i++;
	}
	return (result);
}

size_t			ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	int			i;
	char		*ds;
	const char	*sr;

	if (!dst && !src)
		return (NULL);
	i = 0;
	ds = dst;
	sr = src;
	while (i < (int)n)
	{
		ds[i] = sr[i];
		i++;
	}
	return (dst);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	char	*tab;

	count = 0;
	tab = 0;
	if (!s)
		return (0);
	if (!(tab = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (len > 0 && s[start + count] && ft_strlen((char *)s) > start)
	{
		tab[count] = s[start + count];
		count++;
		len--;
	}
	tab[count] = '\0';
	return (tab);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen((char *)s1);
	j = 0;
	if (!(newstr = (char *)malloc((i + ft_strlen((char *)s2) + 1)
		* sizeof(char))))
		return (NULL);
	else
	{
		ft_memcpy(newstr, s1, i + 1);
		while (s2[j] != '\0')
		{
			newstr[i] = s2[j];
			i++;
			j++;
		}
		newstr[i] = '\0';
	}
	return (newstr);
}
