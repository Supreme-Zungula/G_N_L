/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzungula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 10:32:51 by yzungula          #+#    #+#             */
/*   Updated: 2018/06/29 16:05:45 by yzungula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static int	get_newline(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

int			store_line(char **line, char **str, int ret_bytes)
{
	char	*temp;
	int		newln_pos;

	if (ret_bytes == 0 && !ft_strlen(*str))
		return (0);
	newln_pos = get_newline(*str);
	*line = ft_strsub(*str, 0, newln_pos);
	if (newln_pos == (int)ft_strlen(*str))
		ft_strclr(*str);
	else
	{
		temp = *str;
		*str = ft_strsub(*str, newln_pos + 1, ft_strlen(*str));
		free(temp);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char		*str[1];
	char			*buff;
	char			*temp;
	size_t			ret_bytes;

	if (BUFF_SIZE < 0)
		return (-1);
	temp = NULL;
	buff = ft_strnew(BUFF_SIZE);
	if (fd < 0 || !line || BUFF_SIZE <= 0 || (read(fd, buff, 0)) < 0)
		return (-1);
	while ((ret_bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (str[fd] == NULL)
			str[fd] = ft_strnew(0);
		temp = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = temp;
		if (ft_strchr(buff, '\n'))
			break ;
		ft_strclr(buff);
	}
	ft_strdel(&buff);
	return (store_line(line, &str[fd], ret_bytes));
}
