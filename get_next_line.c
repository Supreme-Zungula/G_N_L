/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzungula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 10:32:51 by yzungula          #+#    #+#             */
/*   Updated: 2018/06/20 14:21:16 by yzungula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

static int	get_newline(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
/*
static void	save_line(char *str, char **line)
{
	int		newln_pos;

	newln_pos = get_newline(str);
	str[newln_pos] = '\0';
	*line = ft_strdup(str);
}
*/
int		get_next_line(const int fd, char **line)
{
	static char		*str;
	char			buff[BUFF_SIZE + 1];
	size_t			ret_bytes;
	int				newln_pos;

	if (fd < 0 || !line || BUFF_SIZE <= 0 || (read(fd, buff, 0)) < 0)
		return (-1);
	while ((ret_bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[BUFF_SIZE] = '\0';
		if (str == NULL)
			str = ft_strdup(buff);
		else
			str = ft_strjoin(str, buff);
		if (get_newline(str) >= 0)
			break;
	}
	newln_pos = get_newline(str);
	*line = ft_strsub(str, 0, newln_pos);
	if (ft_strlen(str) && ret_bytes > 0)
	{
		str = ft_strdup(str + newln_pos + 1);
		return (1);
	}
	if (ret_bytes == 0 && !(ft_strlen(str)))
	{
		*line = str;
		return (0);
	}
	return (-1);
}
