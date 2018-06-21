/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzungula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 10:32:51 by yzungula          #+#    #+#             */
/*   Updated: 2018/06/21 16:59:04 by yzungula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

static int get_newline(char *str)
{
	int i;

	i = 0;
	while ((str[i] != '\n') && (str[i] != '\0'))
		i++;
	return (i);
}
/*
static char *get_str_before(char *str, char c)
{
	size_t	i;
	char	*fresh;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != c || str[i] != '\0')
		i++;
	fresh = (char *)malloc(sizeof(char) * i + 1);
	if (fresh == NULL)
		return (NULL);
	i = 0;
	while (*str != c || *str != '\0')
	{
		fresh[i] = *str;
		i++;
		str++;
	}
	fresh[i] = '\0';
	return (fresh);
}

int		get_next_line(const int fd, char **line)
{
	static char		*str;
	char			buff[BUFF_SIZE + 1];
	size_t			ret_bytes;
	int				newln_pos;

	if (fd < 0 || !line || BUFF_SIZE <= 0 || (read(fd, buff, 0)) < 0)
		return (-1);
	if (!str)
		str = ft_strnew(1);
	while ((ret_bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[BUFF_SIZE] = '\0';
		str = ft_strjoin(str, buff);
		if (ft_strchr(buff, '\n'))
			break;
	}
	if ((ft_strlen(str) == 0) && ret_bytes == 0)
		return (0);
	newln_pos = get_newline(str);
	*line = ft_strsub(str, 0, newln_pos);
	str = ft_strsub(str, newln_pos + 1, ft_strlen(str));
	return (1);
}
*/

static t_list	*find_file(t_list **file_list, int fd)
{
	t_list	*curr;

	curr = (*file_list);
	while (curr)
	{
		if (curr->content_size == (size_t)fd)
			return (curr);
		curr = curr->next;
	}
	curr = ft_lstnew(NULL, 0);
	curr->content_size = fd;
	ft_lstadd(file_list, curr);
	return (*file_list);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*file_list;
	char			buff[BUFF_SIZE + 1];
	size_t			ret_bytes;
	int				newln_pos;
	t_list			*file;

	if (fd < 0 || !line || BUFF_SIZE <= 0 || (read(fd, buff, 0) < 0))
		return (-1);
	file = find_file(&file_list, fd);
	if (file->content == NULL)
		file->content = ft_strnew(0);
	if (!ft_strchr(file->content, '\n'))
	{
	while ((ret_bytes = read(file->content_size, buff, BUFF_SIZE) > 0))
	{
		buff[BUFF_SIZE] = '\0';
	//	puts("BEFORE JOIN:");
	//	printf("%s\n", file->content);
		file->content = ft_strjoin(file->content, buff);
	//	puts("AFTER JOIN:");
	//	printf("%s\n", file->content);
		if (ft_strchr(buff, '\n'))
			break;
	}
	}
	if (!ft_strlen((char *)file->content) && ret_bytes == 0)
		return (0);
	newln_pos = get_newline(file->content);
	*line = ft_strsub(file->content, 0, newln_pos);
	file->content = file->content + newln_pos + 1;
	//printf("\nREMAINS: %s\n", file->content);
	return (1);
}
