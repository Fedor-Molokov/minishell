/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 16:04:03 by qmuntada          #+#    #+#             */
/*   Updated: 2020/08/19 17:36:56 by dmarsell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*re_alloc(char *str, size_t size)
{
	char	*p;
	size_t	i;

	p = NULL;
	i = 0;
	if (str)
	{
		p = (char *)malloc(sizeof(char) * (size));
		if (!p)
			return (NULL);
		ft_bzero(p, size);
		ft_strcpy(p, str);
		free(str);
		str = NULL;
	}
	return (p);
}

static int	ft_not_bull(char *str)
{
	if (str[0] != '\0')
		return (1);
	return (0);
}

static char	*ft_strrsub(char *s, size_t len)
{
	char			*p;
	size_t			i;
	size_t			start;

	i = 0;
	if (!s)
		return (NULL);
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	start = ft_strlen(s) - len;
	while (i < len)
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
	ft_strclr(s);
	free(s);
	s = NULL;
	return (p);
}

int			get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE_GNL + 1];
	char		*tmp;
	static char *save;
	int			ret;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	if (!save)
		save = ft_strnew(BUFF_SIZE_GNL + 1);
	ft_bzero(buf, BUFF_SIZE_GNL + 1);
	while (!ft_strchr(buf, '\n') && (ret = read(fd, buf, BUFF_SIZE_GNL)))
	{
		save = re_alloc(save, ft_strlen(save) + ret + 1);
		save = ft_strncat(save, buf, ret);
	}
	if ((tmp = ft_strchr(save, '\n')))
	{
		*line = ft_strsub(save, 0, ft_strlen(save) - ft_strlen(tmp));
		save = ft_strrsub(save, ft_strlen(&tmp[1]));
		return (1);
	}
	*line = ft_strdup(save);
	ret = ft_not_bull(save);
	ft_strclr(save);
	return (ret == 0 ? 0 : 1);
}
