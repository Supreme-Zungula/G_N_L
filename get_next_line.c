/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzungula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 10:32:51 by yzungula          #+#    #+#             */
/*   Updated: 2018/06/22 17:40:37 by yzungula         ###   ########.fr       */
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
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

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
	//curr = ft_lstnew("\0", fd);
	curr = ft_lstnew(NULL, 0);
	curr->content_size = fd;
	ft_lstadd(file_list, curr);
	return (curr);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*file_list;
	char			buff[BUFF_SIZE + 1];
	char			*temp;
	int				ret_bytes;
	int				newln_pos;
	t_list			*file;
;
	if (fd < 0 || !line || BUFF_SIZE <= 0 || (read(fd, buff, 0) < 0))
		return (-1);
	file = find_file(&file_list, fd);
	ft_bzero(buff, BUFF_SIZE + 1);
	while ((ret_bytes = read(file->content_size, buff, BUFF_SIZE) > 0))
	{
		if (file->content == NULL)
			file->content = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(file->content, buff);
			free(file->content);
			file->content = temp;
		}
		if (ft_strchr(buff, '\n'))
			break;
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	if (!ft_strlen(file->content) && ret_bytes == 0)
		return (0);
	newln_pos = get_newline(file->content);
	*line = ft_strsub(file->content, 0, newln_pos);
	if ((file->content + newln_pos))
		file->content = file->content + newln_pos + 1;
	//else
	//	free(file->content);
	return (1);
} 
