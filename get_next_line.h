/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzungula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:36:34 by yzungula          #+#    #+#             */
/*   Updated: 2018/06/21 16:59:26 by yzungula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include "./libft/libft.h"

# define BUFF_SIZE 100

typedef struct		t_file
{
	char			*content;
	int				fd;
}					t_file;

int		get_next_line(const int fd, char **line);
#endif
