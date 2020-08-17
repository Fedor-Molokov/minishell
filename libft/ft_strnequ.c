/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 02:20:01 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/17 21:23:58 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t		i;

	if (s1 && s2)
	{
		i = 0;
		if (s1[i] == '\0' && s2[i] == '\0')
			return (1);
		while (i < n && (s1[i] || s2[i]))
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
	}
	return (1);
}
