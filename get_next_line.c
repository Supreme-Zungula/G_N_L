/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzungula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 11:41:12 by yzungula          #+#    #+#             */
/*   Updated: 2018/06/18 16:37:32 by yzungula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
/*
static int	get_newln(char *str)
{
	int		found;

	found = 0;
	while (str[found] != '\n')
		found++;
	return (found);
}
*/
int			get_next_line(int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static char		*tmp_str;
	size_t			bytes_read;
	int				newln_pos;

	newln_pos = 0;
	if (fd < 0 || !line || (read(fd, buff, 0)) < 0)
		return (-1);
	else
		{
			while ((bytes_read = read(fd, buff, BUFF_SIZE)))
			{
				buff[bytes_read] = '\0';
				if (tmp_str == NULL)
					tmp_str = ft_strdup(buff);
				else
					tmp_str = ft_strjoin(tmp_str, buff);
				if (ft_strchr(buff, '\n') != NULL)
					break;
			}
		}
	while (tmp_str[newln_pos] != '\n')
		newln_pos++;
	//newln_pos = get_newln(tmp_str);
	*line = ft_strsub(tmp_str, 0, newln_pos);
	tmp_str = ft_strdup(tmp_str + newln_pos);
	if (bytes_read == 0 && ft_strlen(*line) == 0)
	{
		puts("\nEND OF FILE");
		printf("bytesread = %zu\n", bytes_read);
		printf("*line = %s\n", *line);
		return (0);
	}
	else
		return (1);
}
/*
int main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	while (get_next_line(fd, &line))
		printf("%s",line);
	close(fd);
}*/
