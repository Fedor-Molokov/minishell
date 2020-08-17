/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 01:54:29 by dmarsell          #+#    #+#             */
/*   Updated: 2020/08/18 02:07:03 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_dup(const char *mem, char *copy)
{
    int     i;

    i = 0;
    while (mem[i])
	{
		copy[i] = mem[i];
		i++;
	}
}

char	*ft_memdup(const void *mem)
{
	void	*copy;
	int		i;

	copy = malloc(ft_strlen((char *)mem) + 1);
	if (copy == NULL)
		return (0);
	i = 0;
    ft_dup((const char *)mem, (char *)copy);
	return (copy);
}