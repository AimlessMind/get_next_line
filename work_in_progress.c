/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbruce <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 17:59:17 by zbruce            #+#    #+#             */
/*   Updated: 2018/06/05 17:03:00 by zbruce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

#include <stdio.h>

/*
**	s1 has a \n
**	s2 is buffer which contains info read from file
**
**	Need to append s2 to the end of s1
**	au is the appended version os s1
**
**	but this breaks sometimes ??? why ???
*/

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

/*
**	s1 is your static string of whatever the fuck size
**	s2 is your aux string which points to the newline character
**	
**	s2 is a string that starts at the newline character
**	s2 +1 is to get beyone the newline character
**
**	tmp will become a new string that is everything beyond the newline character
**	free s1 and make it point to tmp
*/

int		ft_noleaks(char **s1, char *s2)
{
	char	*tmp;

	if (!s2)
	{
		ft_strdel(s1);
		return (1);
	}
	/* possibly full of bs*/
	if (*s2 + 1 == '\0')
		tmp = ft_strdup(s2);
	else
		tmp = ft_strdup(s2 + 1);
	ft_strdel(s1);
	*s1 = tmp;
	return (1);
}

/*
**	Problem: Garbage on the last return of line
*/

int		get_next_line(int fd, char **line)
{
	static char	*str[666];
	char		*aux;
	char		buf[BUFF_SIZE + 1];
	int			ind;
	int			ret;

	ft_bzero(buf, BUFF_SIZE + 1);
	if (read(fd, buf, 0) == -1)
		return (-1);
	// Read loop
	while (!ft_strchr(str[fd], '\n') && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		ft_alej(&str[fd], buf);
	}
	ind = 0;
	// Assign line the proper size and character to become a new line
	if ((aux = ft_strchr(str[fd], '\n')) != NULL)
	{
		while (str[fd][ind] != *aux)
			ind++;
		str[fd][ind] = '\0';
		*line = ft_strnew(ind);
		*line = ft_strncpy(*line, str[fd], ind);
		//printf("Loop str[fd]: %s\n", str[fd]);
		return (ft_noleaks(&str[fd], aux));
	}
	//printf("Exit str[fd]: %s\n", str[fd]);
	// Exit condition
	if (ret == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
		return (0);
	// If there is no newline in whatever then just copy it and send it out
	// str[fd][ret] = '\0';
	*line = ft_strdup(str[fd]); // <----- PROBLEM str[fd] is not indexed past the previous output
	// skip to the new line
	//	+ 1 to get past newline
	// if ret == 1 do not + 1 past the newline
	//printf("ret: %d\n", ret);
	return (ft_noleaks(&str[fd], NULL));
}
