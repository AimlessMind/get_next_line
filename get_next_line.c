/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbruce <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 17:59:17 by zbruce            #+#    #+#             */
/*   Updated: 2018/06/08 00:05:31 by zbruce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_alej(char **s1, char *s2)
{
	char	*au;

	if (!*s1)
	{
		*s1 = ft_strdup(s2);
		return ;
	}
	au = ft_strjoin(*s1, s2);
	ft_strdel(s1);
	*s1 = au;
}

int		ft_noleaks(char **s1, char *s2)
{
	char	*tmp;

	if (!s2)
	{
		ft_strdel(s1);
		return (1);
	}
	tmp = ft_strdup(s2 + 1);
	ft_strdel(s1);
	*s1 = tmp;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[6144];
	char		*aux;
	char		buf[BUFF_SIZE + 1];
	int			ind;
	int			ret;

	ft_bzero(buf, BUFF_SIZE + 1);
	if (read(fd, buf, 0) == -1)
		return (-1);
	while (!ft_strchr(str[fd], '\n') && (ret = read(fd, buf, BUFF_SIZE)) > 0)
		ft_alej(&str[fd], buf);
	ind = 0;
	if ((aux = ft_strchr(str[fd], '\n')) != NULL)
	{
		while (str[fd][ind] != *aux)
			ind++;
		*line = ft_strnew(ind);
		*line = ft_strncpy(*line, str[fd], ind);
		return (ft_noleaks(&str[fd], aux));
	}
	if (ret == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
		return (0);
	*line = ft_strdup(str[fd]);
	return (ft_noleaks(&str[fd], NULL));
}
