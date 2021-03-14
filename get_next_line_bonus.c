/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 15:34:11 by iariss            #+#    #+#             */
/*   Updated: 2020/02/02 18:19:10 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		get_next_line(int fd, char **line)
{
	char		*c;
	static char *tmp[7168];
	int			rd;
	char		*r;

	if (BUFFER_SIZE < 0 || fd < 0 || !line || read(fd, NULL, 0) ||
			(!(c = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	*line = ft_strdup("");
	if (!tmp[fd])
		tmp[fd] = ft_strdup("");
	while ((rd = read(fd, c, BUFFER_SIZE)) > 0)
	{
		c[rd] = '\0';
		r = tmp[fd];
		tmp[fd] = ft_strjoin(tmp[fd], c);
		free(r);
		if (ft_strchr(tmp[fd], '\n') != 0)
			break ;
	}
	free(c);
	if (rd == -1)
		return (-1);
	return (ft_pp(&tmp[fd], &(*line)));
}

int		ft_pp(char **tmp, char **line)
{
	int		x;
	char	*p;

	x = 0;
	p = *tmp;
	while (p[x] && p[x] != '\n')
		x++;
	p = *line;
	*line = ft_substr(*tmp, 0, x);
	free(p);
	p = *tmp;
	if ((*tmp)[x] == '\n')
	{
		*tmp = ft_substr(*tmp, x + 1, ft_strlen(*tmp) - x);
		free(p);
		return (1);
	}
	else if ((*tmp)[x] == '\0')
	{
		free(p);
		*tmp = NULL;
		return (0);
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = ((char*)s);
	while (*str != c)
	{
		if (*str == '\0')
			return (0);
		str++;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, const char *s2)
{
	int		i;
	int		j;
	int		k;
	char	*b;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(b = (char*)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	k = 0;
	while (s1[k] && k < i)
	{
		b[k] = s1[k];
		k++;
	}
	k = 0;
	while (s2[k] && k < j)
	{
		b[i + k] = s2[k];
		k++;
	}
	b[i + k] = '\0';
	return (b);
}
