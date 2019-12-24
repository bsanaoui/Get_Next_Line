/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:25:00 by bsanaoui          #+#    #+#             */
/*   Updated: 2019/11/11 16:26:09 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		free_line(char **s)
{
	if (*s != NULL)
	{
		free(*s);
		*s = NULL;
	}
	return (-1);
}

static int		it_is_line(char *s, ssize_t nbyte_read, int start)
{
	while (s[start])
	{
		if (s[start] == '\n')
			return (start + 1);
		if (!nbyte_read)
			return (-1);
		start++;
	}
	return (0);
}

static int		final_line(char **line, char **tmp_line,
	int size_line, int start)
{
	if (size_line == -1)
	{
		free_line(&(*line));
		if (!(*line = ft_substr(*tmp_line, start, ft_strlen(*tmp_line))))
			return (free_line(&(*tmp_line)));
		free_line(&(*tmp_line));
		return (0);
	}
	if ((size_line - start) < 1)
	{
		free_line(&(*line));
		if (!(*line = ft_substr(*tmp_line, start, start)))
			return (free_line(&(*tmp_line)));
		free_line(&(*tmp_line));
		return (0);
	}
	return (1);
}

static int		check_line(int fd, char **tmp_line,
	ssize_t *nbyte_read, int start)
{
	char	*buf;
	int		size_line;
	char	*tmp;

	buf = NULL;
	size_line = 0;
	if (*nbyte_read > 0)
	{
		if (!(buf = (char *)malloc((BUFFER_SIZE + 1))))
			return (free_line(&buf));
		while (!(size_line = it_is_line(*tmp_line, *nbyte_read, start))
				&& *nbyte_read > 0)
		{
			*nbyte_read = read(fd, buf, (BUFFER_SIZE));
			buf[*nbyte_read] = '\0';
			tmp = *tmp_line;
			if (!(*tmp_line = ft_strjoin(*tmp_line, buf)))
				return (free_line(&(*tmp_line)));
			free_line(&tmp);
		}
	}
	free_line(&buf);
	return (size_line);
}

int				get_next_line(int fd, char **line)
{
	static char		*tmp_line = NULL;
	static ssize_t	nbyte_read = 1;
	static int		start = 0;
	int				size_line;

	*line = NULL;
	if (nbyte_read < 0 || fd < 0 || !line ||
		read(fd, NULL, 0) != 0 || BUFFER_SIZE < 0)
		return (-1);
	if (!tmp_line)
	{
		if (!(tmp_line = (char *)ft_calloc(sizeof(char), 1)))
			return (-1);
	}
	size_line = check_line(fd, &tmp_line, &nbyte_read, start);
	if (size_line >= 0 && nbyte_read >= 0)
	{
		free_line(&(*line));
		if (!(*line = ft_substr(tmp_line, start,
				size_line - start - 1 >= 0 ? size_line - start - 1 : 1)))
			return (free_line(&tmp_line));
		start = size_line;
	}
	return (nbyte_read == 0 ? final_line(&(*line),
		&tmp_line, size_line, start) : 1);
}
