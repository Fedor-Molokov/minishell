/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:08:20 by dmarsell          #+#    #+#             */
/*   Updated: 2019/09/21 17:00:04 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if ((str1[i] != str2[i]) || str1[i] == '\0' || str2[i] == '\0')
			break ;
		i++;
	}
	return ((int)((unsigned char)str1[i] - (unsigned char)str2[i]));
}
