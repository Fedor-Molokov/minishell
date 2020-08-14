/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:41:42 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/15 02:19:18 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_strnchr(const char *s, int c)
{
    int     i;

    i = 0;
	while (*s != '\0')
	{
		if (*(char*)s == (char)c)
			return (i);
		s++;
        i++;
	}
	if ((char)c == '\0')
		return (-1);
	return (-1);
}