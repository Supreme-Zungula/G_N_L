/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzungula <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 11:31:39 by yzungula          #+#    #+#             */
/*   Updated: 2018/05/31 16:35:52 by yzungula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(const char *str1, const char *str2)
{
	if (!str1 || !str2)
		return (0);
	if (str1 && str2)
	{
		if (ft_strcmp(str1, str2) == 0)
			return (1);
	}
	return (0);
}
